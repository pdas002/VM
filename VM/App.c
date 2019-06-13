/*
 * App.c
 *
 *  Created on: Jun 4, 2019
 *      Author: incinv
 */

#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "registers.h"
#include "memory.h"
#include "execute.h"
#include "GUI.h"
#define true 1
#define false 0


int main(int    argc, char **argv){

	startGUI(argc, argv);
//
//	printf("Welcome to a MIPS inspired VM!\n");
//	printf("Constraints: For SW, LW => (val(rs) + imm) < 100 and For BEQ, address is which instr to go to starting from  0\n"
//			"Enter Instruction Mnemonic in specific format please (Ex: ADD $1,$2,$3 or\nADD\n$1,$2,$3).\n"
//			"Press enter without typing when done.\n");
//	struct INSTRUCTION** instrsFront = malloc(sizeof(struct INSTRUCTION*));
//	if(instrsFront == NULL){
//			fprintf(stderr, "CAN'T ALLOC MEM\n");
//			exit(0);
//	}
//	struct INSTRUCTION** instrsBack = instrsFront;
//	struct INSTRUCTION** instrsTemp;
//	int instrCount = 0;
//	while(true){
//		struct INSTRUCTION* instr = handleInput(); //Returns NULL if wrong input and instr.type = D if done with instrs
//		if(instr != NULL){
//			if(instr->type == D){
//				free(instr);
//				break;
//			}else{
//				if(instrsBack == instrsFront){
//					*instrsFront = instr;
//					instrsTemp = realloc(instrsFront, (instrCount+2) * sizeof(struct INSTRUCTION*));
//					if (instrsTemp == NULL)
//					{
//						printf("CAN'T ALLOC MEM\n");
//						free(instrsFront);
//						exit(0);
//					}
//					else
//					{
//						instrsFront = instrsTemp;
//						instrsBack = instrsFront + 1; //Point to the vacant spot after last instr
//						instrCount++;
//					}
//				} else{
//					*instrsBack = instr; // Fill vacant spot with new instr
//					int difference = instrsBack - instrsFront;
//					instrsTemp = realloc(instrsFront, (instrCount+2) * sizeof(struct INSTRUCTION*));
//					if (instrsTemp == NULL)
//					{
//						printf("CAN'T ALLOC MEM\n");
//						free(instrsFront);
//						exit(0);
//					}
//					else
//					{
//						instrsFront = instrsTemp;
//						instrsBack = (instrsFront + difference)+1; //Point to the vacant spot after last instr
//						instrCount++;
//					}
//				}
//			}
//
//
//
//		}
//	}
//
//    unsigned int* registers = createRegisters();
//    unsigned int* memory = createMem();
//
//    struct INSTRUCTION** PC = instrsFront;
//    while(PC <= instrsBack){
//    	if((*PC)->type == R){
//    		switch((*PC)->Instr.RTYPE.FUNCT){
//    			case ADD:
//    				editReg(registers, (*PC)->Instr.RTYPE.RD, execute(readReg(registers,(*PC)->Instr.RTYPE.RS), readReg(registers,(*PC)->Instr.RTYPE.RT), ADD));
//    				printf("%d %d %d %d %d:%u\n", (*PC)->Instr.RTYPE.OPCODE, (*PC)->Instr.RTYPE.RS, (*PC)->Instr.RTYPE.RT, (*PC)->Instr.RTYPE.RD, (*PC)->Instr.RTYPE.FUNCT, registers[(*PC)->Instr.RTYPE.RD]  );
//    				break;
//    			case DIV:
//    				editReg(registers, (*PC)->Instr.RTYPE.RD, execute(readReg(registers,(*PC)->Instr.RTYPE.RS), readReg(registers,(*PC)->Instr.RTYPE.RT), DIV));
//    				printf("%d %d %d %d %d:%u\n", (*PC)->Instr.RTYPE.OPCODE, (*PC)->Instr.RTYPE.RS, (*PC)->Instr.RTYPE.RT, (*PC)->Instr.RTYPE.RD, (*PC)->Instr.RTYPE.FUNCT, registers[(*PC)->Instr.RTYPE.RD]  );
//    				break;
//    			case MULT:
//    				editReg(registers, (*PC)->Instr.RTYPE.RD, execute(readReg(registers,(*PC)->Instr.RTYPE.RS), readReg(registers,(*PC)->Instr.RTYPE.RT), MULT));
//    				printf("%d %d %d %d %d:%u\n", (*PC)->Instr.RTYPE.OPCODE, (*PC)->Instr.RTYPE.RS, (*PC)->Instr.RTYPE.RT, (*PC)->Instr.RTYPE.RD, (*PC)->Instr.RTYPE.FUNCT, registers[(*PC)->Instr.RTYPE.RD]  );
//    				break;
//    			case XOR:
//    				editReg(registers, (*PC)->Instr.RTYPE.RD, execute(readReg(registers,(*PC)->Instr.RTYPE.RS), readReg(registers,(*PC)->Instr.RTYPE.RT), XOR));
//    				printf("%d %d %d %d %d:%u\n", (*PC)->Instr.RTYPE.OPCODE, (*PC)->Instr.RTYPE.RS, (*PC)->Instr.RTYPE.RT, (*PC)->Instr.RTYPE.RD, (*PC)->Instr.RTYPE.FUNCT, registers[(*PC)->Instr.RTYPE.RD]  );
//    				break;
//    			case OR:
//    				editReg(registers, (*PC)->Instr.RTYPE.RD, execute(readReg(registers,(*PC)->Instr.RTYPE.RS), readReg(registers,(*PC)->Instr.RTYPE.RT), OR));
//    				printf("%d %d %d %d %d:%u\n", (*PC)->Instr.RTYPE.OPCODE, (*PC)->Instr.RTYPE.RS, (*PC)->Instr.RTYPE.RT, (*PC)->Instr.RTYPE.RD, (*PC)->Instr.RTYPE.FUNCT, registers[(*PC)->Instr.RTYPE.RD]  );
//    				break;
//    			case AND:
//    				editReg(registers, (*PC)->Instr.RTYPE.RD, execute(readReg(registers,(*PC)->Instr.RTYPE.RS), readReg(registers,(*PC)->Instr.RTYPE.RT), AND));
//    				printf("%d %d %d %d %d:%u\n", (*PC)->Instr.RTYPE.OPCODE, (*PC)->Instr.RTYPE.RS, (*PC)->Instr.RTYPE.RT, (*PC)->Instr.RTYPE.RD, (*PC)->Instr.RTYPE.FUNCT, registers[(*PC)->Instr.RTYPE.RD]  );
//    				break;
//    			default:
//    				break;
//    		}
//    		PC++;
//    	}else{
//    		switch((*PC)->Instr.ITYPE.OPCODE){
//    			case ADDI:
//    				editReg(registers, (*PC)->Instr.ITYPE.RT, execute(readReg(registers,(*PC)->Instr.ITYPE.RS), (*PC)->Instr.ITYPE.IMM, ADD));
//    				printf("%d %d %d %d:%u\n", (*PC)->Instr.ITYPE.OPCODE, (*PC)->Instr.ITYPE.RS, (*PC)->Instr.ITYPE.RT, (*PC)->Instr.ITYPE.IMM, registers[(*PC)->Instr.ITYPE.RT]);
//    				PC++;
//    				break;
//    			case ANDI:
//    				editReg(registers, (*PC)->Instr.ITYPE.RT, execute(readReg(registers,(*PC)->Instr.ITYPE.RS), (*PC)->Instr.ITYPE.IMM, ADD));
//    				printf("%d %d %d %d:%u\n", (*PC)->Instr.ITYPE.OPCODE, (*PC)->Instr.ITYPE.RS, (*PC)->Instr.ITYPE.RT, (*PC)->Instr.ITYPE.IMM, registers[(*PC)->Instr.ITYPE.RT]);
//    				PC++;
//    				break;
//    			case LW:
//    				editReg(registers, (*PC)->Instr.ITYPE.RT, load(memory, execute(readReg(registers,(*PC)->Instr.ITYPE.RS), (*PC)->Instr.ITYPE.IMM, ADD)));
//    				printf("%d %d %d %d:%u\n", (*PC)->Instr.ITYPE.OPCODE, (*PC)->Instr.ITYPE.RS, (*PC)->Instr.ITYPE.RT, (*PC)->Instr.ITYPE.IMM, registers[(*PC)->Instr.ITYPE.RT]);
//    				PC++;
//    				break;
//    			case SW:
//    				store(memory, execute(readReg(registers,(*PC)->Instr.ITYPE.RS), (*PC)->Instr.ITYPE.IMM, ADD), readReg(registers,(*PC)->Instr.ITYPE.RT) );
//    				printf("%d %d %d %d:%u\n", (*PC)->Instr.ITYPE.OPCODE, (*PC)->Instr.ITYPE.RS, (*PC)->Instr.ITYPE.RT, (*PC)->Instr.ITYPE.IMM, memory[execute(registers[(*PC)->Instr.ITYPE.RS], (*PC)->Instr.ITYPE.IMM, ADD)]);
//    				PC++;
//    				break;
//    			case BEQ:
//    				printf("%d %d %d %d:%u\n", (*PC)->Instr.ITYPE.OPCODE, (*PC)->Instr.ITYPE.RS, (*PC)->Instr.ITYPE.RT, (*PC)->Instr.ITYPE.IMM, memory[execute(registers[(*PC)->Instr.ITYPE.RS], (*PC)->Instr.ITYPE.IMM, ADD)]);
//    				if(execute(readReg(registers,(*PC)->Instr.ITYPE.RS), ~(readReg(registers,(*PC)->Instr.ITYPE.RT)) +1 , ADD ) == 0){
//    					PC = instrsFront + (*PC)->Instr.ITYPE.IMM;
//    					printf("%p\n", PC);
//    				}else{
//    					printf("f%p\n", PC);
//    					PC++;
//    				}
//    				break;
//    			default:
//    				break;
//    		}
//    	}
//    }
//
//
//	free(instrsFront);
//	free(registers);
//	free(memory);
	return 0;
}

