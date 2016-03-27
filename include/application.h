#ifndef APPLICATION_H
#define APPLICATION_H
#define MAIN_APP_TYPE (main_app_get_type ())
#define MAIN_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MAIN_APP_TYPE, MainApp)

typedef struct _MainApp       MainApp;
typedef struct _MainAppClass  MainAppClass;

GType main_app_get_type (void);
MainApp* main_app_new (void);
#endif
