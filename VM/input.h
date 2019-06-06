/*
 * input.h
 *
 *  Created on: Jun 4, 2019
 *      Author: incinv
 */

#ifndef INPUT_H_
#define INPUT_H_
#define R 0
#define I 1
#define B 2

struct RTYPE {
	unsigned int OPCODE: 6;
	unsigned int RS: 5;
	unsigned int RT: 5;
	unsigned int RD: 5;
	unsigned int SHAMT: 5;
	unsigned int FUNCT: 6;
};

struct ITYPE {
	unsigned int OPCODE: 6;
	unsigned int RS: 5;
	unsigned int RT: 5;
	unsigned int IMM: 16;
};


union TYPES {
	struct RTYPE RTYPE;
	struct ITYPE ITYPE;
};

struct INSTRUCTION{
	union TYPES Instr;
	int type;
};

struct INSTRUCTION* handleInput();

#endif /* INPUT_H_ */
