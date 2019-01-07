INSTALLKMODDIR:=$(INSTALLDIR)/lib/modules/$(LINUX_KERNEL)/extra
PBBINS=$(wildcard prebuild/*)
SFE_KMOD=$(filter %.ko,$(PBBINS))
SFE_SH=$(filter-out $(SFE_KMOD),$(PBBINS))

all:

install:
	@[ -d $(INSTALLKMODDIR) ] || install -d $(INSTALLKMODDIR)
	@for i in $(SFE_KMOD); do install -D $$i $(INSTALLKMODDIR) ; done
	@$(STRIPX) $(INSTALLKMODDIR)/*.ko
	@[ -d $(INSTALLDIR)/usr/bin ] || install -d $(INSTALLDIR)/usr/bin
	@for i in $(SFE_SH); do install -D $$i $(INSTALLDIR)/usr/bin ; done

clean:

stage:
