//Jason Langowski
//Danielle Tucker
//Tim Ginder
//2012 November
//Project 4 - LC+ Simulator
//debug.c 


#include <stdio.h>
#include "debug.h"


#define MAX_LINE_LEN 101

//Constructs the debuger object
debugerPTR debugerConstructor(){
	debugerPTR debuger = (debugerPTR) malloc(1000); //bug where malloc(sizeof(debuger)) was not working on linux for this case only
	debuger->user_wants_to_continue = FALSE;
	debuger->want_step = FALSE;
	debuger->command = FALSE;
	debuger->halt_index = FALSE;
	debuger->break_index = FALSE;

	return debuger;
}

//Sets if the user wishes to continue useing the lc+
void setContinue(debugerPTR this) {
	this->user_wants_to_continue = 1;
}	

// This method builds an integer from a hex string the user inputs.
Register buildIntFromHexString(char * s_num) {
	int length = 4;
	Register result = 0x0;
	char digit = s_num[0];
	if (digit < 58) {
		digit = digit - 48; // convert ASCII to decimal 0 - 9
	} else if (digit < 71) {
		digit = digit - 55; // A - F
	} else {  // a - f
		digit = digit - 87;
	}
	result = result | digit;
	int i;
	for (i = 1; i < length; i++) {
		result = result << length;
		digit = s_num[i];
		if (digit < 58) {
			digit = digit - 48; // convert ASCII to decimal 0 - 9
		} else if (digit < 71) {
			digit = digit - 55; // A - F
		} else {  // a - f
			digit = digit - 87;
		}
		result = result | digit;
	}
	return (result);
}

//The main debug function that runs the debug prcess
void debug(debugerPTR this, CPUPtr cpu) {
	MemoryPtr mem = getMemoryPtr(cpu);
	this->user_wants_to_continue = TRUE;

	while(this->user_wants_to_continue) {
		showMenu(this, cpu);

		if(this->want_step == TRUE) {
			nextStep(this, cpu);
		}
		display(cpu);
		if (cpu->PC == this->halt_index + 1 && this->user_wants_to_continue) {
			printf("The program has finished.");
		}
	}
}

//Returns if the user wishes to continue
int getUserContinue(debugerPTR this) {
	return (this->user_wants_to_continue);
}

//Calls the next step function from the cpu
void nextStep(debugerPTR this, CPUPtr cpu) {
	if (cpu->PC != this->halt_index + 1) {
		step(cpu);
		this->want_step = TRUE;
	}
	else {
		this->want_step = FALSE;
	}
}

//Displays to the user the contents of the lc+ simulator
void display(CPUPtr cpu) {
	printf("\nMemory:\n");
	printf("%s\n\n", memoryToString(cpu->memory));
	printf("Registers:\n");
	printf("%s\n\n", registersToString(cpu->controller->registers));
	printf("MAR:       %04X\n", getMAR(cpu));
	printf("IR/MDR:    %04X\n", getMDR(cpu));
	printf("PC:        %04x\n" , getPC(cpu));
        showFlags(cpu);
}

//Displays to the user a menu with options to select what they want the lc+ to do
void showMenu(debugerPTR this, CPUPtr cpu) {
	int command = 0;
	MemoryPtr mem = cpu->memory;
	printf("\nSelect numerical option:\n 1) Load\n 2) Run\n 3) Step\n 4) Set & Run Breakpoint\n 5) Clear Mem\n 6) Modify a Register\n 7) Show Memory\n 8) Display LC+\n 9) Exit\n");
	char * input = (char *) malloc(3);
	gets(input);
	command = atoi(input);
	int end;
	int start;
	int i;
	unsigned int regval;
	char * num = (char *) malloc(5);
	char * in = (char *) malloc(5);
	switch(command) {
	
	case 1:
		selectLoadProgram(this, cpu);
		break;
	case 2:
		this->want_step = FALSE;
		while (cpu->PC != this->halt_index + 1) {
		step(cpu);
		}
		break;
	case 3:
		this->want_step = TRUE;
		break;
	case 4:
		printf("Please enter the breakpoint:");
		gets(in);
		this->break_index = atoi(in);
		this->want_step = FALSE;
		while (cpu->PC != this->break_index) {
		step(cpu);
		}
		printf("Reached breakpoint.");
		break;
	case 5:
		this->want_step = FALSE;
		printf("Select start of memory you would like to clear.\n");
		gets(num);
		start = atoi(num);
		printf("Select end of memory you would like to clear.\n");
		gets(num);
		end = atoi(num);
		while (start <= end) {
			setMemory(mem, 0, start);
			start ++;
		}
		break;
	case 6:
	        printf("Please select the register you would like to modify: 1, 2, 3, 4, 5, 6, 7\n");
	        gets(num);
	        i = atoi(num);
	        printf("Please enter the 0x0000 value for the register: \n");
		gets(in);
		regval = buildIntFromHexString(in);
		printf("%x", regval);
	        setRegister(cpu->controller->registers, regval, i);
	        break;

	case 7:
		this->want_step = FALSE;
		printf("Select start of memory to show\n");
		gets(num);
		start = atoi(num);
		printf("Select end of memory to show.\n");
		gets(num);
		end = atoi(num);
		while (start <= end) {
			printf("%04x : %04x \n", start, getMemory(mem, start));
			start ++;
		}
		break;
	case 8:
		this->want_step = FALSE;
		display(cpu);
		break;
	case 9:
		printf("Exiting Program.\n");
		this->want_step = FALSE;
		this->user_wants_to_continue = FALSE;
		break;
	default:
		printf("Please enter a numerical option 1-5\n");
		break;
	}
}

//Loads the file from source location into the lc+
int loadFile(debugerPTR this, char * file, CPUPtr cpu) {
	MemoryPtr mem = cpu->memory;
	Register halt = 0xF025;
	char * line = (char *) malloc(sizeof(char) * MAX_LINE_LEN); //Allocate space for line reading/input.
	FILE * source = fopen(file, "r"); //Sets the source as the file name
	int i = 0;
	if (source != NULL) {
		while(1) {
			fgets(line, MAX_LINE_LEN, source); //Reads in the string from source ending in null terminator
			if (feof(source)) break; //If end of file, breaks
			else {
				Register val;
				val = buildIntFromHexString(line); 
				if (val == halt) {
					this->halt_index = i;
				}
				insertMemory(mem, val); //sets the memory via mem pointer in the location i
			}
			i++;
		}
	}
	fclose(source);
	return (this->halt_index);
}

//sets the halt index of the debuger
void setHaltIndex(debugerPTR this, int n) {
	this->halt_index = n;
}

//Prompts the user to select or enter the program they wish to load into the lc+ simulator
void selectLoadProgram(debugerPTR this, CPUPtr cputhis) {
        this->want_step = FALSE;
	destroyCPU(cputhis);
	CPUPtr cpu = CPUConstructor();
	int command = 0;
	printf("Please select a program to load:\n");
	printf("1) Add From Memory\n2) Add Overflow From Memory\n3) Subtract From Memory\n4) Not From Memory\n5) Enter your own program name.hex\n");
	char * input = (char *) malloc(MAX_LINE_LEN);
	gets(input);
	command = atoi(input);
	switch (command) {
	case 1:
		loadFile(this, "addfrommemory.hex" , cpu);
		break;
	case 2:
		loadFile(this, "addoverflowfrommem.hex" , cpu);
		break;
	case 3:
		loadFile(this, "subfrommemory.hex" , cpu);
		break;
	case 4:
		loadFile(this, "notfrommemory.hex" , cpu);
		break;
	case 5:
		printf("Type in the name.hex of the program to load: ");
		char * name = (char *) malloc(MAX_LINE_LEN);
		gets(name);
		loadFile(this, name , cpu);
		break;
	default:
		printf("Please enter a number 1-5.");
		break;
	}
}

//Displays the prcess flags by bitmasking the appropriate parts of the flags register
void showFlags(CPUPtr cpu){
	printf("Flags:  N = %d, Z = %d, P = %d, C = %d, O = %d\n", ((getFlagsFromCPU(cpu) & 0x0800)?1:0), ((getFlagsFromCPU(cpu) & 0x0400)?1:0), ((getFlagsFromCPU(cpu) & 0x0200)?1:0), ((getFlagsFromCPU(cpu) & 0x0100)?1:0), ((getFlagsFromCPU(cpu) & 0x0080)?1:0));
}

