bin_PROGRAMS = bin/sshfs-connection-tool

bin_sshfs_connection_tool_SOURCES = \
	src/mainfile.c \
	src/application.c \
	src/ioext.c \
	src/resources.c \
	src/window.c \
	include/application.h \
	include/ioext.h \
	include/window.h

bin_sshfs_connection_tool_LDADD = \
	$(GTK_LIBS)

bin_sshfs_connection_tool_CFLAGS = \
	$(GTK_CFLAGS) \
	$(AM_CFLAGS) \
	-I$(top_srcdir)/include

EXTRA_DIST = \
	builder
dist-hook:
	rm -f `find $(top_distdir) -name '*~'`

src_resources = $(shell glib-compile-resources --sourcedir=$(top_srcdir)/builder --generate-dependencies $(top_srcdir)/builder/sct.gresource.xml)

BUILT_SOURCES = \
	src/resources.c

CLEANFILES = \
	$(BUILT_SOURCES)

src/resources.c: $(top_srcdir)/builder/sct.gresource.xml $(src_resources)
	glib-compile-resources --target=$(top_builddir)/$@ --sourcedir=$(top_srcdir)/builder --generate-source --c-name sshfs_connection_resources $<
