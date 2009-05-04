#include "pvb-ui.h"

struct _pvb_ui {
  GtkWidget *window;
};

static GtkWidget *_create_menubar(pvb_ui_t *ui) {
  GtkWidget *menubar = NULL;
  GtkWidget *menu = NULL;
  GtkWidget *item = NULL;

  menubar = gtk_menu_bar_new();

  /**File Menu*/
  menu = gtk_menu_new();
  gtk_menu_set_title(GTK_MENU(menu), _("File"));

  item = gtk_image_menu_new_from_stock(GTK_STOCK_NEW, NULL);
  gtk_image_menu_item_set_use_stock(GTK_IMAGE_MENU_ITEM(item), FALSE);
  gtk_menu_item_set_label(GTK_MENU_ITEM(item), _("New Album"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_new_from_stock(GTK_STOCK_OPEN, NULL);
  gtk_image_menu_item_set_use_stock(GTK_IMAGE_MENU_ITEM(item), FALSE);
  gtk_menu_item_set_label(GTK_MENU_ITEM(item), _("Open Album"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_new_from_stock(GTK_STOCK_SEARCH, NULL);
  gtk_image_menu_item_set_use_stock(GTK_IMAGE_MENU_ITEM(item), FALSE);
  gtk_menu_item_set_label(GTK_MENU_ITEM(item), _("Search"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_new_from_stock(GTK_STOCK_QUIT, NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu);

  /**Edit Menu*/
  menu = gtk_menu_new();
  gtk_menu_set_title(GTK_MENU(menu), _("Edit"));

  item = gtk_image_menu_new_with_label(_("Open by GIMP"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
  item = gtk_image_menu_new_with_label(_("Set as wallpaper"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
  item = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_new_from_stock(GTK_STOCK_PREFERENCES, NULL);
  gtk_image_menu_item_set_use_stock(GTK_IMAGE_MENU_ITEM(item), FALSE);
  gtk_menu_item_set_label(GTK_MENU_ITEM(item), _("Preferences..."));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu);

  /**About Menu*/
  menu = gtk_menu_new();
  gtk_menu_set_title(GTK_MENU(menu), _("Edit"));

  item = gtk_image_menu_new_with_label(_("Contents"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
  item = gtk_image_menu_new_with_label(_("Keyboard shortcuts"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
  item = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

  item = gtk_image_menu_new_from_stock(GTK_STOCK_ABOUT, NULL);
  gtk_image_menu_item_set_use_stock(GTK_IMAGE_MENU_ITEM(item), FALSE);
  gtk_menu_item_set_label(GTK_MENU_ITEM(item), _("About"));
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu);

  return menubar;
}

static GtkWidget *_create_toolbar(pvb_ui_t *ui) {
  GtkWidget *toolbar = NULL;
  GtkToolItem *item = NULL;

  toolbar = gtk_toolbar_new();

  return toolbar;
}

static GtkWidget *_create_statusbar(pvb_ui_t *ui) {
  GtkWidget *stabar = NULL;

  stabar = gtk_statusbar_new();
  gtk_statusbar_set_has_resize_grip(GTK_STATUS_BAR(stabar), TRUE);

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

