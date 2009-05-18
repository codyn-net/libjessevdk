
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-base-@LIBJESSEVDK_BASE_API_VERSION@.pc

libjessevdk-base-@LIBJESSEVDK_BASE_API_VERSION@.pc: libjessevdk-base.pc
	cp libjessevdk-base.pc libjessevdk-base-@LIBJESSEVDK_BASE_API_VERSION@.pc

EXTRA_DIST += \
	libjessevdk-base.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
