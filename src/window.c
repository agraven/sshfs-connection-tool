#include <fcntl.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "application.h"
#include "window.h"
struct _MainAppWindow { GtkApplicationWindow parent; };
struct _MainAppWindowClass { GtkApplicationWindowClass parent_class; };
typedef struct _MainAppWindowPrivate MainAppWindowPrivate;
struct _MainAppWindowPrivate {
	GtkWidget* connect_button;
	GtkWidget* host_entry;
	GtkWidget* remotedir_entry;
	GtkWidget* mountpoint_chooser;
};

G_DEFINE_TYPE_WITH_PRIVATE(MainAppWindow, main_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void activate_close(GSimpleAction* action, GVariant* parameter, gpointer win) {
	gtk_window_close(win);
}
static GActionEntry win_actions[] = {
	{"close", activate_close, NULL, NULL, NULL},
	//{"connect", activate_connect, NULL, NULL, NULL}, //matching function to-be-implemented
};
static void clicked_connect(GtkApplication* app, MainAppWindow* win) {
	MainAppWindowPrivate* private = main_app_window_get_instance_private(MAIN_APP_WINDOW(win));
	const gchar* host = gtk_entry_get_text(GTK_ENTRY(private->host_entry));
	const gchar* dir = gtk_entry_get_text(GTK_ENTRY(private->remotedir_entry));
	const gchar* mountpoint = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(private->mountpoint_chooser));
	g_print("Mounting %s:%s to %s\n", host, dir, mountpoint);
	// Everything from here becomes more and more hack-ish
	int nulldev = open("/dev/null", O_WRONLY);
	long int size = dprintf(nulldev, "mountpoint -q %s", mountpoint) + 1;
	char buf[size];
	snprintf(buf, size, "mountpoint -q %s", mountpoint);
	const char* is_mountpoint_cmd = buf;
	g_print("executed command is '%s'\n", is_mountpoint_cmd);
	if (system(is_mountpoint_cmd) != 0) {
		size = dprintf(nulldev, "sshfs %s:%s %s", host, dir, mountpoint) + 1;
		char buf2[size];
		snprintf(buf2, size, "sshfs %s:%s %s", host, dir, mountpoint);
		close(nulldev);
		const char* mount_cmd = buf2;
		g_print("executed command is '%s'", mount_cmd);
		int retval = system(mount_cmd);
		g_print(" with return value %d\n", retval);
		if (retval != 0) {
			GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(win), 
			  GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
			  "Failed to connect.");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
		}
	}
}
static void main_app_window_init (MainAppWindow *win) {
	gtk_widget_init_template(GTK_WIDGET(win));
	MainAppWindowPrivate* private = main_app_window_get_instance_private(win);

	GtkWidget* connect_button = private->connect_button;
	g_signal_connect(connect_button, "clicked", G_CALLBACK(clicked_connect), win);

	g_action_map_add_action_entries(G_ACTION_MAP(win), win_actions, G_N_ELEMENTS(win_actions), win);
}
static void main_app_window_class_init (MainAppWindowClass *class) {
	gtk_widget_class_set_template_from_resource(GTK_WIDGET_CLASS(class), "/net/tgraven/test/main.ui");
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, host_entry);
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, remotedir_entry);
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, mountpoint_chooser);
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, connect_button);
}
MainAppWindow* main_app_window_new (MainApp *app) {
	return g_object_new (MAIN_APP_WINDOW_TYPE, "application", app, NULL);
}
void main_app_window_open (MainAppWindow *win, GFile* file) {
}
