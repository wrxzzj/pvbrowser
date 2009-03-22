#ifndef __PVB_UI_H__
#define __PVB_UI_H__
#include "pvb-types.h"

typedef struct _pvb_ui pvb_ui_t;

pvb_ui_t *pvb_ui_new(GtkWidget *window);
void pvb_ui_free(pvb_ui_t *ui);

GtkWidget *pvb_ui_create(pvb_ui_t *ui);
#endif
