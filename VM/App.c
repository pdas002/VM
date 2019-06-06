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
	while(true){
		struct INSTRUCTION* instr = getInput();
		printf("%d %d %d %d %d", (*instr).Instr.RTYPE.OPCODE, (*instr).Instr.RTYPE.RS, (*instr).Instr.RTYPE.RT, (*instr).Instr.RTYPE.RD, (*instr).Instr.RTYPE.FUNCT );
		//Check if its correct
		//Create Instruc Array

		//Store in Mem
		//Decode (Registers)
		//Execute/AccessMem
		//WriteBack
	}
}

