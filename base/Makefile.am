
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-base-@LIBJESSEVDK_BASE_API_VERSION@.pc

libjessevdk-base-@LIBJESSEVDK_BASE_API_VERSION@.pc: libjessevdk-base.pc
	cp libjessevdk-base.pc libjessevdk-base-@LIBJESSEVDK_BASE_API_VERSION@.pc

headerdir = $(pkgincludedir)
header_DATA = 	\
	base.hh

EXTRA_DIST = \
	$(header_DATA) \
	libjessevdk-base.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
