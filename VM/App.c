/*
 * App.c
 *
 *  Created on: Jun 4, 2019
 *      Author: incinv
 */

#include <stdlib.h>
#include <stdio.h>
#include "input.h"

#define true 1
#define false 0


int main(){
	struct INSTRUCTION** instrsFront = malloc(sizeof(struct INSTRUCTION*));
	struct INSTRUCTION** instrsBack = instrsFront;
	struct INSTRUCTION** instrsTemp;
	int instrCount = 0;
	while(true){
		struct INSTRUCTION* instr = handleInput(); //Returns NULL if wrong input
		if(instr != NULL){
			if(sizeof(instrsFront) == sizeof(struct INSTRUCTION*)){
				*instrsFront = instr;
				instrsTemp = realloc(instrsFront, (instrCount+2) * sizeof(struct INSTRUCTION*));
				if (instrsTemp == NULL)
				{
					printf("\nExiting!!!");
					free(instrsFront);
					exit(0);
				}
				else
				{
					instrsFront = instrsTemp;
					printf("%d %d %d %d %d", (*instrsFront)->Instr.RTYPE.OPCODE, (*instrsFront)->Instr.RTYPE.RS, (*instrsFront)->Instr.RTYPE.RT, (*instrsFront)->Instr.RTYPE.RD, (*instrsFront)->Instr.RTYPE.FUNCT );
					instrsBack = instrsFront + 1; //Point to the vacant spot after last instr
					instrCount++;
				}
			} else{
				*instrsBack = instr; // Fill vacant spot with new instr
				int difference = instrsBack - instrsFront;
				instrsTemp = realloc(instrsFront, (instrCount+2) * sizeof(struct INSTRUCTION*));
				if (instrsTemp == NULL)
				{
					printf("\nExiting!!!");
					free(instrsFront);
					exit(0);
				}
				else
				{
					instrsFront = instrsTemp;
					instrsBack = (instrsFront + difference)+1; //Point to the vacant spot after last instr
					printf("%d %d %d %d %d", (*(instrsBack-1))->Instr.RTYPE.OPCODE, (*(instrsBack-1))->Instr.RTYPE.RS, (*(instrsBack-1))->Instr.RTYPE.RT, (*(instrsBack-1))->Instr.RTYPE.RD, (*(instrsBack-1))->Instr.RTYPE.FUNCT );
					instrCount++;
				}
			}

		}else{
//			fprintf( stderr, "Bad Instruction...");
//			return 1;
			break;
		}


		//Store in Mem
		//Decode (Registers)
		//Execute/AccessMem
		//WriteBack
	}
	printf("%p", instrsFront);
	for(struct INSTRUCTION** p = instrsFront; p <instrsBack; p++ ){
		if((*p)->type == R){
			printf("%d %d %d %d %d", (*p)->Instr.RTYPE.OPCODE, (*p)->Instr.RTYPE.RS, (*p)->Instr.RTYPE.RT, (*p)->Instr.RTYPE.RD, (*p)->Instr.RTYPE.FUNCT );
		}else{
			printf("%d %d %d %d", (*p)->Instr.ITYPE.OPCODE, (*p)->Instr.ITYPE.RS, (*p)->Instr.ITYPE.RT, (*p)->Instr.ITYPE.IMM);
		}
		printf("%p", p);
		free((*p));
	}
	printf("%p", instrsBack);
	free(instrsFront);
	return 0;
}

