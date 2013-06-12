// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// fullAdder.h
// This is the header file for the fullAdder.c which contains function protypes and macro definitions
// used in the lc+

#define FULL_ADDER_H

#ifndef BIT_MAN
#define BIT_MAN
#include "bit_def.h"
#endif
 
typedef unsigned short Register;

#define LOB_MASK 0x0000ffff
#define BIT_0_MASK (short)0x0001
#define BIT_0_MASK_REG 0x00000001
#define BIT_1_MASK_REG 0x00000002
#define BIT_2_MASK_REG 0x00000004
#define BIT_3_MASK_REG 0x00000008
#define BIT_4_MASK_REG 0x00000010
#define BIT_5_MASK_REG 0x00000020
#define BIT_6_MASK_REG 0x00000040
#define BIT_7_MASK_REG 0x00000080
#define BIT_8_MASK_REG 0x00000100
#define BIT_9_MASK_REG 0x00000200
#define BIT_A_MASK_REG 0x00000400
#define BIT_B_MASK_REG 0x00000800
#define BIT_C_MASK_REG 0x00001000
#define BIT_D_MASK_REG 0x00002000
#define BIT_E_MASK_REG 0x00004000
#define BIT_F_MASK_REG 0x00008000


// prototype -
bit fullAdder(bit a, bit b, bit c_in, bit * c_out);
// returns the result bit but also sets the contents of c-out to be used to retrieve the carry out bit
// for the next iteration
// This function, internally, iteratively calls the and_gate with the input bits either as given or
// not-ted as indicated in the diagram in page 62. The outputs from each call to and_gate should be saved
// temporarily to be input to the or_gates. Since your or_gate function only accepts two input bits you
// will have to call the or_gate iteratively over the four wires shown in the diagram. Or the first two
// bits and then or the result of that with the next bit, and so on.
//
// Thus, this function contains several for loops to implement in series what would be done in parallel
// in hardware. That is why this is a simulation!!!

// other methods like setters and getters as needed
