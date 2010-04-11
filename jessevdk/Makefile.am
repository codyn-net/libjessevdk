SUBDIRS = base db math network os

INCLUDES = \
	-I$(srcdir) \
	-I$(builddir) \
	-I$(top_srcdir) \
	-I$(top_builddir) \
	$(PACKAGE_LIBJESSEVDK_CFLAGS) \
	$(SQLITE_CFLAGS) \
	-DDATADIR=\""$(datadir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DCONFDIR=\""$(sysconfdir)"\" \
	-DPREFIXDIR=\""$(prefix)"\" \
	-DPKGDATADIR=\""$(pkgdatadir)"\" \
	-DPKGLIBDIR=\""$(pkglibdir)"\"

lib_LTLIBRARIES = libjessevdk-1.0.la
libjessevdk_1_0_la_CFLAGS = -D_GNU_SOURCE -g $(PACKAGE_LIBJESSEVDK_CFLAGS) $(SQLITE_CFLAGS)

libjessevdk_1_0_la_LDFLAGS = -export-dynamic -no-undefined $(PACKAGE_LIBJESSEVDK_LIBS) $(SQLITE_LIBS)

libjessevdk_1_0_la_SOURCES = \
	base/binarystream.cc \
	base/config.cc \
	base/debug.cc \
	base/object.cc \
	base/properties/properties.cc \
	base/string.cc \
	base/timer.cc \
	db/sqlite/row.cc \
	db/sqlite/sqlite.cc \
	math/math.cc \
	math/sse/float4.cc \
	network/addressinfo.cc \
	network/client.cc \
	network/server.cc \
	network/socketaddress.cc \
	network/socket.cc \
	network/tcpserver.cc \
	network/udpserver.cc \
	network/unixserver.cc \
	os/environment.cc \
	os/fifo.cc \
	os/filedescriptor.cc \
	os/filesystem.cc \
	os/module.cc \
	os/pipe.cc \
	os/processes.cc \
	os/signals.cc \
	os/terminator.cc

headerdir = $(pkgincludedir)/
header_DATA = \
	jessevdk.hh

EXTRA_DIST = \
	$(header_DATA)
