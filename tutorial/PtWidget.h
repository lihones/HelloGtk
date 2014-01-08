#ifndef __PTWIDGET_H__
#define __PTWIDGET_H__

#include <gtk/gtk.h>
#include <cairo.h>

G_BEGIN_DECLS

typedef struct _PtWidget PtWidget;
typedef struct _PtWidgetClass PtWidgetClass;

#define PT_TYPE_WIDGET (pt_widget_get_type())
#define PT_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), PT_TYPE_WIDGET, PtWidget))
#define PT_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), PT_TYPE_WIDGET, PtWidgetClass))
#define PT_IS_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), PT_TYPE_WIDGET))
#define PT_IS_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), PT_TYPE_WIDGET))
#define PT_WIDGET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), PT_TYPE_WIDGET, PtWidgetClass))

struct _PtWidget {
	GtkWidget widget;
	gint val;
};

struct _PtWidgetClass {
	GtkWidgetClass klass;
};

GtkType pt_widget_get_type();
GtkWidget* pt_widget_new();

int ptwidget_main(int argc, char* argv[]);

G_END_DECLS

#endif
