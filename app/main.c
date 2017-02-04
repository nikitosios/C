#include <gtk/gtk.h>
#include <stdio.h>

const char title[] = "Application";
const unsigned char border_width = 50;

GtkWidget *window;
GtkWidget *grid;

int code (void)
{
	/* code */
	return 0;
}

int main (int argc, char *argv[])
{
	int ret = 0;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_container_set_border_width(GTK_CONTAINER(window), border_width);
	grid = gtk_grid_new();
	ret = code();
	gtk_container_add(GTK_CONTAINER(window), grid);
	gtk_widget_show_all(window);
	gtk_main();
	return ret;
}

