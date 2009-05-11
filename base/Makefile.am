
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	jessevdk-base-@JESSEVDK_BASE_API_VERSION@.pc

jessevdk-base-@JESSEVDK_BASE_API_VERSION@.pc: jessevdk-base.pc
	cp jessevdk-base.pc jessevdk-base-@JESSEVDK_BASE_API_VERSION@.pc

headerdir = $(pkgincludedir)
header_DATA = 	\
	base.hh

EXTRA_DIST = \
	$(header_DATA) \
	jessevdk-base.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
