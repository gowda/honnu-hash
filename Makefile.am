EXTRA_DIST = autogen.sh COPYING INSTALL README AUTHORS THANKS NEWS

SUBDIRS = src

CLEANFILES =

gitclean: distclean
	find . -name Makefile.in -exec rm -f {} \;
	find . -name Makefile -exec rm -f {} \;
	rm -rf autom4te.cache
	rm -f missing aclocal.m4 config.h.in config.guess config.sub ltmain.sh\
	install-sh configure depcomp
