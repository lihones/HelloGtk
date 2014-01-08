#include "start.h"
#include <stdio.h>
#include <gtk/gtk.h>

int start_main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);

	GtkWidget *window;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "start");

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show(window);

	gtk_main();

	return 0;
}
