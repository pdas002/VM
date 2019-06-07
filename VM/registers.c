
#include <stdlib.h>
#include <stdio.h>
#include "input.h"

unsigned int* createRegisters(){
	unsigned int* registers = calloc(32, sizeof(unsigned int));
	return registers;
}
