/*
 * Input.c
 *
 *  Created on: Jun 4, 2019
 *      Author: Prangon Das
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "input.h"


#define MAX_MNEMONIC 50
#define MAX_OPCHAR 18


char* getInput(GtkTextBuffer* buff){

	char* Name = malloc(sizeof(char));
	if(Name == NULL){
		return NULL;
	}
	char* tmpName;
	char c;
	gtk_text_buffer_insert_at_cursor (GTK_TEXT_BUFFER(buff),
	                                 "> ",
	                                  2);
		for(int i = 0; i< MAX_MNEMONIC; i++){
			gtk_main();
			GtkTextIter* iter;
			GtkTextMark* mark= gtk_text_buffer_get_mark (buff,
			                          "insert");
			gtk_text_buffer_get_iter_at_mark (buff,
			                                  iter,
			                                mark);
			c = gtk_text_iter_get_char (iter);
			gtk_text_buffer_insert_at_cursor (GTK_TEXT_BUFFER(buff),
				                                 "g",
				                                  1);
			if(c == '\n' && i == 0){
				tmpName = realloc(Name, 5 * sizeof(char));
				if (tmpName == NULL)
				{
				    printf("\nExiting!!");
				    free(Name);
				    exit(0);
				}
				else
				{
				    Name = tmpName;
				}
				strcpy(Name, "Done");
				return Name;
			}
			if(c == ' ' || ( c == '\n' && i != 0)){ //User says they finished the first part or messed up by pressing enter before full instruction
				break;
			} else{
				Name[i] = (char) c;
				tmpName = realloc(Name, (i+2) * sizeof(char));
				if (tmpName == NULL)
				{
				    printf("\nExiting!!");
				    free(Name);
				    exit(0);
				}
				else
				{
				    Name = tmpName;           // the reallocation succeeded, we can overwrite our original pointer now
				    Name[i+1] = '\0';
				}
			}
		}
		return Name;
}

struct INSTRUCTION* handleInput(GtkTextBuffer* buff){
	char operation[MAX_OPCHAR];
	struct INSTRUCTION* Instruct = malloc(sizeof(struct INSTRUCTION));
	if(Instruct == NULL){
			fprintf(stderr, "CAN'T ALLOC MEM\n");
			exit(0);
	}
	unsigned int rs, rt, rd, imm;

	char* Name = getInput(buff);

	if((strcmp(Name, "Done") == 0)){
		Instruct->type = D; //Done with instrs type
		free(Name);
		return Instruct;
	}else if(Name == NULL){
		fprintf(stderr, "CAN'T ALLOC MEM\n");
		exit(0);
	}
	else if((strcmp(Name, "ADDI") == 0)){
		fgets(operation, MAX_OPCHAR, stdin);
		if(sscanf(operation, "$%d,$%d,%d", &rt, &rs, &imm)  != 3){
			printf("Wrong Format...\n");
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = ADDI;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	} else if((strcmp(Name, "ANDI") == 0) ){
		fgets(operation, MAX_OPCHAR, stdin);
		if(sscanf(operation, "$%d,$%d,%d", &rt, &rs, &imm)  != 3){
			printf("Wrong Format...\n");
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = ANDI;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "SW") == 0) ){
		fgets(operation, MAX_OPCHAR, stdin);
		if(sscanf(operation, "$%d, %d($%d)", &rt, &imm, &rs) != 3){
			printf("Wrong Format...\n");
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = SW;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "LW") == 0) ){
		fgets(operation, MAX_OPCHAR, stdin);
		if(sscanf(operation,"$%d, %d($%d)", &rt, &imm, &rs) != 3){
			printf("Wrong Format...\n");
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = LW;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "BEQ") == 0) ){
		fgets(operation, MAX_OPCHAR, stdin);
		if(sscanf(operation, "$%d,$%d,%d", &rs, &rt, &imm) != 3){
			printf("Wrong Format...\n");
			free(Name);
			free(Instruct);
			return NULL;
		};
		(*Instruct).Instr.ITYPE.OPCODE = BEQ;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "ADD") == 0) || (strcmp(Name, "DIV") == 0) || (strcmp(Name, "MULT") == 0) ||
			(strcmp(Name, "XOR") == 0) || (strcmp(Name, "OR") == 0) || (strcmp(Name, "AND") == 0)){
				fgets(operation, MAX_OPCHAR, stdin);
				if(sscanf(operation, "$%d,$%d,$%d\n", &rd, &rs, &rt) != 3){
					printf("Wrong Format...\n");
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
				if((strcmp(Name, "ADD") == 0)){
					(*Instruct).Instr.RTYPE.FUNCT = ADD;

				}else if((strcmp(Name, "DIV") == 0)){
					(*Instruct).Instr.RTYPE.FUNCT = DIV;

				} else if((strcmp(Name, "MULT") == 0)){
					(*Instruct).Instr.RTYPE.FUNCT = MULT;

				}else if((strcmp(Name, "XOR") == 0)){
					(*Instruct).Instr.RTYPE.FUNCT = XOR;

				}else if((strcmp(Name, "OR") == 0)){
					(*Instruct).Instr.RTYPE.FUNCT = OR;

				}else if((strcmp(Name, "AND") == 0)){
					(*Instruct).Instr.RTYPE.FUNCT = AND;

				}
	} else{
		printf("Instruction Not Currently Supported. Enter another!\n");
		free(Name);
		free(Instruct);
		return NULL;
	}
	free(Name);
	return Instruct;
}







