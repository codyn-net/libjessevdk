AC_INIT(libjessevdk, 1.0)

AM_INIT_AUTOMAKE([subdir-objects])

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

LIBJESSEVDK_API_VERSION=1.0
AC_SUBST(LIBJESSEVDK_API_VERSION)

pkgincludedir="$includedir/libjessevdk-$LIBJESSEVDK_API_VERSION"
AC_SUBST(pkgincludedir)

PKG_CHECK_MODULES(PACKAGE_LIBJESSEVDK, [
	sqlite3
	glibmm-2.4
])

AC_SUBST(PACKAGE_LIBJESSEVDK_CFLAGS)
AC_SUBST(PACKAGE_LIBJESSEVDK_LIBS)

AC_OUTPUT(
Makefile
jessevdk/Makefile
jessevdk/base/Makefile
jessevdk/base/signals/Makefile
jessevdk/base/exceptions/Makefile
jessevdk/base/functional/Makefile
jessevdk/base/properties/Makefile
jessevdk/db/Makefile
jessevdk/db/sqlite/Makefile
jessevdk/math/Makefile
jessevdk/network/Makefile
jessevdk/os/Makefile
libjessevdk.pc
)
