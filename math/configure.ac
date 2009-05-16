AC_INIT(libjessevdk-math, 0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_CONFIG_MACRO_DIR([m4])
AC_PROG_LIBTOOL

AC_ISC_POSIX
AC_STDC_HEADERS
AC_PROG_CXX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_MAKE_SET

LIBJESSEVDK_MATH_API_VERSION=0.1
AC_SUBST(LIBJESSEVDK_MATH_API_VERSION)

pkgincludedir="$includedir/libjessevdk-$LIBJESSEVDK_MATH_API_VERSION/math"
AC_SUBST(pkgincludedir)

pkgbasedir=""
AC_SUBST(pkgbasedir)

# PKG_CHECK_MODULES(PACKAGE_MATH, [
# ])

AC_ARG_ENABLE([sse],
	AS_HELP_STRING([--enable-sse],[Enable SSE support]),
	[enable_sse=$enableval],
	[enable_sse=no])

if test "$enable_sse" = "yes";
then
	PACKAGE_MATH_CFLAGS="$PACKAGE_MATH_FLAGS -sse2"
fi

AM_CONDITIONAL(ENABLE_SSE, test "$enable_sse" = "yes")

AC_SUBST(PACKAGE_MATH_CFLAGS)
AC_SUBST(PACKAGE_MATH_LIBS)

AC_OUTPUT(
Makefile
sse/Makefile

libjessevdk-math.pc
)
