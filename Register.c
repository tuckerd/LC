// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// Register.c
// This is the Registers that the LC+ used to store data locally in order to operate on the data.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Register.h"

//Constructs the Registers.
RegistersPtr RegistersConstructor(void) {
	RegistersPtr registers = (RegistersPtr) malloc(sizeof(Registers));
	int i;
	for (i = 0; i < 8; i++) {
		registers->registers[i] = 0x0000;
	}
	return registers;
}

//Sets a particular register to the value passed in.
void setRegister(RegistersPtr registers, Register value, int index) {
	registers->registers[index] = value;
}

//Returns the value in a particular register.
Register getRegister(RegistersPtr registers, int index) {
	return registers->registers[index];
}

//Returns the String representation the the Registers.
char * registersToString(RegistersPtr registers) {
	char * string = (char *) malloc(9);
	char * result = (char *) malloc(200);
	char * reg_string = (char *) malloc(9);
	Register  * regs = registers->registers;
	
	int i;
	for (i = 0; i < 8; i++) {
		sprintf(string, "0x%04X\n", regs[i]);
		sprintf(reg_string, "R%d: ", i);
		result = strcat(result, reg_string);
		result = strcat(result, string);
	} 
	return result;
}
/*
int main() {
	RegistersPtr registers = RegistersConstructor();
	setRegister(registers, 0x0022, 0);
	printf("%04X\n", getRegister(registers, 0));
	printf("%s", registersToString(registers));
} */
