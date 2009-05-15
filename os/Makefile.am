
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-os-@LIBJESSEVDK_OS_API_VERSION@.pc

libjessevdk-os-@LIBJESSEVDK_OS_API_VERSION@.pc: libjessevdk-os.pc
	cp libjessevdk-os.pc libjessevdk-os-@LIBJESSEVDK_OS_API_VERSION@.pc

headerdir = $(pkgincludedir)
header_DATA = 	\
	os.hh
	
EXTRA_DIST = \
	$(header_DATA) \
	libjessevdk-os.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
