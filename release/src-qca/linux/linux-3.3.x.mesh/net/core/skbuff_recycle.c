/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 *
 * Generic skb recycler
 *
 */
#include "skbuff_recycle.h"
#include <trace/events/skb.h>
#include <linux/proc_fs.h>
#include <linux/string.h>

static struct proc_dir_entry *proc_net_skbrecycler;

static DEFINE_PER_CPU(struct sk_buff_head, recycle_list);
static int skb_recycle_max_skbs = SKB_RECYCLE_MAX_SKBS;

#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
static DEFINE_PER_CPU(struct sk_buff_head, recycle_spare_list);
static struct global_recycler glob_recycler;
static int skb_recycle_spare_max_skbs = SKB_RECYCLE_SPARE_MAX_SKBS;
#endif

inline struct sk_buff *skb_recycler_alloc(struct net_device *dev, unsigned int length) {
	unsigned long flags;
	struct sk_buff_head *h;
	struct sk_buff *skb = NULL;

	if (unlikely(length > SKB_RECYCLE_SIZE)) {
		return NULL;
	}

	h = &get_cpu_var(recycle_list);
	local_irq_save(flags);
	skb = __skb_dequeue(h);
#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	if (unlikely(!skb)) {
		uint8_t head;
		spin_lock(&glob_recycler.lock);
		/* If global recycle list is not empty, use global buffers */
		head = glob_recycler.head;
		if (likely(head != glob_recycler.tail)) {
			/* Move SKBs from global list to CPU pool */
			skb_queue_splice_init(&glob_recycler.pool[head], h);
			head = (head + 1) & SKB_RECYCLE_MAX_SHARED_POOLS_MASK;
			glob_recycler.head = head;
			spin_unlock(&glob_recycler.lock);
			/* We have refilled the CPU pool - dequeue */
			skb = __skb_dequeue(h);
		} else {
			spin_unlock(&glob_recycler.lock);
		}
	}
#endif
	local_irq_restore(flags);
	put_cpu_var(recycle_list);

	if (likely(skb)) {
		struct skb_shared_info *shinfo;

		/* We're about to write a large amount to the skb to
		 * zero most of the structure so prefetch the start
		 * of the shinfo region now so it's in the D-cache
		 * before we start to write that.
		 */
		shinfo = skb_shinfo(skb);
		prefetchw(shinfo);

		zero_struct(skb, offsetof(struct sk_buff, tail));
		atomic_set(&skb->users, 1);
#ifdef NET_SKBUFF_DATA_USES_OFFSET
		skb->mac_header = ~0U;
#endif
		zero_struct(shinfo, offsetof(struct skb_shared_info, dataref));
		atomic_set(&shinfo->dataref, 1);

		skb->data = skb->head + NET_SKB_PAD;
		skb_reset_tail_pointer(skb);

		skb->dev = dev;
	}

	return skb;
}

inline bool skb_recycler_consume(struct sk_buff *skb) {
	unsigned long flags;
	struct sk_buff_head *h;

	/* Can we recycle this skb?  If not, simply return that we cannot */
	if (unlikely(!consume_skb_can_recycle(skb, SKB_RECYCLE_MIN_SIZE,
					      SKB_RECYCLE_MAX_SIZE)))
		return false;

	/* If we can, then it will be much faster for us to recycle this one
	 * later than to allocate a new one from scratch.
	 */
	preempt_disable();
	h = &__get_cpu_var(recycle_list);
	local_irq_save(flags);
	/* Attempt to enqueue the CPU hot recycle list first */
	if (likely(skb_queue_len(h) < skb_recycle_max_skbs)) {
		__skb_queue_head(h, skb);
		local_irq_restore(flags);
		preempt_enable();
		return true;
	}
#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	h = &__get_cpu_var(recycle_spare_list);

	/* The CPU hot recycle list was full; if the spare list is also full,
	 * attempt to move the spare list to the global list for other CPUs to
	 * use.
	 */
	if (unlikely(skb_queue_len(h) >= skb_recycle_spare_max_skbs)) {
		uint8_t cur_tail, next_tail;
		spin_lock(&glob_recycler.lock);
		cur_tail = glob_recycler.tail;
		next_tail = (cur_tail + 1) & SKB_RECYCLE_MAX_SHARED_POOLS_MASK;
		if (next_tail != glob_recycler.head) {
			struct sk_buff_head *p = &glob_recycler.pool[cur_tail];

			/* Move SKBs from CPU pool to Global pool*/
			skb_queue_splice_init(h, p);

			/* Done with global list init */
			glob_recycler.tail = next_tail;
			spin_unlock(&glob_recycler.lock);

			/* We have now cleared room in the spare;
			 * Intialize and enqueue skb into spare
			 */
			__skb_queue_head(h, skb);

			local_irq_restore(flags);
			preempt_enable();
			return true;
		}
		/* We still have a full spare because the global is also full */
		spin_unlock(&glob_recycler.lock);
	} else {
		/* We have room in the spare list; enqueue to spare list */
		__skb_queue_head(h, skb);
		local_irq_restore(flags);
		preempt_enable();
		return true;
	}
#endif

	local_irq_restore(flags);
	preempt_enable();

	return false;
}

static void skb_recycler_free_skb(struct sk_buff_head *list)
{
	struct sk_buff *skb = NULL;

	while ((skb = skb_dequeue(list)) != NULL) {
		trace_consume_skb(skb);
		skb_release_data(skb);
		kfree_skbmem(skb);
	}
}

static int skb_cpu_callback(struct notifier_block *nfb,
		unsigned long action, void *ocpu)
{
	unsigned long oldcpu = (unsigned long)ocpu;

	if (action == CPU_DEAD || action == CPU_DEAD_FROZEN) {
		skb_recycler_free_skb(&per_cpu(recycle_list, oldcpu));
#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
		spin_lock(&glob_recycler.lock);
		skb_recycler_free_skb(&per_cpu(recycle_spare_list, oldcpu));
		spin_unlock(&glob_recycler.lock);
#endif
	}

	return NOTIFY_OK;
}

/* procfs: count
 */
static int proc_skb_count_show(struct seq_file *seq, void *v)
{
	int cpu;
	int len;
	int total;
#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	unsigned int i;
#endif

	total = 0;

	for_each_online_cpu(cpu) {
		len = skb_queue_len(&per_cpu(recycle_list, cpu));
		seq_printf(seq, "recycle_list[%d]: %d\n", cpu, len);
		total += len;
	}

#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	for_each_online_cpu(cpu) {
		len = skb_queue_len(&per_cpu(recycle_spare_list, cpu));
		seq_printf(seq, "recycle_spare_list[%d]: %d\n", cpu, len);
		total += len;
	}

	spin_lock(&glob_recycler.lock);
	for (i = 0; i < SKB_RECYCLE_MAX_SHARED_POOLS; i++) {
		len = skb_queue_len(&glob_recycler.pool[i]);
		seq_printf(seq, "global_list[%d]: %d\n", i, len);
		total += len;
	}
	spin_unlock(&glob_recycler.lock);
#endif

	seq_printf(seq, "total: %d\n", total);
	return 0;
}

static int proc_skb_count_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_skb_count_show, PDE(inode)->data);
}

static const struct file_operations proc_skb_count_fops = {
	.owner   = THIS_MODULE,
	.open    = proc_skb_count_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

/* procfs: flush
 */
static void skb_recycler_flush_task(struct work_struct *work)
{
	unsigned long flags;
	struct sk_buff_head *h;
	struct sk_buff_head tmp;

	skb_queue_head_init(&tmp);

	h = &get_cpu_var(recycle_list);
	local_irq_save(flags);
	skb_queue_splice_init(h, &tmp);
	local_irq_restore(flags);
	put_cpu_var(recycle_list);
	skb_recycler_free_skb(&tmp);

#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	h = &get_cpu_var(recycle_spare_list);
	local_irq_save(flags);
	skb_queue_splice_init(h, &tmp);
	local_irq_restore(flags);
	put_cpu_var(recycle_spare_list);
	skb_recycler_free_skb(&tmp);
#endif
}

static ssize_t proc_skb_flush_write(struct file *file,
				    const char __user *buf,
				    size_t count,
				    loff_t *ppos)
{
#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	unsigned int i;
	unsigned long flags;
#endif
	schedule_on_each_cpu(&skb_recycler_flush_task);

#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	spin_lock_irqsave(&glob_recycler.lock, flags);
	for (i = 0; i < SKB_RECYCLE_MAX_SHARED_POOLS; i++)
		skb_recycler_free_skb(&glob_recycler.pool[i]);
	glob_recycler.head = 0;
	glob_recycler.tail = 0;
	spin_unlock_irqrestore(&glob_recycler.lock, flags);
#endif
	return count;

}

static const struct file_operations proc_skb_flush_fops = {
	.owner   = THIS_MODULE,
	.write   = proc_skb_flush_write,
	.open    = simple_open,
	.llseek  = noop_llseek,
};

/* procfs: max_skbs
 */
static int proc_skb_max_skbs_show(struct seq_file *seq, void *v)
{
	return seq_printf(seq, "%d\n", skb_recycle_max_skbs);
}

static int proc_skb_max_skbs_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_skb_max_skbs_show, PDE(inode)->data);
}

static ssize_t proc_skb_max_skbs_write(struct file *file,
				       const char __user *buf,
				       size_t count,
				       loff_t *ppos)
{
	int ret;
	int max;
	char buffer[PROC_NUMBUF];

	memset(buffer, 0, sizeof(buffer));
	if (count > sizeof(buffer) - 1)
		count = sizeof(buffer) - 1;
	if (copy_from_user(buffer, buf, count) != 0)
		return -EFAULT;
	ret = kstrtoint(strstrip(buffer), 10, &max);
	if (ret == 0 && max >= 0)
		skb_recycle_max_skbs = max;

	return count;
}

static const struct file_operations proc_skb_max_skbs_fops = {
	.owner   = THIS_MODULE,
	.open    = proc_skb_max_skbs_open,
	.read    = seq_read,
	.write   = proc_skb_max_skbs_write,
	.release = single_release,
};

#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
/* procfs: max_spare_skbs
 */
static int proc_skb_max_spare_skbs_show(struct seq_file *seq, void *v)
{
	return seq_printf(seq, "%d\n", skb_recycle_spare_max_skbs);
}

static int proc_skb_max_spare_skbs_open(struct inode *inode, struct file *file)
{
	return single_open(file,
			   proc_skb_max_spare_skbs_show,
			   PDE(inode)->data);
}

static ssize_t
proc_skb_max_spare_skbs_write(struct file *file,
			      const char __user *buf,
			      size_t count,
			      loff_t *ppos)
{
	int ret;
	int max;
	char buffer[PROC_NUMBUF];

	memset(buffer, 0, sizeof(buffer));
	if (count > sizeof(buffer) - 1)
		count = sizeof(buffer) - 1;
	if (copy_from_user(buffer, buf, count) != 0)
		return -EFAULT;
	ret = kstrtoint(strstrip(buffer), 10, &max);
	if (ret == 0 && max >= 0)
		skb_recycle_spare_max_skbs = max;

	return count;
}

static const struct file_operations proc_skb_max_spare_skbs_fops = {
	.owner   = THIS_MODULE,
	.open    = proc_skb_max_spare_skbs_open,
	.read    = seq_read,
	.write   = proc_skb_max_spare_skbs_write,
	.release = single_release,
};
#endif /* CONFIG_SKB_RECYCLER_MULTI_CPU */

static void skb_recycler_init_procfs(void)
{
	proc_net_skbrecycler = proc_mkdir("skb_recycler", init_net.proc_net);
	if (!proc_net_skbrecycler) {
		pr_err("cannot create skb_recycle proc dir");
		return;
	}

	if (!proc_create("count",
			 S_IRUGO,
			 proc_net_skbrecycler,
			 &proc_skb_count_fops))
		pr_err("cannot create proc net skb_recycle held\n");

	if (!proc_create("flush",
			 S_IWUGO,
			 proc_net_skbrecycler,
			 &proc_skb_flush_fops))
		pr_err("cannot create proc net skb_recycle flush\n");

	if (!proc_create("max_skbs",
			 S_IRUGO | S_IWUGO,
			 proc_net_skbrecycler,
			 &proc_skb_max_skbs_fops))
		pr_err("cannot create proc net skb_recycle max_skbs\n");

#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	if (!proc_create("max_spare_skbs",
			 S_IRUGO | S_IWUGO,
			 proc_net_skbrecycler,
			 &proc_skb_max_spare_skbs_fops))
		pr_err("cannot create proc net skb_recycle max_spare_skbs\n");
#endif
}

void __init skb_recycler_init() {
	int cpu;

	for_each_possible_cpu(cpu) {
		skb_queue_head_init(&per_cpu(recycle_list, cpu));
	}

#ifdef CONFIG_SKB_RECYCLER_MULTI_CPU
	for_each_possible_cpu(cpu) {
		skb_queue_head_init(&per_cpu(recycle_spare_list, cpu));
	}

	spin_lock_init(&glob_recycler.lock);
	{
		unsigned int i;
		for (i = 0; i < SKB_RECYCLE_MAX_SHARED_POOLS; i++) {
			skb_queue_head_init(&glob_recycler.pool[i]);
		}
		glob_recycler.head = 0;
		glob_recycler.tail = 0;
	}
#endif

	hotcpu_notifier(skb_cpu_callback, 0);
	skb_recycler_init_procfs();
}
