#include "listview.h"
#include <gtk/gtk.h>

enum {
	LIST_ITEM = 0,
	N_COLUMNS
};

static void init_list(GtkWidget *list)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("List Items", renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

	g_object_unref(store);
}

static void add_to_list(GtkWidget *list, const gchar *str)
{
	GtkListStore *store;
	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

static void on_changed(GtkWidget *widget, gpointer label)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;

	if(gtk_tree_selection_get_selected(
			GTK_TREE_SELECTION(widget), &model, &iter)) {
		gtk_tree_model_get(model, &iter, LIST_ITEM, &value, -1);
		gtk_label_set_text(GTK_LABEL(label), value);
		g_free(value);
	}
}

int listview_main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget *window;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Hello Gtk");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	GtkWidget *vbox;
	vbox = gtk_vbox_new(FALSE, 0);

	GtkWidget *list;
	list = gtk_tree_view_new();
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);
	gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

	GtkWidget *label;
	label = gtk_label_new("");
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

	init_list(list);
	add_to_list(list, "a");
	add_to_list(list, "b");
	add_to_list(list, "c");

	GtkTreeSelection *selection;
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

	g_signal_connect(selection, "changed",
			G_CALLBACK(on_changed), label);

	g_signal_connect(GTK_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	gtk_container_add(GTK_CONTAINER(window), vbox);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
