
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	jessevdk-network-@JESSEVDK_NETWORK_API_VERSION@.pc

jessevdk-network-@JESSEVDK_NETWORK_API_VERSION@.pc: jessevdk-network.pc
	cp jessevdk-network.pc jessevdk-network-@JESSEVDK_NETWORK_API_VERSION@.pc

EXTRA_DIST = \
	jessevdk-network.pc.in

CLEANFILES = 	\
	$(pkgconfig_DATA)
