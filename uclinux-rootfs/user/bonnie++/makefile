include $(ROOTDIR)/config.arch

all:
	./configure --host=$(MACHINE)-linux large_file=yes
	make -f Makefile

clean distclean:
	[ ! -f Makefile ] || make -f Makefile clean

romfs:
	$(ROMFSINST) -e CONFIG_USER_BONNIEXX_BONNIEXX bonnie++ /bin/bonnie++
	$(ROMFSINST) -e CONFIG_USER_BONNIEXX_BONNIEXX zcav /bin/zcav

.PHONY: all clean distclean romfs
