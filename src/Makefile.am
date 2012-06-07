noinst_PROGRAMS = honnuhash

honnuhash_SOURCES = honnuhash.c
honnuhash_LDADD = $(top_builddir)/lib/libhashmap.la
honnuhash_CFLAGS = -I$(top_srcdir)/lib/

CLEANFILES =

$(top_builddir)/lib/libhashmap.la:
	$(MAKE) -C $(top_builddir)/lib/ all
