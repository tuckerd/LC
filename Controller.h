// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// Controller.h
// This is the header file for the controller which contains function protypes and macro definitions
// used in the lc+

#include <stdio.h>
#include <stdlib.h>

#define CONTROLLER_H

#ifndef ALU_H
#include "ALU.h"
#endif

#ifndef MEMORY_H
#include "Memory.h"
#endif

#ifndef REGISTER_H
#include "Register.h"
#endif

#ifndef FULL_ADDER_H
#include "fullAdder.h"
#endif

#define OPCODE_MASK 0xF000
#define ADD 0x1000
#define AND 0x5000
#define BR  0x0000
#define JMP	0xC000
#define JSR	0x4000
#define LD	0x2000
#define LDI	0xA000
#define LDR	0x6000
#define LEA	0xE000
#define NOT 0x9000
#define RTI 0x8000
#define ST 	0x3000
#define STI 0xB000
#define STR 0x7000
#define SUB 0xD000
#define IMM 0x0020
#define IMM_MASK 0x001F
#define SRC1 0x01C0
#define SRC2 0x0003
#define PC11 0x07FF
#define JSR_11 0x0800
#define PC11_SIGN 0x0400
#define PC11_SEXT 0xF800
#define PC9  0x01FF
#define PC9_SIGN 0x0100
#define PC9_SEXT 0xFE00
#define PC7  0x007F
#define PC7_SIGN 0x0040
#define PC7_SEXT 0xFFC0
#define PC6  0x003F
#define PC6_SIGN 0x0020
#define PC6_SEXT 0xFFC0


typedef struct {
	ALUPtr alu;
	RegistersPtr registers;
	MemoryPtr memory;
	Register * PC;
	Register codes;
} Controller;

typedef Controller * ControllerPtr; 

//constructor
ControllerPtr ConstructController(MemoryPtr memory, Register * pc);

// Returns a reference to the registers inside the controller struct.
RegistersPtr getRegisters(ControllerPtr controller);

// This method simulates the FNS in that it switches its state based on the the opcode, and 
// sends the instruction to the appropriate helper method to be further parsed.
void execute(ControllerPtr controller, Register ir);

// Helper functions

// controls the add opcode condition. Can ADD two registers and store in a dest register or
// add one register to an immediate value and store it in a dest register
void addHelper(ControllerPtr controller, Register ir);

// controls the and opcode condition. Can AND two registers and store in a dest register or
// add one register to an immediate value and store it in a dest register
void andHelper(ControllerPtr controller, Register ir);

// Controls the BR opcode condition. Will branch on the appropriate condition codes specified
// in bits [11:7] of the opcode. Will branch by using the CC of the last instruction that set the
// Condition Codes
void brHelper(ControllerPtr controller, Register ir);

// Controls the JMP opcode condition. Will load the pc with the address that is in the Base Register.
void jmpHelper(ControllerPtr controller, Register ir);

// Controls the JSR and JSRR opcode conditions. If Bit 11 is a one the the PC will be loaded with
// PC + and 11 bit offset else PC will be loaded with address specifed in a Base Register.
void jsrHelper(ControllerPtr controller, Register ir);

// Controls the LD opcode condition. Loads a desination register with the value at the memory
//location that is PC + 9 bit offset.
void ldHelper(ControllerPtr controller, Register ir);

//Controls the LDI opcode condition.  Loads a destination register with the value at the memory location
//of the value at the memory location that is PC + 9 bit offset.
void ldiHelper(ControllerPtr controller, Register ir);

//Controls the LDR opcode condition. Loads a destination register with the value at a source
//register + a 6 bit offset.
void ldrHelper(ControllerPtr controller, Register ir);

//Controls the LEA opcode condition. Loads a destination register with PC + a 9 bit offset.
void leaHelper(ControllerPtr controller, Register ir);

//Controls the NOT opcode condition. Will bitwise not the value in a source register and store
//it in a destination register.
void notHelper(ControllerPtr controller, Register ir);

void retHelper(ControllerPtr controller, Register ir);

//Controls the ST opcode condition. Will store in memory location that is PC + 9 bit offset the value in
//a source register.
void stHelper(ControllerPtr controller, Register ir);

//Controls the STI opcode condition. Will store in the memory location that is obtained from the
// memory location that is PC + 9 bit offset the value in a source register.
void stiHelper(ControllerPtr controller, Register ir);

//Controls the STR opcode condition. Will store in the memory location that is the value of a base 
//register plus a 6 bit offset the value that is in a source register.
void strHelper(ControllerPtr controller, Register ir);

//Controls the SUB opcode we added to the machine hence LC+. Will subtract the value in source 2 from 
// the value in source 1 and store the result in a destination register or will subtract an 
//immediate value from source 1 and store the result in a desination register.
void subHelper(ControllerPtr controller, Register ir);

unsigned char getFlags(ControllerPtr this);      /* for all ALU functions - overflow, negative, zero, and carry flags are set */

//Parses out the opcode and returns it as a Register.
Register parseOpcode(Register ir);

// Parses the destination register [11:9] from the instruction to an int.
int parseDest(Register ir);

//Parses the SRC1 register [8:6] from the instruction to an int.
int parseSrc1(Register ir);

//Parses the SRC2 register[2:0] from the instruction to an int.
int parseSrc2(Register ir);

//Parses the immediate [4:0] value from the instruction to a Register.
Register parseImm(Register ir);

//Sign extends bits [5:0] and returns the value as a register.
Register sext6(Register offset);

//Sign extends bits [6:0] and returns the value as a register.
Register sext7(Register offset);

//Sign extends bits [8:0] and returns the value as a register.
Register sext9(Register offset);

//Sign extends bits [10:0] and returns the value as a register.
Register sext11(Register offset);

//Will check the condition codes that should be set based on the value and calls the 
//set condition codes method.
void checkCC(ControllerPtr controller, Register value);

//Sets the condition codes in the struct.
void setCC(ControllerPtr controller, Register ir);

//returns the contition codes from the struct.
Register getCC(ControllerPtr controller);

