AC_INIT(libjessevdk-base, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

LIBJESSEVDK_BASE_API_VERSION=0.1
AC_SUBST(LIBJESSEVDK_BASE_API_VERSION)

pkgincludedir="$includedir/libjessevdk-$LIBJESSEVDK_BASE_API_VERSION/base"
AC_SUBST(pkgincludedir)

pkgbasedir=""
AC_SUBST(pkgbasedir)

PACKAGE_BASE_CFLAGS=
AC_SUBST(PACKAGE_BASE_CFLAGS)

PACKAGE_BASE_LIBS=
AC_SUBST(PACKAGE_BASE_LIBS)

AC_OUTPUT(
Makefile
Algorithms/Makefile
BinaryStream/Makefile
Cloneable/Makefile
CommandLine/Makefile
Debug/Makefile
Enum/Makefile
Exceptions/Makefile
Flags/Makefile
Functional/Makefile
Object/Makefile
Properties/Property/Makefile
Properties/Makefile
Signals/Callback/Makefile
Signals/CallbackBase/Makefile
Signals/Signal/Makefile
Signals/Makefile
String/Makefile
Timer/Makefile

libjessevdk-base.pc
)
