
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-network-@LIBJESSEVDK_NETWORK_API_VERSION@.pc

libjessevdk-network-@LIBJESSEVDK_NETWORK_API_VERSION@.pc: libjessevdk-network.pc
	cp libjessevdk-network.pc libjessevdk-network-@LIBJESSEVDK_NETWORK_API_VERSION@.pc

headerdir = $(pkgincludedir)
header_DATA = 	\
	network.hh

EXTRA_DIST = \
	$(header_DATA) \
	libjessevdk-network.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
