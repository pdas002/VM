/*
 * GUI.h
 *
 *  Created on: Jun 10, 2019
 *      Author: incinv
 */

#ifndef GUI_H_
#define GUI_H_

GtkWidget* startGUI(int    argc,
	      char **argv);

void initRegLabels(unsigned int* regs, GtkWidget* grid );
void initTextMessage(GtkWidget* textview);


#endif /* GUI_H_ */
