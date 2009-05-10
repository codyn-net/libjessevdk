
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	jessevdk-os-@JESSEVDK_OS_API_VERSION@.pc

jessevdk-os-@JESSEVDK_OS_API_VERSION@.pc: jessevdk-os.pc
	cp jessevdk-os.pc jessevdk-os-@JESSEVDK_OS_API_VERSION@.pc

EXTRA_DIST = \
	jessevdk-os.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
