// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// logic_gates.c

#include "logic_gates.h"
#ifndef BIT
#include "bit_def.h"
#define BIT
#endif

// And two bits
bit and(bit a, bit b) {
    bit r;

    a = maskBit(a);    // make sure no spurious bits get by!
    b = maskBit(b);
    r = a & b & 0x01;

    return r;
}

// Not And two bits
bit nand(bit a, bit b) {
    return not(and(a, b));
}

// Not Or two bits
bit nor(bit a, bit b) {
	return not(or(a, b));
}

// Not two bits
bit not(bit a) {
	a = maskBit(a);
	a = ~a & 0x01;
	return a;
}

// Or two bits
bit or(bit a, bit b) {
	a = maskBit(a);
	b = maskBit(b);

	bit r = a | b;
	return r;
}

// Exclusive or two bits
bit xor(bit a, bit b) {
	a = maskBit(a);
	b = maskBit(b);

	bit r = a ^ b;
	return r;
}
