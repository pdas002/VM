/*
 * Header file for GUI.c
 *
 *
 *      Author: Prangon Das(pcd3897@g.rit.edu)
 */

#ifndef GUI_H_
#define GUI_H_
/*
 * Starts the gui using GTK.
 * Params: argc/argv - arguments passed from main for gtk to use
 */
GtkWidget* startGUI(int argc, char **argv);
/*
 * Place 0s in the labels representing register contents
 * Params: regs - the actual registers in memory
 * 		   grid - the inner register grid with the labels
 */
void initRegLabels(unsigned int* regs, GtkWidget* grid);
/*
 * Places initial message into the buffer to read
 * Params: textview - the view with the text
 */
void initTextMessage(GtkWidget* textview);

#endif /* GUI_H_ */
