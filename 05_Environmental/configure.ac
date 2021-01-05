#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Pcre2 Windows], [0.1], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([Windows.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([ncursesw], [initscr], [], AC_MSG_ERROR[Curses is needed])
AC_CHECK_LIB([pcre2-8], [pcre2_compile_8], [], AC_MSG_ERROR[Pcre2 is needed])

# Checks for header files.
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([ncurses.h], [], AC_MSG_ERROR[No curses.h found])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_ARG_WITH([UTF],
    AS_HELP_STRING([--without-UTF], [Shutdown PCRE2_UCP flag]))

AS_IF([test "x$with_UTF" != "xno"], [
    AC_DEFINE(UTF, [], [PCRE2_UCP flag])
])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
