/*
 * Input.c
 *
 *  Created on: Jun 4, 2019
 *      Author: Prangon Das
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"


#define MAX_MNEMONIC 5
#define MAX_OPCHAR 11



typedef enum{
	RTYPE = 0x00,
	ADDI = 0x08,
	ANDI = 0x0C,
	LW = 0x23,
	SW = 0x2B,
	BEQ = 0x04,
} OPCODE;

typedef enum{
	ADD = 0x20,
	DIV = 0x1A,
	MULT = 0x18,
	XOR = 0x26,
	OR = 0x25,
	AND = 0x24,
	SLL = 0x00,
	SRL = 0x02
} FUNCTION;

struct INSTRUCTION* getInput(){
	char Name[MAX_MNEMONIC+1], operation[MAX_OPCHAR];
	struct INSTRUCTION* Instruct = malloc(sizeof(struct INSTRUCTION));
	unsigned int rs, rt, rd, imm;
	char c;

	printf("Enter Instruction Mnemonic: ");
	for(int i = 0; i< MAX_MNEMONIC; i++){
		c = getchar();
		if(c == ' '){
			break;
		} else{
			Name[i] = c;
		}
	}

	if((strcmp(Name, "ADDI") == 0)){
		fgets(operation, 9, stdin);
		sscanf(operation, "$%d,$%d,%d", &rt, &rs, &imm);
		(*Instruct).Instr.ITYPE.OPCODE = ADDI;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	} else if((strcmp(Name, "ANDI") == 0) ){
		fgets(operation, 9, stdin);
		sscanf(operation, "$%d,$%d,%d", &rt, &rs, &imm);
		(*Instruct).Instr.ITYPE.OPCODE = ANDI;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "SW") == 0) ){
		fgets(operation, 12, stdin);
		sscanf(operation, "$%d, %d($%d)", &rt, &imm, &rs);
		(*Instruct).Instr.ITYPE.OPCODE = SW;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "LW") == 0) ){
		fgets(operation, 12, stdin);
		sscanf(operation, "$%d, %d($%d)", &rt, &imm, &rs);
		(*Instruct).Instr.ITYPE.OPCODE = LW;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "BEQ") == 0) ){
		fgets(operation, 10, stdin);
		sscanf(operation, "$%d,$%d,%d", &rs, &rt, &imm);
		(*Instruct).Instr.ITYPE.OPCODE = BEQ;
		(*Instruct).Instr.ITYPE.IMM = imm;
		(*Instruct).Instr.ITYPE.RS = rs;
		(*Instruct).Instr.ITYPE.RT = rt;
		(*Instruct).type = I;
	}else if((strcmp(Name, "ADD") == 0) || (strcmp(Name, "DIV") == 0) || (strcmp(Name, "MULT") == 0) ||
			(strcmp(Name, "XOR") == 0) || (strcmp(Name, "OR") == 0) || (strcmp(Name, "AND") == 0)){
				fgets(operation, 9, stdin);
				sscanf(operation, "$%d,$%d,$%d", &rd, &rs, &rt);
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
		printf("Instruction Not Currently Supported. Enter another.");
	}
	printf("%s", operation);
	return Instruct;
}









