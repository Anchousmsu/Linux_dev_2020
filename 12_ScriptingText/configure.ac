#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(Library for work with buf, [0.0], [NUT1997020501@yandex.ru])
AM_INIT_AUTOMAKE([foreign])
PKG_CHECK_MODULES([CHECK], [check])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/libbuf.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 tests/Makefile])

AC_ARG_ENABLE([gcov],
	[AS_HELP_STRING([--enable-gcov],
		[use Gcov to test the test suite])],
		[],
		[enable_gcov=no])

AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

AC_OUTPUT

MSG="COMMENT:: $PACKAGE_NAME, $PACKAGE_VERSION: `date`"
echo '/* '$MSG' */'
for i in `grep -l "/* COMMENT::" src/*.h src/*.c` ; do sed -i "s|/* COMMENT::.*| $MSG */|" $i; done
for i in `grep -L "/* COMMENT::" src/*.h src/*.c` ; do sed -i -e "1 s|^|/* $MSG */\n|" $i; done
