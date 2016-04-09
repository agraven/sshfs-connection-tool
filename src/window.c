#include <gtk/gtk.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ioext.h"
#include "application.h"
#include "window.h"
const int DEFAULT_SSH_PORT = 22;
struct _MainAppWindow { GtkApplicationWindow parent; };
struct _MainAppWindowClass { GtkApplicationWindowClass parent_class; };
typedef struct _MainAppWindowPrivate MainAppWindowPrivate;
struct _MainAppWindowPrivate {
	GtkWidget* connect_button;
	GtkWidget* host_entry;
	GtkWidget* remotedir_entry;
	GtkWidget* mountpoint_chooser;
	GtkWidget* legacy_protocol_check;
	GtkWidget* custom_port_check;
	GtkWidget* port_spin_button;
	GtkWidget* other_options_entry;
};

G_DEFINE_TYPE_WITH_PRIVATE(MainAppWindow, main_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void activate_close(GSimpleAction* action, GVariant* parameter, gpointer win) {
	gtk_window_close(win);
}
static GActionEntry win_actions[] = {
	{"close", activate_close, NULL, NULL, NULL},
};
static void clicked_connect(GtkApplication* app, MainAppWindow* win) {
	MainAppWindowPrivate* private = main_app_window_get_instance_private(MAIN_APP_WINDOW(win));
	const gchar* host = gtk_entry_get_text(GTK_ENTRY(private->host_entry));
	const gchar* dir = gtk_entry_get_text(GTK_ENTRY(private->remotedir_entry));
	const gchar* mountpoint = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(private->mountpoint_chooser));
	gboolean legacy_protocol = gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(private->legacy_protocol_check));
	gboolean custom_port = gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(private->custom_port_check));
	gint port = gtk_spin_button_get_value(GTK_SPIN_BUTTON(private->port_spin_button));
	const gchar* other_options = gtk_entry_get_text(GTK_ENTRY(private->other_options_entry));

	char* is_mountpoint_cmd;
	int strsize = msprintf(&is_mountpoint_cmd, "mountpoint -q %s", mountpoint);
	if (strsize != 0 && system(is_mountpoint_cmd) != 0) {
		char* mount_cmd;
		msprintf(&mount_cmd, "sshfs %s:%s %s%s -p %d %s", host, dir, mountpoint,
		  legacy_protocol ? " -1" : "", custom_port ? port : DEFAULT_SSH_PORT, other_options);
		int retval = system(mount_cmd);
		if (retval != 0) {
			GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(win), 
			  GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
			  "Failed to connect. Error code is %d", retval);
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
		}
		free(mount_cmd);
	}
	free(is_mountpoint_cmd);
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
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, legacy_protocol_check);
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, custom_port_check);
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, port_spin_button);
	gtk_widget_class_bind_template_child_private(GTK_WIDGET_CLASS(class), MainAppWindow, other_options_entry);
}
MainAppWindow* main_app_window_new (MainApp *app) {
	return g_object_new (MAIN_APP_WINDOW_TYPE, "application", app, NULL);
}
void main_app_window_open (MainAppWindow *win, GFile* file) {
}
