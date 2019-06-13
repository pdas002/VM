/*
 * GUI.c
 *
 *  Created on: Jun 10, 2019
 *      Author: incinv
 */


#include <gtk/gtk.h>




int
startGUI(int    argc,
      char **argv)
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "VMWindow.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_builder_connect_signals(builder, NULL);

    if(GTK_IS_BIN(window)) {
        GtkWidget* grid = gtk_bin_get_child(GTK_BIN(window));
        GtkWidget* grid2 = gtk_grid_get_child_at (GTK_GRID(grid), 2, 1);

        GtkWidget* label = gtk_grid_get_child_at (GTK_GRID(grid2), 2, 1);
        gtk_label_set_text (GTK_LABEL(label),
                            "YES!");

    }


    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}

