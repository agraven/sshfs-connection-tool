AC_PREREQ([2.69])
AC_INIT([SSHFS Connection Tool], [0.0.1], [tobiaspg@member.fsf.org])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/mainfile.c])
AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects -Wno-portability])

AC_PROG_CC
PKG_PROG_PKG_CONFIG

m4_define([gtk_required_version], [3.6])

PKG_CHECK_MODULES([GTK],
                [
                 gtk+-3.0 >= gtk_required_version,
                 glib-2.0
                ]
)

AC_PATH_PROG(GLIB_COMPILE_RESOURCES, glib-compile-resources)

AC_CHECK_HEADER_STDBOOL

AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT

AC_MSG_RESULT([
        sshfs-connection-tool $VERSION
        ========

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}
])
