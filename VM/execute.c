/*
 * Functionality related to the execute stage using ALU
 *
 *
 * Author: Prangon Das (pcd3897@g.rit.edu)
 */

#include "input.h"
#include "execute.h"

/*
 * The add function
 * Params: op1 - first operand
 *  	   op2 - second operand
 */
static unsigned int ADDf(unsigned int op1, unsigned int op2) {
	return op1 + op2;

}

/*
 * The divide function
 * Params: op1 - first operand
 *  	   op2 - second operand
 */
static unsigned int DIVf(unsigned int op1, unsigned int op2) {
	return op1 / op2;
}

/*
 * The mult function
 * Params: op1 - first operand
 *  	   op2 - second operand
 */
static unsigned int MULTf(unsigned int op1, unsigned int op2) {
	return op1 * op2;

}

/*
 * The bitwise xor function
 * Params: op1 - first operand
 *  	   op2 - second operand
 */
static unsigned int XORf(unsigned int op1, unsigned int op2) {
	return op1 ^ op2;
}

/*
 * The bitwise or function
 * Params: op1 - first operand
 *  	   op2 - second operand
 */
static unsigned int ORf(unsigned int op1, unsigned int op2) {
	return op1 | op2;

}

/*
 * The bitwise and function
 * Params: op1 - first operand
 *  	   op2 - second operand
 */
static unsigned int ANDf(unsigned int op1, unsigned int op2) {
	return op1 & op2;

}

/*
 * Executes a function based on operation specified
 * Params: op1 - first operand
 *  	   op2 - second operand
 *  	   operation - the operation to do
 */
unsigned int execute(unsigned int op1, unsigned int op2, int operation) {
	switch (operation) {
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

