#include <gtk/gtk.h>
#include "config.h"
#include "application.h"
#include "window.h"

struct _MainApp { GtkApplication parent; };
struct _MainAppClass { GtkApplicationClass parent_class; };

G_DEFINE_TYPE(MainApp, main_app, GTK_TYPE_APPLICATION);

const gchar* authors[] = { 
	"Tobias Graven <tobiaspg@member.fsf.org>",
	NULL
};
static void main_app_init(MainApp* app) {}
static void activate_about(GSimpleAction* action, GVariant* parameter, gpointer app) {
	GList* windows = gtk_application_get_windows(GTK_APPLICATION(app));
	GtkWindow* window;
	if (windows) {
		window = GTK_WINDOW(windows->data);
	}
	gtk_show_about_dialog(window,
		"program-name",   PACKAGE_NAME,
		"version",        PACKAGE_VERSION,
		"authors",        authors,
		"copyright",      "Copyright (C) 2016 Tobias Graven and contributors",
		"license-type",   GTK_LICENSE_GPL_3_0,
		"logo-icon-name", "applications-debugging",
		NULL);
}
static void activate_quit(GSimpleAction* action, GVariant* parameter, gpointer app) {
	g_application_quit(G_APPLICATION(app));
}
static GActionEntry app_actions[] = {
	{ "quit", activate_quit, NULL, NULL, NULL },
	{ "about", activate_about, NULL, NULL, NULL },
};
static void main_app_startup(GApplication* app) {
	G_APPLICATION_CLASS(main_app_parent_class)->startup(app); // Macro required in this function to define startup calls

	GtkBuilder* builder;
	GMenuModel* menu;
	builder = gtk_builder_new_from_resource("/net/tgraven/test/menu.ui"); 
	menu = G_MENU_MODEL(gtk_builder_get_object(builder, "appmenu")); 
	gtk_application_set_menubar(GTK_APPLICATION(app), menu); 
	g_object_unref(builder); 

	/* Assign accelerators/keyboard shortcuts */
	g_action_map_add_action_entries(G_ACTION_MAP(app), app_actions, G_N_ELEMENTS(app_actions), app);
	gtk_application_add_accelerator(GTK_APPLICATION(app), "<Ctrl>q", "app.quit", NULL);
}
static void main_app_activate(GApplication* app) {
	MainAppWindow *window;
	window = main_app_window_new(MAIN_APP(app)));
	gtk_window_present(GTK_WINDOW(window));
}
static void main_app_open(GApplication* app, GFile** filev, gint filec, const gchar* hint) {
	GList* windows;
	MainAppWindow* window;
	int i;
	windows = gtk_application_get_windows(GTK_APPLICATION(app));
	if (windows) {
		window = MAIN_APP_WINDOW(windows->data);
	} else {
		window = main_app_window_new(MAIN_APP(app))); }
	for (i = 0; i < filec; i++) {
		main_app_window_open(window, filev[i]);
		gtk_window_present(GTK_WINDOW(window));
	}
}
void main_app_class_init(MainAppClass* class) {
	/* Links events to respective functions */
	G_APPLICATION_CLASS (class)->startup = main_app_startup;
	G_APPLICATION_CLASS (class)->activate = main_app_activate;
	G_APPLICATION_CLASS (class)->open = main_app_open;
}
MainApp* main_app_new(void) {
	return g_object_new(MAIN_APP_TYPE,
		"application-id", "net.tgraven.test","flags",
		G_APPLICATION_HANDLES_OPEN, NULL);
}

