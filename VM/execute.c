/*
 * execute.c
 *
 *  Created on: Jun 7, 2019
 *      Author: incinv
 */

#include "input.h"
static unsigned int ADDf(unsigned int op1, unsigned int op2){
	return op1 + op2;

}

static unsigned int DIVf(unsigned int op1, unsigned int op2){
	return op1 / op2;
}

static unsigned int MULTf(unsigned int op1,unsigned  int op2){
	return op1 * op2;

}

static unsigned int XORf(unsigned int op1,unsigned int op2){
	return op1 ^ op2;
}

static unsigned int ORf(unsigned int op1, unsigned int op2){
	return op1 | op2;

}

static unsigned int ANDf(unsigned int op1, unsigned int op2){
	return op1 & op2;

}


unsigned int execute(unsigned int op1, unsigned int op2, int operation){
	switch (operation){
		case ADD:
			return ADDf(op1, op2);
		case DIV:
			return DIVf(op1, op2);
		case MULT:
			return MULTf(op1, op2);
		case XOR:
			return XORf(op1, op2);
		case OR:
			return ORf(op1, op2);
		case AND:
			return ANDf(op1, op2);
		default:
			return 0;
	}
}


