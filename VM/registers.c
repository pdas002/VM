
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

unsigned int* createRegisters(){
	unsigned int* registers = calloc(32, sizeof(unsigned int));
	return registers;
}

void editReg(unsigned int* registers, unsigned int reg, unsigned int val){
	registers[reg] = val;
}

unsigned int readReg(unsigned int* registers, unsigned int reg){
	return registers[reg];
}
