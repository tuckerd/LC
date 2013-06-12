// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// CPU.c  simulates the PC, and the fetching of instructions.

#include <stdlib.h>
#ifndef CPU_H
#include "CPU.h"
#endif

//function prototypes
CPUPtr CPUConstructor()
{
	CPUPtr cpu = (CPUPtr) malloc(sizeof(CPU));
	cpu->memory = MemoryConstructor();
	cpu->MAR = 0x0;
	cpu->MDR = 0x0;
	cpu->PC = 0x0;
	cpu->controller = ConstructController(cpu->memory, &(cpu->PC));
	
	return cpu;
}

//CPU Destructor
void CPUDestructor(CPUPtr this)
{
	free(this->memory);
	free(this);
}

//setters and getters
//Returns a pointer to the Memory inside the CPU struct
MemoryPtr getMemoryPtr(CPUPtr this)
{
	return this->memory;
}

//Returns the value of the MAR
Register getMAR(CPUPtr this)
{
	return this->MAR;
}

//Sets the value of the MAR
void setMAR(CPUPtr this, Register new_mar)
{
	this->MAR = new_mar;
}

//Returns the value of the MDR
Register getMDR(CPUPtr this)
{
	return this->MDR;
}

//Returns the value of the PC
Register getPC(CPUPtr this)
{
	return this->PC;
}

//Sets the value of the PC
void setPC(CPUPtr this, Register new_pc)
{
	this->PC = new_pc;
}

//Returns the value of the flags from the ALU
unsigned short getFlagsFromCPU(CPUPtr this)
{
	return getCC(this->controller);
}

//Operation
//Reads the PC, sets the MAR, advances the PC, gets the instruction from
//memory, and calls the controller to execute the instruction
void step(CPUPtr this)
{
	this->MAR = this->PC;
	this->PC = (this->PC) + 1;
	
	this->MDR = getMemory(this->memory, this->MAR);
	execute(this->controller, this->MDR);
}

//Resets the machine's PC, MAR, and MDR
void resetMachine(CPUPtr this)
{
	this->MAR = 0x0;
	this->MDR = 0x0;
	this->PC = 0x0;
}
