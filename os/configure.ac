AC_INIT(libjessevdk-os, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

LIBJESSEVDK_OS_API_VERSION=0.1
AC_SUBST(LIBJESSEVDK_OS_API_VERSION)

pkgincludedir="$includedir/libjessevdk-$LIBJESSEVDK_OS_API_VERSION/os"
AC_SUBST(pkgincludedir)

pkgbasedir=""
AC_SUBST(pkgbasedir)

PKG_CHECK_MODULES(PACKAGE_OS, [
	libjessevdk-base-0.1
	glibmm-2.4
])

AC_SUBST(PACKAGE_OS_CFLAGS)
AC_SUBST(PACKAGE_OS_LIBS)

AC_OUTPUT(
Makefile
Environment/Makefile
Fifo/Makefile
FileDescriptor/Makefile
FileSystem/Makefile
Module/Makefile
Pipe/Makefile
Signals/Makefile

libjessevdk-os.pc
)
