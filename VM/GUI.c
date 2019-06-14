/*
 * GUI.c
 *
 *  Created on: Jun 10, 2019
 *      Author: incinv
 */


#include <gtk/gtk.h>



void handleBuff(){
	gtk_main_quit();
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

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_builder_connect_signals(builder, NULL);

	GtkWidget* grid = gtk_bin_get_child(GTK_BIN(window));


    g_object_unref(builder);

    gtk_widget_show(window);

    return grid;
}


void initRegLabels(unsigned int* regs, GtkWidget* grid ){
	char Hex[8];
	 for(int i = 0; i< 32; i++){
		 GtkWidget* label = gtk_grid_get_child_at (GTK_GRID(grid), 2, i);
		 sprintf(Hex, "0x%X", regs[i]);
		 gtk_label_set_text (GTK_LABEL(label), Hex);
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
	//	printf("Welcome to a MIPS inspired VM!\n");
	//	printf("Constraints: For SW, LW => (val(rs) + imm) < 100 and For BEQ, address is which instr to go to starting from  0\n"
	//			"Enter Instruction Mnemonic in specific format please (Ex: ADD $1,$2,$3 or\nADD\n$1,$2,$3).\n"
	//			"Press enter without typing when done.\n");
}

