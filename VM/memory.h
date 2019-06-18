/*
 * Header file for memory.c
 *
 *
 *      Author: Prangon Das (pcd3897@g.rit.edu)
 */

#ifndef MEMORY_H_
#define MEMORY_H_

/*
 * Allocate an array of size 100 that holds unsigned int elements.
 * Params: None.
 */
unsigned int* createMem();
/*
 * Read the array contents at a location
 * Params: memory - array of unsigned ints
 * 		   add - the index to read at
 */
unsigned int load( unsigned int* memory, unsigned int add);
/*
 * Set the array location to a val
 * Params: memory - array of unsigned ints
 * 		   add - the index
 * 		   val - the value to insert
 */
unsigned int store(unsigned int* memory, unsigned int add,  unsigned int val);

#endif /* MEMORY_H_ */
