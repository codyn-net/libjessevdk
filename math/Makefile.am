
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-math-@LIBJESSEVDK_MATH_API_VERSION@.pc

libjessevdk-math-@LIBJESSEVDK_MATH_API_VERSION@.pc: libjessevdk-math.pc
	cp libjessevdk-math.pc libjessevdk-math-@LIBJESSEVDK_MATH_API_VERSION@.pc

EXTRA_DIST += \
	libjessevdk-math.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
