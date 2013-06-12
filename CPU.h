// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// CPU.h
// This is the header file for CPU.c that contains function prototypes for CPU.c

#ifndef CPU_H
#define CPU_H

#ifndef CONTROLLER_H
#define	CONTROLLER_H
#include "Controller.h"
#endif

#ifndef MEMORY_H
#define	MEMORY_H
#include "Memory.h"
#endif

#ifndef FULL_ADDER_H
#define FULL_ADDER_H
#include "fullAdder.h"
#endif

typedef struct {
	ControllerPtr	controller;
	MemoryPtr memory;
	Register MAR;
	Register MDR;
	Register PC;
} CPU;

typedef CPU * CPUPtr;

//function prototypes
//constructor for CPU struct.
CPUPtr CPUConstructor();

//CPU Destructor
void CPUDestructor(CPUPtr this);

//setters and getters
//Returns a pointer to the Memory inside the CPU struct
MemoryPtr getMemoryPtr(CPUPtr this);

//Returns the value of the MAR
Register getMAR(CPUPtr this);

//Sets the value of the MAR
void setMAR(CPUPtr this, Register new_mar);

//Returns the value of the MDR
Register getMDR(CPUPtr this);

//Returns the value of the PC
Register getPC(CPUPtr this);

//Sets the value of the PC
void setPC(CPUPtr this, Register new_pc);

//Returns the value of the flags from the ALU
Register getFlagsFromCPU(CPUPtr this);

Register getRegistersFromCPU(CPUPtr this);

//Operation
//Reads the PC, sets the MAR, advances the PC, gets the instruction from
//memory, and calls the controller to execute the instruction
void step(CPUPtr this);

//Resets the machine's PC, MAR, and MDR
void resetMachine(CPUPtr this);
#endif //#ifndef CPU_H
