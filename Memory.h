// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// Memory.h
// This is the header file for Memory.c which contains function protypes and macro definitions
// used in the lc+

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_H

#ifndef BIT_MAN
#define BIT_MAN
#include "bit_def.h"
#endif

#ifndef FULL_ADDER_H
#define FULL_ADDER_H
#include "fullAdder.h"
#endif


typedef struct {
	Register * memory;
	int size;
	int capacity;
} Memory;

typedef Memory * MemoryPtr;

MemoryPtr MemoryConstructor();

void insertMemory(MemoryPtr memory, Register value);

Register getMemory(MemoryPtr memory, int index);

char * memoryToString(MemoryPtr memory);

