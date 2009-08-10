AC_INIT(libjessevdk, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_CONFIG_HEADERS(config.h)
AM_MAINTAINER_MODE

LIBJESSEVDK_API_VERSION=0.1
AC_SUBST(LIBJESSEVDK_API_VERSION)

pkgincludedir="$includedir/libjessevdk-$LIBJESSEVDK_API_VERSION"
AC_SUBST(pkgincludedir)

pkgbasedir=""
AC_SUBST(pkgbasedir)

PKG_CHECK_MODULES(PACKAGE_LIBJESSEVDK, [
	sqlite3
	glibmm-2.4
])

AC_SUBST(PACKAGE_LIBJESSEVDK_CFLAGS)
AC_SUBST(PACKAGE_LIBJESSEVDK_LIBS)

AC_OUTPUT(
Makefile
base/Algorithms/Makefile
base/BinaryStream/Makefile
base/Cloneable/Makefile
base/CommandLine/Makefile
base/Debug/Makefile
base/Enum/Makefile
base/Exceptions/Makefile
base/Flags/Makefile
base/Functional/Makefile
base/Object/Makefile
base/Properties/Property/Makefile
base/Properties/Makefile
base/Signals/Callback/Makefile
base/Signals/CallbackBase/Makefile
base/Signals/Signal/Makefile
base/Signals/Makefile
base/String/Makefile
base/Timer/Makefile
base/Makefile
db/SQLite/Row/Makefile
db/SQLite/Makefile
db/Makefile
math/Random/Makefile
math/sse/Makefile
math/Makefile
network/AddressInfo/Makefile
network/Client/Makefile
network/Server/Makefile
network/Socket/Makefile
network/SocketAddress/Makefile
network/TcpServer/Makefile
network/UdpServer/Makefile
network/UnixServer/Makefile
network/Makefile
os/Environment/Makefile
os/Fifo/Makefile
os/FileDescriptor/Makefile
os/FileSystem/Makefile
os/Module/Makefile
os/Pipe/Makefile
os/Signals/Makefile
os/Makefile

libjessevdk.pc
)
