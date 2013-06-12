//Jason Langowski
//Danielle Tucker
//Tim Ginder
//2012 November
//Project 4 - LC+ Simulator
//lc-plus.c

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "CPU.h"
#include "lc-plus.h"

//The main function!
int main (void) {
	CPUPtr cpu = CPUConstructor();
	debugerPTR debuger = debugerConstructor();
	setContinue(debuger);
	startFile(debuger, cpu);
	while (getUserContinue(debuger)) {
		debug(debuger, cpu);
	}
	destroyCPU(cpu);
}

//Deallocates memory for the cpu
void destroyCPU(CPUPtr cpu) {
	CPUDestructor(cpu);
}

//Initalizes the process
void startFile(debugerPTR this, CPUPtr cpu) {
	selectLoadProgram(this, cpu);
	display(cpu);
}


