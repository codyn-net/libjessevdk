SUBDIRS = base db math network os

INCLUDES = \
	-I$(srcdir) \
	-I$(builddir) \
	-I$(top_srcdir) \
	-I$(top_builddir) \
	$(PACKAGE_LIBJESSEVDK_CFLAGS) \
	-DDATADIR=\""$(datadir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DCONFDIR=\""$(sysconfdir)"\" \
	-DPREFIXDIR=\""$(prefix)"\" \
	-DPKGDATADIR=\""$(pkgdatadir)"\" \
	-DPKGLIBDIR=\""$(pkglibdir)"\"

lib_LTLIBRARIES = libjessevdk-1.0.la
libjessevdk_1_0_la_CFLAGS = -D_GNU_SOURCE -g $(PACKAGE_LIBJESSEVDK_CFLAGS)
libjessevdk_1_0_la_LDFLAGS = -export-dynamic -no-undefined $(PACKAGE_LIBJESSEVDK_LIBS)
libjessevdk_1_0_la_SOURCES = \
	base/binarystream.cc \
	base/object.cc \
	base/config.cc \
	base/timer.cc \
	base/string.cc \
	base/debug.cc \
	base/properties/properties.cc \
	db/sqlite/row.cc \
	db/sqlite/sqlite.cc \
	os/filesystem.cc \
	os/pipe.cc \
	os/fifo.cc \
	os/signals.cc \
	os/filedescriptor.cc \
	os/module.cc \
	os/environment.cc \
	network/udpserver.cc \
	network/tcpserver.cc \
	network/socket.cc \
	network/unixserver.cc \
	network/addressinfo.cc \
	network/server.cc \
	network/socketaddress.cc \
	network/client.cc \
	math/math.cc \
	math/sse/float4.cc

headerdir = $(pkgincludedir)/
header_DATA = \
	jessevdk.hh

EXTRA_DIST = \
	$(header_DATA)
