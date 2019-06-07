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

#define true 1
#define false 0


int main(){
	struct INSTRUCTION** instrsFront = malloc(sizeof(struct INSTRUCTION*));
	if(instrsFront == NULL){
			fprintf(stderr, "CAN'T ALLOC MEM\n");
			exit(0);
	}
	struct INSTRUCTION** instrsBack = instrsFront;
	struct INSTRUCTION** instrsTemp;
	int instrCount = 0;
	while(true){
		struct INSTRUCTION* instr = handleInput(); //Returns NULL if wrong input and instr.type = D if done with instrs
		if(instr != NULL){
			if(instr->type == D){
				free(instr);
				break;
			}else{
				if(instrsBack == instrsFront){
					*instrsFront = instr;
					instrsTemp = realloc(instrsFront, (instrCount+2) * sizeof(struct INSTRUCTION*));
					if (instrsTemp == NULL)
					{
						printf("CAN'T ALLOC MEM\n");
						free(instrsFront);
						exit(0);
					}
					else
					{
						instrsFront = instrsTemp;
						instrsBack = instrsFront + 1; //Point to the vacant spot after last instr
						instrCount++;
					}
				} else{
					*instrsBack = instr; // Fill vacant spot with new instr
					int difference = instrsBack - instrsFront;
					instrsTemp = realloc(instrsFront, (instrCount+2) * sizeof(struct INSTRUCTION*));
					if (instrsTemp == NULL)
					{
						printf("CAN'T ALLOC MEM\n");
						free(instrsFront);
						exit(0);
					}
					else
					{
						instrsFront = instrsTemp;
						instrsBack = (instrsFront + difference)+1; //Point to the vacant spot after last instr
						instrCount++;
					}
				}
			}



		}
	}

    unsigned int* registers = createRegisters();
    instrsTemp = instrsFront;
    while(instrsTemp <= instrsBack){
    	if((*instrsTemp)->type == R){
    		switch((*instrsTemp)->Instr.RTYPE.FUNCT){
    			case ADD:
    				//execute(op1, op2, operation);
    				break;
    			case DIV:
    				break;
    			case MULT:
    				break;
    			case XOR:
    				break;
    			case OR:
    				break;
    			case AND:
    				break;
    			case SLL:
    				break;
    			case SRL:
    				break;
    			default:
    				break;
    		}
    	}else{
    		switch((*instrsTemp)->Instr.ITYPE.OPCODE){
    			case ADDI:
    				break;
    			case ANDI:
    				break;
    			case LW:
    				break;
    			case SW:
    				break;
    			case BEQ:
    				break;
    			default:
    				break;
    		}
    	}
    }

//	printf("%p\n", instrsFront);
//	for(struct INSTRUCTION** p = instrsFront; p <instrsBack; p++ ){
//		if((*p)->type == R){
//			printf("%p\n", p);
//			printf("%d %d %d %d %d\n", (*p)->Instr.RTYPE.OPCODE, (*p)->Instr.RTYPE.RS, (*p)->Instr.RTYPE.RT, (*p)->Instr.RTYPE.RD, (*p)->Instr.RTYPE.FUNCT );
//		}else{
//			printf("%d %d %d %d\n", (*p)->Instr.ITYPE.OPCODE, (*p)->Instr.ITYPE.RS, (*p)->Instr.ITYPE.RT, (*p)->Instr.ITYPE.IMM);
//		}
//		free((*p));
//	}
//	printf("%p\n", instrsBack);

	// Store in Mem
	//Decode (Registers)
	//Execute/AccessMem
	//WriteBack
	free(instrsFront);
	free(registers);
	return 0;
}

