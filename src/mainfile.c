#include <gtk/gtk.h>
#include "application.h"
#include "window.h"
int main(int argc, char* argv[]) {
	return g_application_run(G_APPLICATION(main_app_new()), argc, argv);
}
