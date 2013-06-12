// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// Memory.c
// This is the memory for the LC+. This data structure will grow on its own sort of like 
// Java's implementation of the arraylist. There is no max capacity for this structure.

#include "Memory.h"

//Contructs the memory
MemoryPtr MemoryConstructor() {
	MemoryPtr mem = (MemoryPtr) malloc(sizeof(Memory));
	mem->memory = (Register *) malloc(sizeof(Register) * 100);
	mem->size = 0;
	mem->capacity = 100;
	int i;
	for (i = 0; i < mem->capacity; i++) {
		mem->memory[i] = 0;
	}
	return mem;
}

//Allows client to set the value of a particular memory location.
void setMemory(MemoryPtr mem, Register value, int index) {
	mem->memory[index] = value;
}

//Appends a new memory location to the end of memmory and store the value there.
void insertMemory(MemoryPtr mem, Register value) {
	int size = mem->size;
	if (size < mem->capacity) {
		Register * mem1 = mem->memory;
		mem1[size] = value;
		
	} else {
		Register * new_mem =  (Register *) malloc(sizeof(Register) * (mem->capacity * 2));
		int i;
		for (i = 0; i < mem->capacity; i++) {
			new_mem[i] = mem->memory[i];
		}
		mem->memory = new_mem;
		mem->capacity = mem->capacity * 2;
		mem->memory[size] = value;
	}
	mem->size = size + 1;
}

//Returns the value at a particular memory address.
Register getMemory(MemoryPtr mem, int index) {
	return mem->memory[index];
}

//Returns the string representation of the Memory.
char * memoryToString(MemoryPtr memory) {
	char * string = (char *) malloc(10);
	char * result = (char *) malloc(memory->capacity * 16);
	char * reg_string = (char *) malloc(10);
	Register i;
	for (i = 0; i < memory->size; i++) {
		Register reg = getMemory(memory, i);
		sprintf(string, "0x%04X\n", reg);
		sprintf(reg_string, "0x%04X: ", i);
		result = strcat(result, reg_string);
		result = strcat(result, string);
	} 
	return result;
}
/*
int main() {
	MemoryPtr memory = MemoryConstructor();
	Register i;
	printf("0x%04X\n", getMemory(memory, 0));
	for (i = 0; i < 150; i++) {
		insertMemory(memory,  i);
	}
	printf("%s", memoryToString(memory));

	setMemory(memory, 0x0000, 3);
	printf("%04X", getMemory(memory, 3));
	
}*/


