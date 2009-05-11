
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	jessevdk-network-@JESSEVDK_NETWORK_API_VERSION@.pc

jessevdk-network-@JESSEVDK_NETWORK_API_VERSION@.pc: jessevdk-network.pc
	cp jessevdk-network.pc jessevdk-network-@JESSEVDK_NETWORK_API_VERSION@.pc

headerdir = $(pkgincludedir)
header_DATA = 	\
	network.hh

EXTRA_DIST = \
	$(header_DATA) \
	jessevdk-network.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
