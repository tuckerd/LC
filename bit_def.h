// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// bit_def.h
// This is the header file for the bit_man.c which contains a function protype and macro definitions
// used in the lc+

#define BIT_MAN

typedef unsigned char bit;        // simulates a single bit, we'll use the low order bit in a byte

#ifndef BIT0_MASK
#define BIT0_MASK 0x01
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

bit maskBit(bit a);    // used to ensure only bit 0 has a non-zero value
