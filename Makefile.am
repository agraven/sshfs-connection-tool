AM_CFLAGS = $(GTK_CFLAGS)
bin_PROGRAMS = bin/sshfs-connection-tool
bin_sshfs_connection_tool_SOURCES = src/mainfile.c \
	src/application.c \
	src/resources.c \
	src/window.c \
	include/application.h \
	include/window.h
bin_sshfs_connection_tool_LDADD = $(GTK_LIBS)
BUILT_SOURCES = src/resources.c
src_resources.c: builder/main.ui builder/menu.ui
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES_) $(srcdir)/builder/test.gresource.xml \
		--target=$@ --sourcedir=$(srcdir)/builder --generate-source
EXTRA_DIST = builder
