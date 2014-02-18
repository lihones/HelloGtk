#include "PtWidget.h"
#include <stdio.h>
#include <stdlib.h>

static void pt_widget_init(PtWidget *widget);
static void pt_widget_class_init(PtWidgetClass *klass);
static void pt_widget_realize(GtkWidget *widget);
static void pt_widget_size_request(GtkWidget *widget,
		GtkRequisition *requisition);
static void pt_widget_size_allocate(GtkWidget *widget,
		GtkAllocation *allocation);
static gboolean pt_widget_expose_event(GtkWidget *widget,
		GdkEventExpose *event);
static void pt_widget_paint(GtkWidget *widget);
static void pt_widget_destroy(GtkObject *object);

GtkType pt_widget_get_type()
{
	static GtkType type = 0;
	if(type == 0) {
		static GtkTypeInfo type_info = {
				"pt_widget",
				sizeof(PtWidget),
				sizeof(PtWidgetClass),
				(GtkClassInitFunc)pt_widget_class_init,
				(GtkObjectInitFunc)pt_widget_init,
				NULL,
				NULL,
				(GtkClassInitFunc)NULL
		};
		type = gtk_type_unique(GTK_TYPE_WIDGET, &type_info);
	}
	return type;
}

static void pt_widget_init(PtWidget *widget)
{
	widget->val = 0;
}

static void pt_widget_class_init(PtWidgetClass *klass)
{
	GtkWidgetClass *widget_class;
	GtkObjectClass *object_class;

	widget_class = (GtkWidgetClass*)klass;
	object_class = (GtkObjectClass*)klass;

	widget_class->realize = pt_widget_realize;
	widget_class->size_request = pt_widget_size_request;
	widget_class->size_allocate = pt_widget_size_allocate;
	widget_class->expose_event = pt_widget_expose_event;

	object_class->destroy = pt_widget_destroy;
}

static void pt_widget_realize(GtkWidget *widget)
{
	GdkWindowAttr attr;
	guint attr_mask;

	g_return_if_fail(widget != NULL);
	g_return_if_fail(PT_IS_WIDGET(widget));

	GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);

	attr.window_type = GDK_WINDOW_CHILD;
	attr.x = widget->allocation.x;
	attr.y = widget->allocation.y;
	attr.width = 600;
	attr.height = 800;

	attr.wclass = GDK_INPUT_OUTPUT;
	attr.event_mask = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;

	attr_mask = GDK_WA_X | GDK_WA_Y;

	widget->window = gdk_window_new(
			gtk_widget_get_parent_window(widget),
			&attr,
			attr_mask);
	gdk_window_set_user_data(widget->window, widget);
	widget->style = gtk_style_attach(widget->style, widget->window);
	gtk_style_set_background(widget->style, widget->window, GTK_STATE_NORMAL);
}

static void pt_widget_size_request(GtkWidget *widget,
		GtkRequisition *requisition)
{
	g_return_if_fail(widget != NULL);
	g_return_if_fail(PT_IS_WIDGET(widget));
	g_return_if_fail(requisition != NULL);

	requisition->width = 600;
	requisition->height = 800;
}

static void pt_widget_size_allocate(GtkWidget *widget,
		GtkAllocation *allocation)
{
	g_return_if_fail(widget != NULL);
	g_return_if_fail(PT_IS_WIDGET(widget));
	g_return_if_fail(allocation != NULL);

	widget->allocation = *allocation;

	if(GTK_WIDGET_REALIZED(widget)) {
		gdk_window_move_resize(
				widget->window,
				allocation->x, allocation->y,
				allocation->width, allocation->height
		);
	}
}

static gboolean pt_widget_expose_event(GtkWidget *widget,
		GdkEventExpose *event)
{
	g_return_val_if_fail(widget != NULL, FALSE);
	g_return_val_if_fail(PT_IS_WIDGET(widget), FALSE);
	g_return_val_if_fail(event != NULL, FALSE);

	pt_widget_paint(widget);

	return FALSE;
}

static void pt_widget_paint(GtkWidget *widget)
{
	cairo_t *cr;

	cr = gdk_cairo_create(widget->window);

	cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
	cairo_fill(cr);

	cairo_save(cr);
	cairo_save(cr);

	cairo_translate(cr, 20, 20);
	cairo_set_source_rgb(cr, 1, 1, 0);
	cairo_rectangle(cr, 0, 0, 50, 50);
	cairo_fill(cr);

	cairo_translate(cr, 0, 100);
	cairo_set_line_width(cr, 3);
	cairo_set_source_rgb(cr, 0, 1, 0);
	cairo_rectangle(cr, 0, 0, 50, 50);
	cairo_stroke(cr);

	cairo_translate(cr, 0, 100);
	cairo_move_to(cr, 25, 0);
	cairo_line_to(cr, 50, 25);
	cairo_line_to(cr, 25, 50);
	cairo_line_to(cr, 0, 25);
	cairo_close_path(cr);
	cairo_set_source_rgb(cr, 0, 0, 1);
	cairo_fill(cr);

	cairo_translate(cr, 0, 100);
	cairo_move_to(cr, 0, 0);
	cairo_line_to(cr, 25, 0);
#define U_PI 3.14
	cairo_arc(cr, 25, 25, 25, 270 * U_PI / 180, 0 * U_PI / 180);
//	cairo_close_path(cr);
	cairo_set_source_rgb(cr, 1, 1, 0);
	cairo_stroke(cr);

	cairo_restore(cr);

	cairo_translate(cr, 100, 0);
	cairo_set_source_rgb(cr, 1, 0, 0);
	cairo_rectangle(cr, 0, 0, 50, 50);
	cairo_fill(cr);

	cairo_translate(cr, 0, 100);
	cairo_set_source_rgb(cr, 0, 1, 0);
	char *alphabet = "ABCDEFG";
	cairo_show_text(cr, alphabet);

	cairo_translate(cr, 0, 100);
	cairo_surface_t *image;
	image = cairo_image_surface_create_from_png("res/clip_image.png");
	int w = cairo_image_surface_get_width(image);
	int h = cairo_image_surface_get_height(image);
	cairo_scale(cr, 100.0 / w, 100.0 / h);
	cairo_set_source_surface(cr, image, 0, 0);
	cairo_paint(cr);
	cairo_surface_destroy(image);

	cairo_translate(cr, 0, 100);
	cairo_surface_t *target;
	target = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
	cairo_t *ctx = cairo_create(target);
	cairo_set_source_rgb(ctx, 1, 0, 1);
	cairo_paint(ctx);
	cairo_set_source_surface(cr, target, 0, 0);
	cairo_paint(cr);

	cairo_destroy(cr);
}

static void pt_widget_destroy(GtkObject *object)
{
	g_return_if_fail(object != NULL);
	g_return_if_fail(PT_IS_WIDGET(object));

	//parent destroy
	GtkWidgetClass *klass = (GtkWidgetClass*)gtk_type_class(GTK_TYPE_WIDGET);
	if(GTK_OBJECT_CLASS(klass)->destroy) {
		(GTK_OBJECT_CLASS(klass)->destroy)(object);
	}
}

GtkWidget* pt_widget_new()
{
	return GTK_WIDGET(gtk_type_new(pt_widget_get_type()));
}

int ptwidget_main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget *window;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "pt widget");

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *frame;
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);

	GtkWidget *ptWidget;
	ptWidget = pt_widget_new();
	gtk_fixed_put(GTK_FIXED(frame), ptWidget, 5, 5);

	GtkWidget *label;
	label = gtk_label_new("");
	gtk_fixed_put(GTK_FIXED(frame), label, 5, 100);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
