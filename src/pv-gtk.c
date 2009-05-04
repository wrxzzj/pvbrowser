#include "pvb-ui.h"

struct _pvb_ui {
  GtkWidget *window;
  GtkBuilder *builder;
};

static GtkWidget *_create_menubar(pvb_ui_t *ui) {
  GtkWidget *menubar = NULL;
  GtkWidget *menu = NULL;
  GtkWidget *item = NULL;

  menubar = gtk_builder_get_object(ui->builder, "mw-menubar");
  DD("menubar = %x\n", menubar);
  return menubar;
}

static GtkWidget *_create_toolbar(pvb_ui_t *ui) {
  GtkWidget *toolbar = NULL;

  toolbar = gtk_builder_get_object(ui->builder, "mw-toolbar");
  DD("toolbar = %x\n", toolbar);

  return toolbar;
}

static GtkWidget *_create_statusbar(pvb_ui_t *ui) {
  GtkWidget *stabar = NULL;

  stabar = gtk_builder_get_object(ui->builder, "mw-statusbar");
  DD("stabar = %x\n", stabar);

  return stabar;
}

static GtkWidget *_create_lview(pvb_ui_t *ui) {
}

static GtkWidget *_create_rview(pvb_ui_t *ui) {
}

static GtkWidget *_create_mainview(pvb_ui_t *ui) {
  GtkWidget *hpaned = NULL;

  hpaned = gtk_hpaned_new();
  gtk_paned_add1(GTK_PANED(hpaned), _create_lview(ui));
  gtk_paned_add2(GTK_PANED(hpaned), _create_rview(ui));

  return hpaned;
}

pvb_ui_t *pvb_ui_new(GtkWidget *window) {
  pvb_ui_t *ui = NULL;

  ui = g_new0(pvb_ui_t, 1);
  ui->window = window;
}

GtkWidget *pvb_ui_create(pvb_ui_t *ui) {
  GtkWidget *vbox = NULL;

  vbox = gtk_vbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), _create_menubar(ui), FALSE, TRUE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), _create_toolbar(ui), FALSE, TRUE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), _create_mainview(ui), TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), _create_statusbar(ui), FALSE, TRUE, 0);

  return vbox;
}

void pvb_ui_free(pvb_ui_t *ui) {
  gtk_widget_destroy(ui->window);
}

