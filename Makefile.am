
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-@LIBJESSEVDK_API_VERSION@.pc

libjessevdk-@LIBJESSEVDK_API_VERSION@.pc: libjessevdk.pc
	cp libjessevdk.pc libjessevdk-@LIBJESSEVDK_API_VERSION@.pc

EXTRA_DIST += \
	libjessevdk.pc.in

CLEANFILES = \
	$(pkgconfig_DATA)
