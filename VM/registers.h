/*
 * registers.h
 *
 *  Created on: Jun 7, 2019
 *      Author: incinv
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

unsigned int* createRegisters();
void editReg(unsigned int* registers, unsigned int reg, unsigned int val);
unsigned int readReg(unsigned int* registers, unsigned int reg);

#endif /* REGISTERS_H_ */
