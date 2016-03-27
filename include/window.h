#ifndef __MAINAPPWIN_H
#define __MAINAPPWIN_H

#include <gtk/gtk.h>
#include "application.h"

#define MAIN_APP_WINDOW_TYPE (main_app_window_get_type ())
#define MAIN_APP_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MAIN_APP_WINDOW_TYPE, MainAppWindow))

typedef struct _MainAppWindow         MainAppWindow;
typedef struct _MainAppWindowClass    MainAppWindowClass;

GType main_app_window_get_type(void);
MainAppWindow* main_app_window_new(MainApp* app);
void main_app_window_open(MainAppWindow* win, GFile* file);
#endif 
