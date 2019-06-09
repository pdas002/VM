/*
 * memory.c
 *
 *  Created on: Jun 9, 2019
 *      Author: incinv
 */

#include <stdlib.h>
#include <stdio.h>

unsigned int* createMem(){
	return malloc(100*sizeof(int));
}

unsigned int load( unsigned int* memory, unsigned int add){
	return memory[add];
}

void store( unsigned int* memory, unsigned int add,  unsigned int val){
	memory[add] = val;
}
