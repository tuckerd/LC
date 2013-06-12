// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 2 - LC+ Simulator
// AlU.h
// This is the header file for the ALU which contains function protypes and macro definitions
// used in the lc+

#define ALU_H

#include <stdio.h>
#include "bit_def.h"
#include "fullAdder.h"

#define DEST 0x0E00
#define BR_N 0x0800
#define BR_Z 0x0400
#define BR_P 0x0200
#define BR_C 0x0100
#define BR_O 0x0080

typedef struct {
	int mask_array[16];
	Register A, B, R;
	Register flags;
	bit c_out;
} ALU;

typedef ALU * ALUPtr;

// prototypes
ALUPtr ALUConstructor(void);
int ALUSetOperands(ALUPtr this, Register A, Register B);
int rippleCarryAdderAdd(ALUPtr this); // returns error code if a problem occurred
unsigned short ALUGetResult(ALUPtr this);  // error is an integer for error codes
Register ALUGetFlags(ALUPtr this);
// any other methods deemed necessary to work with this object
int ALUsetFlags(ALUPtr this);
int ALUSubtract(ALUPtr this);
int ALUNegation(ALUPtr this);
int ALUAdderNot(ALUPtr this);
int ALUAnd(ALUPtr this);
int ALUOr(ALUPtr this);
