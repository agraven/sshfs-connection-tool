AC_PREREQ([2.69])
AC_INIT([SSHFS Connection Tool], [0.0.1], [tobiaspg@member.fsf.org])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/mainfile.c])
AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects])

AC_PROG_CC
PKG_PROG_PKG_CONFIG

PKG_CHECK_MODULES([GTK], [gtk+-3.0 glib-2.0])
AM_PATH_GTK_3_0([3.10.0])
AC_CHECK_HEADER_STDBOOL

AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
