/*
 * GUI.c
 *
 *  Created on: Jun 10, 2019
 *      Author: incinv
 */


#include <gtk/gtk.h>
#include  <gdk/gdkkeysyms.h>



void handleBuff(){
	if(gtk_main_level () != 0){
		fprintf(stderr, "Press");
		gtk_main_quit();
	}
}

void handlePlay(GtkButton *button, gpointer user_data){
	fprintf(stderr, "bet");
	gtk_widget_set_visible (gtk_grid_get_child_at (GTK_GRID(user_data), 1, 1), FALSE);
	if(gtk_main_level () != 0){
		fprintf(stderr, "Play");
		gtk_main_quit();
	}
}

void handleStep(){
	if(gtk_main_level () != 0){
		fprintf(stderr, "Step");
		gtk_main_quit();
	}
}

GtkWidget*
startGUI(int    argc,
      char **argv)
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "VMWindow.glade", NULL);


    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "gui.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
							   GTK_STYLE_PROVIDER(cssProvider),
							   GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	GtkWidget* grid = gtk_bin_get_child(GTK_BIN(window));
    g_signal_connect (G_OBJECT (gtk_text_view_get_buffer (GTK_TEXT_VIEW(gtk_bin_get_child(GTK_BIN(gtk_grid_get_child_at (GTK_GRID(grid), 0, 2)))))), "notify::text", G_CALLBACK (handleBuff), NULL);
    g_signal_connect (G_OBJECT (gtk_grid_get_child_at (GTK_GRID(grid), 0, 1)), "clicked", G_CALLBACK (handlePlay), grid);
    g_signal_connect (G_OBJECT (gtk_grid_get_child_at (GTK_GRID(grid), 1, 1)), "clicked", G_CALLBACK (handleStep), NULL);
    g_object_unref(builder);
    gtk_widget_show(window);

    return grid;
}


void initRegLabels(unsigned int* regs, GtkWidget* grid ){
	char Hex[10];
	 for(int i = 0; i< 33; i++){
		 if(i == 32){
			 GtkWidget* label = gtk_grid_get_child_at (GTK_GRID(grid), 2, i);
			 gtk_label_set_text (GTK_LABEL(label), "0x0");
		 }else{
			 GtkWidget* label = gtk_grid_get_child_at (GTK_GRID(grid), 2, i);
			 sprintf(Hex, "0x%X", regs[i]);
			 gtk_label_set_text (GTK_LABEL(label), Hex);
		 }
	 }
}

void initTextMessage(GtkWidget* textview){
	GtkTextBuffer* buff = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textview));
	gtk_text_buffer_set_text (GTK_TEXT_BUFFER(buff),
			"Welcome to a MIPS inspired VM!\n"
			"Constraints: For SW, LW => (val(rs) + imm) < 100 and For BEQ, address is which instr to go to starting from 0.\n"
			"Enter Instruction Mnemonic in specific format please (Ex: ADD $1,$2,$3 or\nADD\n$1,$2,$3).\n"
			"Press enter without typing when done.\n",
	                          -1);
}

