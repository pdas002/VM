/*
 * Input.c
 *
 *  Created on: Jun 4, 2019
 *      Author: incinv
 */
#include<stdlib.h>
#include<stdio.h>

typedef enum{
	RTYPE = 0x00,
	ADDI = 0x08,
	LW = 0x23,
	SW = 0x2B,
	BEQ = 0x04
} OPCODE;

typedef enum{
	ADD = 0x20,
	DIV = 0x1A,
	MULT = 0x18,
	XOR = 0x26,
	OR = 0x25,
	AND = 0x24,
	SLL = 0x00,
	SRL = 0x02
} FUNCTION;

int* getInput(){
	char Name[5];
	int* operands = malloc(sizeof(int));

	printf("Enter Instruction Mnemonic:");
	fgets(Name, 5, stdin);



}









