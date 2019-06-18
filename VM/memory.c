/*
 * Functionality related to the "memory".
 *
 * Author: Prangon Das (pcd3897@g.rit.edu)
 */


#include <stdlib.h>
#include <stdio.h>

/*
 * Allocate an array of size 100 that holds unsigned int elements.
 * Params: None.
 */
unsigned int* createMem(){
	return malloc(100*sizeof(unsigned int));
}

/*
 * Read the array contents at a location
 * Params: memory - array of unsigned ints
 * 		   add - the index to read at
 */
unsigned int load( unsigned int* memory, unsigned int add){
	return memory[add];
}
/*
 * Set the array location to a val
 * Params: memory - array of unsigned ints
 * 		   add - the index
 * 		   val - the value to insert
 */
void store( unsigned int* memory, unsigned int add,  unsigned int val){
	memory[add] = val;
}
