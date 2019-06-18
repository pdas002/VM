/*
 * Functionality related to starting and using the GUI like handling button presses and
 * outputting to the buffer.
 *
 *
 *      Author: Prangon Das(pcd3897@g.rit.edu)
 */

#include <gtk/gtk.h>

/*
 * Handle the user clicking the play button.
 * Params: user_data - pointer to the grid that holds the step button
 */
void handlePlay(gpointer user_data) {
	gtk_widget_set_visible(gtk_grid_get_child_at(GTK_GRID(user_data), 1, 1), //turn step function off
			FALSE);
	if (gtk_main_level() != 0) { //quit the main loop
		gtk_main_quit();
	}
}
/*
 * Quits the main loop.
 */
void quitLoop() {
	if (gtk_main_level() != 0) {
		gtk_main_quit();
	}
}

/*
 * Starts the gui using GTK.
 * Params: argc/argv - arguments passed from main for gtk to use
 */
GtkWidget*
startGUI(int argc, char **argv) {
	GtkBuilder *builder;
	GtkWidget *window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "VMWindow.glade", NULL); // Turn the xml given by glade into a GTKbuilder

	GtkCssProvider *cssProvider = gtk_css_provider_new(); // Allows CSS usage on widgets
	gtk_css_provider_load_from_path(cssProvider, "gui.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
			GTK_STYLE_PROVIDER(cssProvider),
			GTK_STYLE_PROVIDER_PRIORITY_USER);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
	GtkWidget* grid = gtk_bin_get_child(GTK_BIN(window));

	/******* Signals *******/
	g_signal_connect(
			G_OBJECT (gtk_text_view_get_buffer (GTK_TEXT_VIEW(gtk_bin_get_child(GTK_BIN(gtk_grid_get_child_at (GTK_GRID(grid), 0, 2)))))),
			"notify::text", G_CALLBACK (quitLoop), NULL);
	g_signal_connect(G_OBJECT (gtk_grid_get_child_at (GTK_GRID(grid), 0, 1)),
			"clicked", G_CALLBACK (handlePlay), grid);
	g_signal_connect(G_OBJECT (gtk_grid_get_child_at (GTK_GRID(grid), 1, 1)),
			"clicked", G_CALLBACK (quitLoop), NULL);
	g_signal_connect(G_OBJECT (gtk_grid_get_child_at (GTK_GRID(grid), 5, 1)),
			"clicked", G_CALLBACK (quitLoop), NULL);


	g_object_unref(builder); //Created a new builder so unref it
	gtk_widget_show(window);

	return grid;
}

/*
 * Place 0s in the labels representing register contents
 * Params: regs - the actual registers in memory
 * 		   grid - the inner register grid with the labels
 */
void initRegLabels(unsigned int* regs, GtkWidget* grid) {
	char Hex[10]; // holder for label string

	for (int i = 0; i < 33; i++) {
		if (i == 32) {
			GtkWidget* label = gtk_grid_get_child_at(GTK_GRID(grid), 2, i);
			gtk_label_set_text(GTK_LABEL(label), "0x0");
		} else {
			GtkWidget* label = gtk_grid_get_child_at(GTK_GRID(grid), 2, i);
			sprintf(Hex, "0x%X", regs[i]); 		//Print in hex format
			gtk_label_set_text(GTK_LABEL(label), Hex);
		}
	}
}

/*
 * Places initial message into the buffer to read
 * Params: textview - the view with the text
 */
void initTextMessage(GtkWidget* textview) {
	GtkTextBuffer* buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buff),
			"Welcome to a MIPS inspired VM!\n"
					"Constraints: For SW, LW => (val(rs) + imm) < 100 and For BEQ, address is which instr to go to starting from 0.\n"
					"Enter Instruction Mnemonic in specific format please (Ex: ADD $1,$2,$3 or\nADD\n$1,$2,$3). "
					"Allowed instructions: SW, LW, ADD, ADDI, XOR, ANDI, AND, BEQ, OR, MULT and DIV\n"
					"Press enter without typing when done.\n", -1);
}

