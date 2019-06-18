/*
 * Functionality related to the "registers".
 *
 * Author: Prangon Das (pcd3897@g.rit.edu)
 */

#include <stdlib.h>
#include <stdio.h>

/*
 * Allocate an array of size 32 that holds unsigned int elements.
 * Params: None.
 */
unsigned int* createRegisters(){
	unsigned int* registers = calloc(32, sizeof(unsigned int));
	return registers;
}

/*
 * Set the array location to a val
 * Params: registers - array of unsigned ints
 * 		   reg - the index
 * 		   val - the value to insert
 */
void editReg(unsigned int* registers, unsigned int reg, unsigned int val){
	registers[reg] = val;
}

/*
 * Read the array contents at a location
 * Params: registers - array of unsigned ints
 * 		   reg - the index to read at
 */
unsigned int readReg(unsigned int* registers, unsigned int reg){
	return registers[reg];
}
