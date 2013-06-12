// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// logic_gates.h
// This is the header file for the logic_gates.c which contains function protypes and macro definitions
// used in the lc+

#define BIT
#include "bit_def.h"

//Logical AND of two bits
bit and(bit a, bit b);

//Logical NAND of two bits
bit nand(bit a, bit b);

//Logical NOR of two bits
bit nor(bit a, bit b);

//Logical NOT of two bits
bit not(bit a);

//Logical OR of two bits
bit or(bit a, bit b);

//Logical XOR of two bits
bit xor(bit a, bit b);
