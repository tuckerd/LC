// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// bit_man.c

#include "bit_def.h"
#define BIT

// masks a bit to only use the low order bit in the data type that was defined as bit.
bit maskBit(bit a) { 
	a &= 0x01; 
	return a; 
}
