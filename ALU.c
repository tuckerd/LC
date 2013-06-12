// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// AlU.c
// This is the ALU. The Registers A,B,R simulate the wire paths to the ALU. A being operand 1, B being Operand 2, and 
// R being the Result that comes out of the ALU. I decided to store the flags inside of the ALU to simulate the ALU setting 
// the flags.

#include <stdio.h>
#include <stdlib.h>
#ifndef ALU_H
#include "ALU.h"
#endif

// Constructs an ALU
ALUPtr ALUConstructor(void) {
	ALUPtr alu = (ALUPtr) malloc(sizeof(ALU));
	alu->A = 0x00;
	alu->B = 0x00;
	alu->R = 0x00;
	alu->flags = 0x0;
	alu->c_out = 0x0;
	alu->mask_array[0] = BIT_0_MASK_REG;
	alu->mask_array[1] = BIT_1_MASK_REG;
	alu->mask_array[2] = BIT_2_MASK_REG;
	alu->mask_array[3] = BIT_3_MASK_REG;
	alu->mask_array[4] = BIT_4_MASK_REG;
	alu->mask_array[5] = BIT_5_MASK_REG;
	alu->mask_array[6] = BIT_6_MASK_REG;
	alu->mask_array[7] = BIT_7_MASK_REG;
	alu->mask_array[8] = BIT_8_MASK_REG;
	alu->mask_array[9] = BIT_9_MASK_REG;
	alu->mask_array[10] = BIT_A_MASK_REG;
	alu->mask_array[11] = BIT_B_MASK_REG;
	alu->mask_array[12] = BIT_C_MASK_REG;
	alu->mask_array[13] = BIT_D_MASK_REG;
	alu->mask_array[14] = BIT_E_MASK_REG;
	alu->mask_array[15] = BIT_F_MASK_REG;
	return alu;
}

// Sets the operands that the alu will carry out operations on
int ALUSetOperands(ALUPtr this, Register A, Register B) {
	this->A = A & LOB_MASK;
	this->B = B & LOB_MASK;
}

// This is the ripple carry adder inside the alu and will add all the bits of an operand with the bits from another 
// operand
int rippleCarryAdderAdd(ALUPtr this) {
	bit c_out;
	bit c_in = 0x0;
	bit a;
	bit b;
	bit r;
	Register R = 0x0000;
	
	int i;
	for (i = 0; i < 16; i++) {
		a = ((this->A & this->mask_array[i])?1:0);
		b = ((this->B & this->mask_array[i])?1:0);
		r = fullAdder(a, b, c_in, &c_out);
		c_in = c_out;
		R |= (r << i);
	}
	this->c_out = c_out;
	this->R = R;
	ALUsetFlags(this);
} // returns error code if a problem occurred

// Subtract first negates operand B then 
// Calls the add function.
int ALUSubtract(ALUPtr this) {
	ALUNegation(this);
	return rippleCarryAdderAdd(this);
}

// Negates the operand B by noting all the bits
// then adding one.
int ALUNegation(ALUPtr this) {
	ALUNot(this);
	Register b = this->B;
	this->c_out = 0;
	b += 0x01;
	this->B = b;
	this->R = b;
	ALUsetFlags(this);
	this->flags &= DEST;
}

// This function will not operand B and store the result in R
int ALUNot(ALUPtr this) {
	Register b = this->B;
	b = ~b;
	this->B = b;
	this->R = b;
	ALUsetFlags(this);
	this->flags &= DEST; 
}

// This function will bitwise AND A and B and store the result.
int ALUAnd(ALUPtr this) {
	Register a = this->A;
	Register b = this->B;
	Register r = a & b;
	this->R = r;
	ALUsetFlags(this);
	this->flags &= DEST; 
}

// This function will bitwise OR A and B and store the result.
int ALUOr(ALUPtr this) {
	Register a = this->A;
	Register b = this->B;
	Register r = a | b;
	this->R = r;
	ALUsetFlags(this);
	this->flags &= DEST;
}

// This function will set the condition codes (flags) after an operation is complete.
int ALUsetFlags(ALUPtr this) {
	Register flags = 0x00;

	if (((this->R & LOB_MASK)?1:0) == 0) {
		flags |= BR_Z;
	} else if (((this->R & BIT_F_MASK_REG)?1:0) == 1) {
		flags |= BR_N;
	} else if (((this->R & BIT_F_MASK_REG)?1:0) == 0) {
		flags |= BR_P;
	}
	if (this->c_out == 1) {
		flags |= BR_C;
	}
	if (((this->A & BIT_F_MASK_REG)?1:0) == ((this->B & BIT_F_MASK_REG)?1:0)  && 
		((this->A & BIT_F_MASK_REG)?1:0) != ((this->R & BIT_F_MASK_REG)?1:0)) {
		flags |= BR_O;
	}
	
	this->flags = flags;
}

// This method will return the result of an operation.
unsigned short ALUGetResult(ALUPtr this) {
	return this->R;
} 

// This method will return the condition codes (flags) that an operation sets.
Register ALUGetFlags(ALUPtr this) {
	return this->flags;
}

/*
int main(void) {
	int error;
	Register array[] = {0x70B0, 0x41AA, 0xA123,
	0x8001, 0x7001, 0x0022, 0x0122, 0x81D3,
    0xB041, 0x7579, 0x7854};

	RippleCarryAdderPtr adder = rippleCarryAdder();
	int i;
	rippleCarryAdderSetRegisters(adder, array[0], array[1]);
	rippleCarryAdderAdd(adder);
	Register R = rippleCarryAdderGetResult(adder, &error);
	unsigned char flags = rippleCarryAdderGetFlags(adder, &error);
	printf("0x%X + 0x%X = 0x%X flags 0x%X\n", array[0], array[1], R ,flags);

	rippleCarryAdderSetRegisters(adder, array[2], array[3]);
	rippleCarryAdderAdd(adder);
	R = rippleCarryAdderGetResult(adder, &error);
	flags = rippleCarryAdderGetFlags(adder, &error);
	printf("0x%X + 0x%X = 0x%X flags 0x%X\n", array[2], array[3], R ,flags);

	rippleCarryAdderSetRegisters(adder, array[2], array[4]);
	rippleCarryAdderAdd(adder);
	R = rippleCarryAdderGetResult(adder, &error);
	flags = rippleCarryAdderGetFlags(adder, &error);
	printf("0x%X + 0x%X = 0x%X flags 0x%X\n", array[2], array[4], R ,flags);

	rippleCarryAdderSetRegisters(adder, array[5], array[6]);
	rippleCarryAdderAdd(adder);
	R = rippleCarryAdderGetResult(adder, &error);
	flags = rippleCarryAdderGetFlags(adder, &error);
	printf("0x00%X + 0x0%X = 0x0%X flags 0x%X\n", array[5], array[6], R ,flags);

	rippleCarryAdderSetRegisters(adder, array[7], array[8]);
	rippleCarryAdderAdd(adder);
	R = rippleCarryAdderGetResult(adder, &error);
	flags = rippleCarryAdderGetFlags(adder, &error);
	printf("0x%X + 0x%X = 0x%X flags 0x%X\n", array[7], array[8], R ,flags);


	rippleCarryAdderSetRegisters(adder, array[9], array[10]);
	rippleCarryAdderAdd(adder);
	R = rippleCarryAdderGetResult(adder, &error);
	flags = rippleCarryAdderGetFlags(adder, &error);
	printf("0x%X + 0x%X = 0x%X flags 0x%X\n", array[9], array[10], R ,flags);
	free(adder);



    0x70B0 + 0x41AA = 0xB25A
    0xA123 + 0x8001 = 0x2124 with carry out and overflow
    0xA123 + 0x7001 = ? (was there carry or overflow?)
    two more additions of two operands of your own choice that show a) a zero result and b) a negative result, both without carry or overflow

*/


