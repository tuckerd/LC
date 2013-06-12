// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 2 - LC+ Simulator
// Register.h
// This is the header file for Register.c which contains function protypes and macro definitions
// used in the lc+

#define REGISTER_H

#ifndef BIT_MAN
#define BIT_MAN
#include "bit_def.h"
#endif

#ifndef FULL_ADDER_H
#define FULL_ADDER_H
#include "fullAdder.h"
#endif

typedef struct {
	Register registers[8];
} Registers;

typedef Registers * RegistersPtr;

RegistersPtr RegistersConstructor(void);

void setRegister(RegistersPtr registers, Register value, int index);

Register getRegister(RegistersPtr registers, int index);

char * registersToString(RegistersPtr registers);

