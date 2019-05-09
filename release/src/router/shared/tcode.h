#ifndef __TCODE_H__
#define __TCODE_H__

#ifdef RTCONFIG_TCODE
struct tcode_nvram_s {
	int model;
	char *odmpid;
	char *tcode;
	char *name;
	char *value;
};

struct tcode_rc_support_s {
	int model;
	char *tcode;
	char *features;
};

struct tcode_location_s {
	int model;
	char *location;
	char *prefix_fmt;
	int idx_base;
	char *ccode_2g;
	char *regrev_2g;	/* non-BRCM model, this maybe NULL */
	char *ccode_5g;		/* For 2.4G model, this should be NULL */
	char *regrev_5g;	/* For 2.4G model, this should be NULL */
	char *ccode_5g_2;	/* For 2.4G model, this should be NULL */
	char *regrev_5g_2;	/* For 2.4G model, this should be NULL */
};

struct tcode_lang_s {
	int model;
	char *odmpid;
	char *tcode;
	char *support_lang;  /* support language list */
	int auto_change;
};

extern struct tcode_nvram_s tcode_nvram_list[];
extern struct tcode_nvram_s tcode_init_nvram_list[];
extern struct tcode_rc_support_s tcode_rc_support_list[];
extern struct tcode_lang_s tcode_lang_list[];

extern char *tcode_default_get(const char *name);

#endif	/* RTCONFIG_TCODE */
#endif	/* !__TCODE_H__ */
