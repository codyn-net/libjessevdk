AC_INIT(jessevdk-base, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC
AM_PROG_LIBTOOL

AC_PROG_INSTALL
AC_PROG_MAKE_SET

JESSEVDK_BASE_API_VERSION=0.1
AC_SUBST(JESSEVDK_BASE_API_VERSION)

pkgincludedir="$includedir/jessevdk-$JESSEVDK_BASE_API_VERSION/base"
AC_SUBST(pkgincludedir)

pkgbasedir="base"
AC_SUBST(pkgbasedir)

PACKAGE_CFLAGS=
AC_SUBST(PACKAGE_CFLAGS)

AC_OUTPUT(
Makefile
Cloneable/Makefile
String/Makefile
Makefile
Signals/Makefile
Signals/Callback/Makefile
Signals/Signal/Makefile
Signals/CallbackBase/Makefile
Object/Makefile
Properties/Makefile
Properties/Property/Makefile
Random/Makefile
Math/Makefile
jessevdk-base.pc
)
