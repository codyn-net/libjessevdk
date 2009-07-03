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

libjessevdk-base.pc
)
