#
# Makefile for libuargp. It is intended for Linux/ELF only.
#

LIBNAME=uargp

VERSION=1.0.1
SONAME_VERSION=1

# CC=gcc   <--- set by makefile
# CFLAGS=-Os -I.  <--- set by makefile
# AR=ar    <--- set by makefile

ARFLAGS=ucvr
MAKEINFO=makeinfo

OWNER=root.root

STATIC_LIB=lib$(LIBNAME).a
BASE_SHARED_LIB=lib$(LIBNAME).so
SHARED_LIB=lib$(LIBNAME).so.$(VERSION)
SONAME_SHARED_LIB=lib$(LIBNAME).so.$(SONAME_VERSION)

TARGETS=$(STATIC_LIB) $(SHARED_LIB)

# Where is include and dir located?
prefix=$(PREFIX)

.c.o:
	$(CC) $(CFLAGS) -c $<
	$(CC) $(CFLAGS) -fPIC -c $< -o pic/$@

SRCS = argp-ba.c argp-fmtstream.c argp-help.c argp-pv.c argp-xinl.c \
	argp-eexst.c argp-fs-xinl.c argp-parse.c argp-pvh.c

OBJS= $(SRCS:.c=.o)

# all lib: pic .depend $(TARGETS) info
all lib: pic .depend $(TARGETS)

$(STATIC_LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(SHARED_LIB): $(OBJS)
	cd pic; \
	$(CC) -shared -o ../$@ -Wl,-soname,$(SONAME_SHARED_LIB) $(OBJS) -lc
	ln -sf $(SHARED_LIB) $(BASE_SHARED_LIB)
pic:
	-if [ ! -d pic ]; then mkdir pic; fi

install: lib install-dirs
	-if [ -f $(prefix)/lib/$(SHARED_LIB) ]; then \
	   mkdir -p $(prefix)/lib/backup; \
	   mv $(prefix)/lib/$(SHARED_LIB) \
		$(prefix)/lib/backup/$(SHARED_LIB).$$$$; \
	fi
	-if [ $(prefix) = "/" ]; then \
	  if [ -x /sbin/ldconfig -o -x /etc/ldconfig ]; then \
	    ldconfig; \
	  fi; \
	  cp -f $(STATIC_LIB) /usr/lib; \
	  cp $(SHARED_LIB) /lib; \
	  rm -f /lib/$(BASE_SHARED_LIB); \
	  rm -f /usr/lib/$(BASE_SHARED_LIB); \
	  ln -s /lib/$(SHARED_LIB) /usr/lib/$(BASE_SHARED_LIB); \
	  cp -f termcap.h /usr/include; \
	  chown $(OWNER) \
		/usr/lib/$(STATIC_LIB) \
		/usr/lib/$(BASE_SHARED_LIB) \
		/usr/include/termcap.h; \
	else \
	  cp -f $(STATIC_LIB) $(prefix)/usr/lib; \
	  rm -f $(prefix)/lib/$(BASE_SHARED_LIB); \
	  cp -f $(SHARED_LIB) $(prefix)/lib; \
	  ln -sf $(SHARED_LIB) $(prefix)/lib/$(SONAME_SHARED_LIB); \
	  ln -sf $(SHARED_LIB) $(prefix)/lib/$(BASE_SHARED_LIB); \
	fi

install-dirs:
	-if [ $(prefix) = "/" ]; then \
	  mkdir -p /usr/lib /usr/include /lib; \
	fi

clean:
	-rm -fr .depend core a.out *.o *.so pic $(TARGETS)

distclean: clean

depend: .depend

.depend: $(SRCS) Makefile
	$(CC) $(CFLAGS) -M $(SRCS) | \
		sed -e 's,^[ 	]*\(.*\.o\)[ 	]*:,\1 pic/\1:,' > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
