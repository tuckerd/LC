//Jason Langowski
//Danielle Tucker
//Tim Ginder
//2012 November
//Project 4 - LC+ Simulator
//debug.h

#ifndef DEBUG_H
#define DEBUG_H

#include "CPU.h"

typedef struct {
	int user_wants_to_continue;
	int want_step;
	int command;
	int halt_index;
	int break_index;

} debuger;

typedef debuger * debugerPTR;

//Constructs the debug montior
debugerPTR debugerConstructor();

//Set the "mode" of the monitor to contine instead of pause
void setContinue(debugerPTR this);

//The main debug function that runs the debug prcess
void debug(debugerPTR this, CPUPtr cpu);

//Returns if the user wishes to continue
int getUserContinue(debugerPTR this);

//Calls the next stem function from the cpu
void nextStep(debugerPTR this, CPUPtr cpu);

//Displays to the user the contents of the lc+ simulator
void display(CPUPtr cpu);

//Displays to the user a menu with options to select what they want the lc+ to do
void showMenu(debugerPTR this, CPUPtr cpu);

//Loads the file from source location into the lc+
int loadFile(debugerPTR this, char * file, CPUPtr cpu);

//Prompts the user to select or enter the program they wish to load into the lc+ simulator
void selectLoadProgram(debugerPTR this, CPUPtr cputhis);

//Displays the prcess flags by bitmasking the appropriate parts of the flags register
void showFlags(CPUPtr cpu);

#endif

