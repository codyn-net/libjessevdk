INCLUDES = -g -I$(top_srcdir) $(PACKAGE_LIBJESSEVDK_CFLAGS)

noinst_PROGRAMS = signals

signals_SOURCES = signals.cc
signals_LDADD = $(top_builddir)/jessevdk/libjessevdk-@LIBJESSEVDK_API_VERSION@.la
