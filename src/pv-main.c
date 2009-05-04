#include <gtk/gtk.h>
#include "pvb-ui.h"

typedef struct {
  pvb_ui_t *ui;
} pvb_t;

static gboolean pvb_window_closed(GtkWidget *widget, GdkEvent *event, gpointer data) {
  gtk_main_quit();

  return TRUE;
}

int main(int argc, char *argv[]) {
  pvb_t pvb;
  GtkWidget *window = NULL;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "PhotoVideo Browser");
  gtk_container_set_border_width(GTK_CONTAINER(window), 8);
  g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(pvb_window_closed), &pvb);

  pvb.ui = pvb_ui_new(window);
  if(pvb.ui) {
    gtk_container_add(GTK_CONTAINER(window), pvb_ui_create(pvb.ui));
    gtk_widget_show_all(window);

    gtk_main();

    pvb_ui_free(pvb.ui);
  }
}
