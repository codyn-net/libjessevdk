
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-os-@LIBJESSEVDK_OS_API_VERSION@.pc

libjessevdk-os-@LIBJESSEVDK_OS_API_VERSION@.pc: libjessevdk-os.pc
	cp libjessevdk-os.pc libjessevdk-os-@LIBJESSEVDK_OS_API_VERSION@.pc

EXTRA_DIST += \
	libjessevdk-os.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
