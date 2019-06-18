/*
 * Header file for  registers.c
 *
 * Author: Prangon Das (pcd3897@g.rit.edu)
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

/*
 * Allocate an array of size 32 that holds unsigned int elements.
 * Params: None.
 */
unsigned int* createRegisters();

/*
 * Set the array location to a val
 * Params: registers - array of unsigned ints
 * 		   reg - the index
 * 		   val - the value to insert
 */
void editReg(unsigned int* registers, unsigned int reg, unsigned int val);

/*
 * Read the array contents at a location
 * Params: registers - array of unsigned ints
 * 		   reg - the index to read at
 */
unsigned int readReg(unsigned int* registers, unsigned int reg);

#endif /* REGISTERS_H_ */
