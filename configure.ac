AC_INIT(libjessevdk, 1.0)

AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_CONFIG_HEADERS(jessevdk/config.hh)
AM_MAINTAINER_MODE
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

LIBJESSEVDK_API_VERSION=1.0
AC_SUBST(LIBJESSEVDK_API_VERSION)

pkgincludedir="$includedir/libjessevdk-$LIBJESSEVDK_API_VERSION/jessevdk"
AC_SUBST(pkgincludedir)

dnl check for osx platform
AC_MSG_CHECKING([for Mac OS X platform])
case "$host" in
  *-*-darwin*)
    platform_osx=yes
    ;;
  *)
    platform_osx=no
    ;;
esac

AC_MSG_RESULT([$platform_osx])
AM_CONDITIONAL(PLATFORM_OSX, test "$platform_osx" = "yes")

LIBJESSEVDK_REQUIRES="glibmm-2.4"

if test "$platform_osx" = "yes"; then
	AC_DEFINE([PLATFORM_OSX],[1],[Defined if platform is Mac OSX])
	
	SQLITE_LIBS="-lsqlite3"
	PKGCONFIG_EXTRA_LIBS="-lsqlite3"
else
	PKG_CHECK_MODULES(SQLITE, [
		sqlite3
	])

	LIBJESSEVDK_REQUIRES="$LIBJESSEVDK_REQUIRES sqlite3"
fi

AC_SUBST(LIBJESSEVDK_REQUIRES)
AC_SUBST(PKGCONFIG_EXTRA_LIBS)

AC_SUBST(SQLITE_CFLAGS)
AC_SUBST(SQLITE_LIBS)

# Check for enabling sse support
AC_ARG_ENABLE([sse],
        AS_HELP_STRING([--enable-sse],[Enable sse support (default: disabled)]),
        [enable_sse=$enableval],
        [enable_sse=no])

if test "x$enable_sse" == "xyes"; then
	AC_DEFINE([JESSEVDK_ENABLE_SSE], [1], [Defined if sse support is enabled])
fi

AM_CONDITIONAL(ENABLE_SSE, test x"$enable_sse" = "xyes")

PKG_CHECK_MODULES(PACKAGE_LIBJESSEVDK, [
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
jessevdk/math/sse/Makefile
jessevdk/network/Makefile
jessevdk/os/Makefile
libjessevdk.pc
)
