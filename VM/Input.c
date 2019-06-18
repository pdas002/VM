/*
 * Functions used to receive input and parse it.
 *
 *
 *      Author: Prangon Das (pcd3897@g.rit.edu)
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "input.h"

#define MAX_MNEMONIC 200

/**
 * Receives input from user one letter at a time and dynamically creates strings.
 * Params: buff - GUI text buffer to receive chars from
 * 		   len - max len that any input should have
 * 		   isMnemonic - 1/0 depending if its the first part of the instr or the second part
 */
char* getInput(GtkTextBuffer* buff, int len, int isMnemonic) {

	/* Init the array with a string terminator, \0 */
	char* instrPart = malloc(sizeof(char));

	if (instrPart == NULL) {
		return NULL;
	} else {
		instrPart[0] = '\0';
	}

	char* tmpName;
	char c;

	if (isMnemonic == TRUE) {
		gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff), "> ", 2);
	}

	/* Loop and get chars */
	for (int i = 0; i < len; i++) {

		/* Go into a blocked loop and get char */
		gtk_main();
		//exits to here if input happened
		GtkTextIter start;
		gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(buff), &start, -1);
		gtk_text_iter_backward_char(&start);
		c = gtk_text_iter_get_char(&start);

		if (isMnemonic == TRUE) { // First part of instr
			if (c == ' ' || (c == '\n' && i != 0)) { //User says they finished  or messed up by pressing enter before full instruction
				return instrPart;
			}
			if (c == '\n' && i == 0) {
				tmpName = realloc(instrPart, 5 * sizeof(char));
				if (tmpName == NULL) {
					printf("\nExiting!!");
					free(instrPart);
					exit(0);
				} else {
					instrPart = tmpName;
				}
				strcpy(instrPart, "Done");
				return instrPart;
			}
		} else {
			if (c == '\n') {
				return instrPart;
			}
		}
		/* If it gets to this part then the string must be made bigger by realloc */
		instrPart[i] = c;
		tmpName = realloc(instrPart, (i + 2) * sizeof(char));
		if (tmpName == NULL) {
			printf("\nExiting!!");
			free(instrPart);
			exit(0);
		} else {
			instrPart = tmpName; // the reallocation succeeded, we can overwrite our original pointer now
			instrPart[i + 1] = '\0';
		}
	}
	free(tmpName);
	return instrPart;
}

/*
 * Function to get input and parse it to create instructions.
 * Params: buff - the text view buffer
 */
struct INSTRUCTION* handleInput(GtkTextBuffer* buff) {

	struct INSTRUCTION* Instruct = malloc(sizeof(struct INSTRUCTION)); // empty instruction struct pointer
	if (Instruct == NULL) {
		fprintf(stderr, "CAN'T ALLOC MEM\n");
		exit(0);
	}
	unsigned int rs, rt, rd, imm;

	char* Name = getInput(buff, MAX_MNEMONIC, TRUE); //Get first part of instr
	/* Check if first part is done or messed up */
	if ((strcmp(Name, "Done") == 0)) {
		Instruct->type = D; //Done with instrs type
		free(Name);
		return Instruct;
	} else if (Name == NULL) {
		fprintf(stderr, "CAN'T ALLOC MEM\n");
		exit(0);
	}

	char* operat = getInput(buff, MAX_MNEMONIC, FALSE); //Get second part of instr

	/* Based on name check the format of the second part and then set the instr struct with the values from input*/
	if ((strcmp(Name, "ADDI") == 0)) {
		if (sscanf(operat, "$%d,$%d,%d", &rt, &rs, &imm) != 3) {
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff),
					"Wrong Format...\n", 16);
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = ADDI;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	} else if ((strcmp(Name, "ANDI") == 0)) {
		if (sscanf(operat, "$%d,$%d,%d", &rt, &rs, &imm) != 3) {
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff),
					"Wrong Format...\n", 16);
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = ANDI;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	} else if ((strcmp(Name, "SW") == 0)) {
		if (sscanf(operat, "$%d, %d($%d)", &rt, &imm, &rs) != 3) {
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff),
					"Wrong Format...\n", 16);
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = SW;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	} else if ((strcmp(Name, "LW") == 0)) {
		if (sscanf(operat, "$%d, %d($%d)", &rt, &imm, &rs) != 3) {
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff),
					"Wrong Format...\n", 16);
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = LW;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	} else if ((strcmp(Name, "BEQ") == 0)) {
		if (sscanf(operat, "$%d,$%d,%d", &rs, &rt, &imm) != 3) {
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff),
					"Wrong Format...\n", 16);
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = BEQ;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	} else if ((strcmp(Name, "ADD") == 0) || (strcmp(Name, "DIV") == 0)
			|| (strcmp(Name, "MULT") == 0) || (strcmp(Name, "XOR") == 0)
			|| (strcmp(Name, "OR") == 0) || (strcmp(Name, "AND") == 0)) {
		if (sscanf(operat, "$%d,$%d,$%d\n", &rd, &rs, &rt) != 3) {
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff),
					"Wrong Format...\n", 16);
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.RTYPE.OPCODE = RTYPE;
		(*Instruct).Instr.RTYPE.RD = rd;
		(*Instruct).Instr.RTYPE.RS = rs;
		(*Instruct).Instr.RTYPE.RT = rt;
		(*Instruct).Instr.RTYPE.SHAMT = 0;
		(*Instruct).type = R;
		if ((strcmp(Name, "ADD") == 0)) {
			(*Instruct).Instr.RTYPE.FUNCT = ADD;

		} else if ((strcmp(Name, "DIV") == 0)) {
			(*Instruct).Instr.RTYPE.FUNCT = DIV;

		} else if ((strcmp(Name, "MULT") == 0)) {
			(*Instruct).Instr.RTYPE.FUNCT = MULT;

		} else if ((strcmp(Name, "XOR") == 0)) {
			(*Instruct).Instr.RTYPE.FUNCT = XOR;

		} else if ((strcmp(Name, "OR") == 0)) {
			(*Instruct).Instr.RTYPE.FUNCT = OR;

		} else if ((strcmp(Name, "AND") == 0)) {
			(*Instruct).Instr.RTYPE.FUNCT = AND;

		}
	} else { //Wrong name for instr
		gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buff),
				"Instruction Not Currently Supported. Enter another!\n", -1);
		free(Name);
		free(Instruct);
		free(operat);
		return NULL;
	}
	free(Name);
	free(operat);
	return Instruct;
}

