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
#define D 2

typedef enum{
	RTYPE = 0x00,
	ADDI = 0x08,
	ANDI = 0x0C,
	LW = 0x23,
	SW = 0x2B,
	BEQ = 0x04,
} OPCODE;

typedef enum{
	ADD = 0x20,
	DIV = 0x1A,
	MULT = 0x18,
	XOR = 0x26,
	OR = 0x25,
	AND = 0x24
} FUNCTION;

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
