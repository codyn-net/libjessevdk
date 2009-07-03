AC_INIT(libjessevdk-network, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

LIBJESSEVDK_NETWORK_API_VERSION=0.1
AC_SUBST(LIBJESSEVDK_NETWORK_API_VERSION)

pkgincludedir="$includedir/libjessevdk-$LIBJESSEVDK_NETWORK_API_VERSION/network"
AC_SUBST(pkgincludedir)

pkgbasedir=""
AC_SUBST(pkgbasedir)

PKG_CHECK_MODULES(PACKAGE_NETWORK, [
	libjessevdk-base-0.1
	libjessevdk-os-0.1
	glibmm-2.4
])

AC_SUBST(PACKAGE_NETWORK_CFLAGS)
AC_SUBST(PACKAGE_NETWORK_LIBS)

AC_OUTPUT(
Makefile
network/AddressInfo/Makefile
network/Client/Makefile
network/Server/Makefile
network/Socket/Makefile
network/SocketAddress/Makefile
network/TcpServer/Makefile
network/UdpServer/Makefile
network/UnixServer/Makefile
network/Makefile

libjessevdk-network.pc
)
