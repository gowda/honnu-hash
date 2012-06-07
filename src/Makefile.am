noinst_PROGRAMS = honnuhash p-honnuhash

honnuhash_SOURCES = honnuhash.c
honnuhash_LDADD = $(top_builddir)/lib/libhashmap.la
honnuhash_CFLAGS = -I$(top_srcdir)/lib/

p_honnuhash_SOURCES = p-honnuhash.c
p_honnuhash_LDADD = $(top_builddir)/lib/libhashmap.la
p_honnuhash_CFLAGS = -I$(top_srcdir)/lib/

CLEANFILES =

$(top_builddir)/lib/libhashmap.la:
	$(MAKE) -C $(top_builddir)/lib/ all
