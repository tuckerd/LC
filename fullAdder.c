// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// fullAdder.c


#include <stdio.h>
#include "bit_def.h"
#include "fullAdder.h"

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

bit fullAdder(bit a, bit b, bit c_in, bit * c_out) {
	bit gate_1 = and(and(a, b), c_in);
	bit gate_2 = and(and(a, b), not(c_in));
	bit gate_3 = and(and(a, not(b)), c_in);
	bit gate_4 = and(and(a, not(b)), not(c_in));
	bit gate_5 = and(and(not(a), b), c_in);
	bit gate_6 = and(and(not(a), b), not(c_in));
	bit gate_7 = and(nor(a, b), c_in);

	*c_out = or(or(gate_1, gate_2), or(gate_3, gate_5));
	bit result = or(or(gate_1, gate_4), or(gate_6, gate_7));
	return result;
}
/*
int main(void) {
	bit c_out = 0x0;
	bit c_in = 0x1;
	bit a = 0x1;
	bit b = 0x1;
	bit r = fullAdder(a, b, c_in, &c_out);
	printf("result: expected: 1, actual: %d, carry_out: expected: 1, actual: %d\n", r, c_out);
	a = 0x0;
	c_in = c_out;
	r = fullAdder(a, b, c_in, &c_out);
	printf("result: expected: 0, actual: %d, carry_out: expected: 1, actual: %d\n",r , c_out);
	c_in = c_out;
	b = 0x0;
	r = fullAdder(a, b, c_in, &c_out);
	printf("result: expected: 1, actual: %d, carry_out: expected: 0, actual: %d\n", r, c_out);
	c_in = c_out;
	b = 0x0;
	r = fullAdder(a, b, c_in, &c_out);
	printf("result: expected: 0, actual: %d, carry_out: expected: 0, actual: %d\n", r, c_out);

} */
