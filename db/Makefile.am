
include Makefile.am.inc
	
# pkg-config stuff
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	libjessevdk-db-@LIBJESSEVDK_DB_API_VERSION@.pc

libjessevdk-db-@LIBJESSEVDK_DB_API_VERSION@.pc: libjessevdk-db.pc
	cp libjessevdk-db.pc libjessevdk-db-@LIBJESSEVDK_DB_API_VERSION@.pc

EXTRA_DIST = \
	libjessevdk-db.pc.in

CLEANFILES = \
	$(pkgconfig_DATA)
