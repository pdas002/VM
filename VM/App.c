/*
 * The starting point for the application.
 *
 *      Author: Prangon Das (pcd3897@g.rit.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "input.h"
#include "registers.h"
#include "memory.h"
#include "execute.h"
#include "GUI.h"
#define true 1
#define false 0

/*
 * The main method that starts the gui, receives input assembly instructions, makes them into c structs, and then executes them.
 * Uses "registers" and "memory" represented by arrays.
 */
int main(int argc, char **argv) {

	/* Start the GUI */
	GtkWidget* grid = startGUI(argc, argv);
	GtkWidget* innerRegGrid = gtk_grid_get_child_at(GTK_GRID(grid), 6, 1);
	GtkWidget* textView = gtk_bin_get_child(
			GTK_BIN(gtk_grid_get_child_at (GTK_GRID(grid), 0, 2)));

	/* Go into a loop and run the program */
	while (1) {
		/* Initialize the gui */
		gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), TRUE);
		gtk_widget_set_visible(gtk_grid_get_child_at(GTK_GRID(grid), 5, 1),
				FALSE);
		initTextMessage(textView);
		unsigned int* registers = createRegisters(); //Create the registes
		initRegLabels(registers, innerRegGrid);

		/* Create a instruction array */
		struct INSTRUCTION** instrsFront = malloc(sizeof(struct INSTRUCTION*));
		if (instrsFront == NULL) {
			fprintf(stderr, "CAN'T ALLOC MEM\n");
			exit(0);
		}
		struct INSTRUCTION** instrsBack = instrsFront; // Pointers to both the beginning
		struct INSTRUCTION** instrsTemp;			   // and end of array
		int instrCount = 0;
		while (true) {
			struct INSTRUCTION* instr = handleInput( 					//Get the Instruction from input
					gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView))); //Returns NULL if wrong input and instr.type = D if done with instrs
			if (instr != NULL) {
				if (instr->type == D) {
					free(instr);
					break;
				} else {
					if (instrsBack == instrsFront) {
						*instrsFront = instr;
						instrsTemp = realloc(instrsFront,
								(instrCount + 2) * sizeof(struct INSTRUCTION*)); //makes a vacant spot at the end
						if (instrsTemp == NULL) {
							printf("CAN'T ALLOC MEM\n");
							free(instrsFront);
							exit(0);
						} else {
							instrsFront = instrsTemp;
							instrsBack = instrsFront + 1; //Point to the vacant spot after last instr
							instrCount++;
						}
					} else {
						*instrsBack = instr; // Fill vacant spot with new instr
						int difference = instrsBack - instrsFront;
						instrsTemp = realloc(instrsFront,
								(instrCount + 2) * sizeof(struct INSTRUCTION*));
						if (instrsTemp == NULL) {
							printf("CAN'T ALLOC MEM\n");
							free(instrsFront);
							exit(0);
						} else {
							instrsFront = instrsTemp;
							instrsBack = (instrsFront + difference) + 1; //Point to the vacant spot after last instr
							instrCount++;
						}
					}
				}
			}
		}


		/* Done with instructions so show play/step buttons and disable editing on the text*/
		gtk_widget_set_visible(gtk_grid_get_child_at(GTK_GRID(grid), 0, 1),
				TRUE);
		gtk_widget_set_visible(gtk_grid_get_child_at(GTK_GRID(grid), 1, 1),
				TRUE);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), FALSE);

		gtk_main(); //Go into loop to see what the user wants


		unsigned int* memory = createMem(); //Create the memory
		char regText[10];
		struct INSTRUCTION** PC = instrsFront;

		sprintf(regText, "%p", PC);
		gtk_label_set_text(
				GTK_LABEL(
						gtk_grid_get_child_at (GTK_GRID(innerRegGrid), 2, 32)), //Initializes the PC label in the GUI with the first address
				regText);

		/* Loop through the instructions and execute them, store in registers, increment PC and update GUI */
		while (PC < instrsBack) {
			if ((*PC)->type == R) {
				switch ((*PC)->Instr.RTYPE.FUNCT) {
				case ADD:
					editReg(registers, (*PC)->Instr.RTYPE.RD,
							execute(readReg(registers, (*PC)->Instr.RTYPE.RS),
									readReg(registers, (*PC)->Instr.RTYPE.RT),
									ADD));
					break;
				case DIV:
					editReg(registers, (*PC)->Instr.RTYPE.RD,
							execute(readReg(registers, (*PC)->Instr.RTYPE.RS),
									readReg(registers, (*PC)->Instr.RTYPE.RT),
									DIV));
					break;
				case MULT:
					editReg(registers, (*PC)->Instr.RTYPE.RD,
							execute(readReg(registers, (*PC)->Instr.RTYPE.RS),
									readReg(registers, (*PC)->Instr.RTYPE.RT),
									MULT));
					break;
				case XOR:
					editReg(registers, (*PC)->Instr.RTYPE.RD,
							execute(readReg(registers, (*PC)->Instr.RTYPE.RS),
									readReg(registers, (*PC)->Instr.RTYPE.RT),
									XOR));
					break;
				case OR:
					editReg(registers, (*PC)->Instr.RTYPE.RD,
							execute(readReg(registers, (*PC)->Instr.RTYPE.RS),
									readReg(registers, (*PC)->Instr.RTYPE.RT),
									OR));
					break;
				case AND:
					editReg(registers, (*PC)->Instr.RTYPE.RD,
							execute(readReg(registers, (*PC)->Instr.RTYPE.RS),
									readReg(registers, (*PC)->Instr.RTYPE.RT),
									AND));
					//fprintf(stderr,"%d %d %d %d %d:%u\n", (*PC)->Instr.RTYPE.OPCODE, (*PC)->Instr.RTYPE.RS, (*PC)->Instr.RTYPE.RT, (*PC)->Instr.RTYPE.RD, (*PC)->Instr.RTYPE.FUNCT, registers[(*PC)->Instr.RTYPE.RD]  );
					break;
				default:
					break;
				}

				sprintf(regText, "0x%X",
						readReg(registers, (*PC)->Instr.RTYPE.RD));
				gtk_label_set_text(
						GTK_LABEL(
								gtk_grid_get_child_at (GTK_GRID(innerRegGrid), 2, (*PC)->Instr.RTYPE.RD)),
						regText);

				PC++;

				sprintf(regText, "%p", PC);
				gtk_label_set_text(
						GTK_LABEL(
								gtk_grid_get_child_at (GTK_GRID(innerRegGrid), 2, 32)),
						regText);
			} else {
				switch ((*PC)->Instr.ITYPE.OPCODE) {
				case ADDI:
					editReg(registers, (*PC)->Instr.ITYPE.RT,
							execute(readReg(registers, (*PC)->Instr.ITYPE.RS),
									(*PC)->Instr.ITYPE.IMM, ADD));
					PC++;
					break;
				case ANDI:
					editReg(registers, (*PC)->Instr.ITYPE.RT,
							execute(readReg(registers, (*PC)->Instr.ITYPE.RS),
									(*PC)->Instr.ITYPE.IMM, ADD));
					PC++;
					break;
				case LW:
					editReg(registers, (*PC)->Instr.ITYPE.RT,
							load(memory,
									execute(
											readReg(registers,
													(*PC)->Instr.ITYPE.RS),
											(*PC)->Instr.ITYPE.IMM, ADD)));
					PC++;
					break;
				case SW:
					store(memory,
							execute(readReg(registers, (*PC)->Instr.ITYPE.RS),
									(*PC)->Instr.ITYPE.IMM, ADD),
							readReg(registers, (*PC)->Instr.ITYPE.RT));
					PC++;
					break;
				case BEQ:
					//fprintf(stderr,"%d %d %d %d:%u\n", (*PC)->Instr.ITYPE.OPCODE, (*PC)->Instr.ITYPE.RS, (*PC)->Instr.ITYPE.RT, (*PC)->Instr.ITYPE.IMM, memory[execute(registers[(*PC)->Instr.ITYPE.RS], (*PC)->Instr.ITYPE.IMM, ADD)]);
					if (execute(readReg(registers, (*PC)->Instr.ITYPE.RS),
							~(readReg(registers, (*PC)->Instr.ITYPE.RT)) + 1,
							ADD) == 0) {
						PC = instrsFront + (*PC)->Instr.ITYPE.IMM;
					} else {
						PC++;
					}
					break;
				default:
					break;
				}

				sprintf(regText, "0x%X",
						readReg(registers, (*(PC - 1))->Instr.ITYPE.RT));
				gtk_label_set_text(
						GTK_LABEL(
								gtk_grid_get_child_at (GTK_GRID(innerRegGrid), 2, (*(PC-1))->Instr.ITYPE.RT)),
						regText);

				sprintf(regText, "%p", PC);
				gtk_label_set_text(
						GTK_LABEL(
								gtk_grid_get_child_at (GTK_GRID(innerRegGrid), 2, 32)),
						regText);
			}
			if (gtk_widget_is_visible(
					gtk_grid_get_child_at(GTK_GRID(grid), 1, 1))) { //Only wait for step button if its visible
				gtk_main();
			}

		}

		//Cleanup for restart or end
		for (PC = instrsFront; PC < instrsBack; PC++) {
			free(*PC);
		}
		free(instrsFront);
		free(registers);
		free(memory);
		gtk_widget_set_visible(gtk_grid_get_child_at(GTK_GRID(grid), 0, 1),
				FALSE);
		gtk_widget_set_visible(gtk_grid_get_child_at(GTK_GRID(grid), 1, 1),
				FALSE);
		gtk_widget_set_visible(gtk_grid_get_child_at(GTK_GRID(grid), 5, 1),
				TRUE);
		gtk_main();
	}
	return 0;
}

