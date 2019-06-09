/*
 * memory.h
 *
 *  Created on: Jun 9, 2019
 *      Author: incinv
 */

#ifndef MEMORY_H_
#define MEMORY_H_

unsigned int* createMem();
unsigned int load( unsigned int* memory, unsigned int add);
unsigned int store(unsigned int* memory, unsigned int add,  unsigned int val);

#endif /* MEMORY_H_ */
