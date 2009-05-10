
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	jessevdk-base-@JESSEVDK_BASE_API_VERSION@.pc

jessevdk-base-@JESSEVDK_BASE_API_VERSION@.pc: jessevdk-base.pc
	cp jessevdk-base.pc jessevdk-base-@JESSEVDK_BASE_API_VERSION@.pc

EXTRA_DIST = \
	jessevdk-base.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
