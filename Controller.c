// Jason Langowski
// Danielle Tucker
// Tim Ginder
// 2012 November
// Project 4 - LC+ Simulator
// Controller.c
// This is the controller which is the Finite State Machine of the CPU. When given an opcode
// the controller is sent to its next state opening data paths based on the opcode given. To simulate
// this process the execute method parses the opcode then in a switch statement goes to the appropriate
// helper method to LEA or SUB or ADD etc.

#include "Controller.h"


//constructor
ControllerPtr ConstructController(MemoryPtr memory, Register * pc) {
	ControllerPtr controller = (ControllerPtr) malloc(sizeof(Controller));
	controller->alu = ALUConstructor();
	controller->registers = RegistersConstructor();
	controller->PC = pc;
	controller->memory = memory;
	controller->codes = 0x0000;
	return controller;
}

// destructor
void ControllerDestructor(ControllerPtr this) {
	free(this->registers);
	free(this->alu);
	free(this);
}


// Returns a reference to the registers inside the controller struct.
RegistersPtr getRegisters(ControllerPtr controller) {
	return controller->registers;
}

// This method simulates the FNS in that it switches its state based on the the opcode, and 
// sends the instruction to the appropriate helper method to be further parsed.
void execute(ControllerPtr controller, Register ir) {
	Register opcode = parseOpcode(ir);
	switch (opcode) {
		case ADD:
			addHelper(controller, ir);
			break;
		case AND:
			andHelper(controller, ir);
			break;
		case BR:
			brHelper(controller, ir);
			break;
		case JMP:
			jmpHelper(controller, ir);
			break;
		case JSR:
			jsrHelper(controller, ir);
			break;
		case LD:
			ldHelper(controller, ir);
			break;
		case LDI:
			ldiHelper(controller, ir);
			break;
		case LDR:
			ldrHelper(controller, ir);
			break;
		case LEA:
			leaHelper(controller, ir);
			break;
		case NOT:
			notHelper(controller, ir);
			break;
		case ST:
			stHelper(controller, ir);
			break;
		case STI:
			stiHelper(controller, ir);
			break;
		case STR:
			strHelper(controller, ir);
			break;
		case SUB:
			subHelper(controller, ir);
			break;
		default:
			break;

	}
}

// Helper functions

// controls the add opcode condition. Can ADD two registers and store in a dest register or
// add one register to an immediate value and store it in a dest register
void addHelper(ControllerPtr controller, Register ir) {
	int dest = parseDest(ir);
	int src1 = parseSrc1(ir);
	Register * registers = controller->registers->registers;
	if ((ir & IMM)?1:0 == 1) {
		int imm = parseImm(ir);
		ALUSetOperands(controller->alu, registers[src1], imm);
	} else {
		int src2 = parseSrc2(ir);
		ALUSetOperands(controller->alu, registers[src1], registers[src2]);
	}
	rippleCarryAdderAdd(controller->alu);
	registers[dest] = ALUGetResult(controller->alu);
	setCC(controller, ALUGetFlags(controller->alu));
}

// controls the and opcode condition. Can AND two registers and store in a dest register or
// add one register to an immediate value and store it in a dest register
void andHelper(ControllerPtr controller, Register ir) {
	int dest = parseDest(ir);
	int src1 = parseSrc1(ir);
	Register * registers = controller->registers->registers;
	if ((ir & IMM)?1:0 == 1) {
		Register imm = parseImm(ir);
		ALUSetOperands(controller->alu, registers[src1], imm);
	} else {
		int src2 = parseSrc2(ir);
		ALUSetOperands(controller->alu, registers[src1], registers[src2]);
	}
	ALUAnd(controller->alu);
	registers[dest] = ALUGetResult(controller->alu);
	setCC(controller, ALUGetFlags(controller->alu));
}

// Controls the BR opcode condition. Will branch on the appropriate condition codes specified
// in bits [11:7] of the opcode. Will branch by using the CC of the last instruction that set the
// Condition Codes
void brHelper(ControllerPtr controller, Register ir) {
	Register flags = controller->codes;
	if (((ir & BR_N)?1:0 == 1) && ((flags & BR_N)?1:0 == 1)|| ((ir & BR_P)?1:0 == 1) && ((flags & BR_P)?1:0 == 1) || 
		((ir & BR_Z)?1:0 == 1) && ((flags & BR_Z)?1:0 == 1) || ((ir & BR_C)?1:0 == 1) && ((flags & BR_C)?1:0 == 1) || 
		((ir & BR_O)?1:0 ==1) && ((flags & BR_O)?1:0 == 1)) {
		Register pc = *controller->PC;
		Register offset = ir & PC7;
		*(controller->PC) = pc + sext7(offset);
	} 
}


// Controls the JMP opcode condition. Will load the pc with the address that is in the Base Register.
void jmpHelper(ControllerPtr controller, Register ir) {
	int baseR = parseSrc1(ir);
	Register * registers = controller->registers->registers;
	*(controller->PC) = registers[baseR];
}

// Controls the JSR and JSRR opcode conditions. If Bit 11 is a one the the PC will be loaded with
// PC + and 11 bit offset else PC will be loaded with address specifed in a Base Register.
void jsrHelper(ControllerPtr controller, Register ir) {
	Register * registers = controller->registers->registers;
	registers[7] = *(controller->PC);
	if ((ir & JSR_11)?1:0 == 0) {
		*(controller->PC) = registers[parseSrc1(ir)];
	} else {
		*(controller->PC) = *(controller->PC) + sext11(ir & PC11);
	}
}


// Controls the LD opcode condition. Loads a desination register with the value at the memory
//location that is PC + 9 bit offset.
void ldHelper(ControllerPtr controller, Register ir) {
	Register * registers = controller->registers->registers;
	Register * memory = controller->memory->memory;
	Register value = memory[*(controller->PC) + sext9(ir & PC9)];
	checkCC(controller, value);
	int destination = parseDest(ir);
	registers[destination] = value;
			
}



//Controls the LDI opcode condition.  Loads a destination register with the value at the memory location
//of the value at the memory location that is PC + 9 bit offset.
void ldiHelper(ControllerPtr controller, Register ir) {
	Register * memory = controller->memory->memory;
	Register * registers = controller->registers->registers;
	Register value = memory[memory[*(controller->PC) + sext9(ir)]];
	checkCC(controller, value);
	registers[parseDest(ir)] = value;
}

//Controls the LDR opcode condition. Loads a destination register with the value at a source
//register + a 6 bit offset.
void ldrHelper(ControllerPtr controller, Register ir) {
	Register * registers = controller->registers->registers;
	Register * memory = controller->memory->memory;
	Register value = memory[registers[parseSrc1(ir)] + sext6(ir & PC6)];
	checkCC(controller, value);
	registers[parseDest(ir)] = value;
}


//Controls the LEA opcode condition. Loads a destination register with PC + a 9 bit offset.
void leaHelper(ControllerPtr controller, Register ir) {
	Register * registers = controller->registers->registers;
	Register value = *(controller->PC) + sext9(ir & PC9);
	checkCC(controller, value);
	registers[parseDest(ir)] = value;
}

//Controls the NOT opcode condition. Will bitwise not the value in a source register and store
//it in a destination register.
void notHelper(ControllerPtr controller, Register ir) {
	int src = parseSrc1(ir);
	ALUPtr alu = controller->alu;
	Register * registers = controller->registers->registers;
	ALUSetOperands(alu, registers[src], registers[src]);
	ALUNot(alu);
	registers[parseDest(ir)] = ALUGetResult(alu);
	setCC(controller, ALUGetFlags(alu));
	
}

//Controls the ST opcode condition. Will store in memory location that is PC + 9 bit offset the value in
//a source register.
void stHelper(ControllerPtr controller, Register ir) {
	Register * registers = controller->registers->registers;
	Register * memory = controller->memory->memory;
	memory[*(controller->PC) + sext9(ir & PC9)] = 
							registers[parseDest(ir)];
}

//Controls the STI opcode condition. Will store in the memory location that is obtained from the
// memory location that is PC + 9 bit offset the value in a source register.
void stiHelper(ControllerPtr controller, Register ir) {
	Register * registers = controller->registers->registers;
	Register * memory = controller->memory->memory;
	memory[memory[*(controller->PC) + sext9(ir & PC9)]] = 
					registers[parseDest(ir)];
}

//Controls the STR opcode condition. Will store in the memory location that is the value of a base 
//register plus a 6 bit offset the value that is in a source register.
void strHelper(ControllerPtr controller, Register ir) {
	Register * registers = controller->registers->registers;
	Register * memory = controller->memory->memory;
	memory[registers[parseSrc1(ir)] + sext6(ir & PC6)] = 
					registers[parseDest(ir)];
}

//Controls the SUB opcode we added to the machine hence LC+. Will subtract the value in source 2 from 
// the value in source 1 and store the result in a destination register or will subtract an 
//immediate value from source 1 and store the result in a desination register.
void subHelper(ControllerPtr controller, Register ir) {
	int dest = parseDest(ir);
	int src1 = parseSrc1(ir);
	Register * registers = controller->registers->registers;
	if ((ir & IMM)?1:0 == 1) {
		int imm = parseImm(ir);
		ALUSetOperands(controller->alu, registers[src1], imm);
	} else {
		int src2 = parseSrc2(ir);
		ALUSetOperands(controller->alu, registers[src1], registers[src2]);
	}
	ALUSubtract(controller->alu);
	registers[dest] = ALUGetResult(controller->alu);
	setCC(controller, ALUGetFlags(controller->alu));
}

// Parses the destination register [11:9] from the instruction to an int.
int parseDest(Register ir) {
	int dest = ir & DEST;
	dest = dest >> 9;
	return dest;
}

//Parses the SRC1 register [8:6] from the instruction to an int.
int parseSrc1(Register ir) {
	int src1 = ir & SRC1;
	src1 = src1 >> 6;
	return src1;
}

//Parses the SRC2 register[2:0] from the instruction to an int.
int parseSrc2(Register ir) {
	int src2 = ir & SRC2;
	return src2;
}

//Parses the immediate [4:0] value from the instruction to a Register.
Register parseImm(Register ir) {
	return ir & IMM_MASK;
}

//Sign extends bits [5:0] and returns the value as a register.
Register sext6(Register offset) {
	if ((offset & PC6_SIGN)?1:0 == 1) {
		offset |= PC6_SEXT;
	}
	return offset;
}

//Sign extends bits [6:0] and returns the value as a register.
Register sext7(Register offset) {
	if ((offset & PC7_SIGN)?1:0 == 1) {
		offset |= PC7_SEXT;
	}
	return offset;
}

//Sign extends bits [8:0] and returns the value as a register.
Register sext9(Register offset) {
	if ((offset & PC9_SIGN)?1:0 == 1) {
		offset |= PC9_SEXT;
	}
	return offset;
}

//Sign extends bits [10:0] and returns the value as a register.
Register sext11(Register offset) {
	if ((offset & PC11_SIGN)?1:0 == 1) {
		offset |= PC11_SEXT;
	}
	return offset;
}

//Parses out the opcode and returns it as a Register.
Register parseOpcode(Register ir) {
	return ir & OPCODE_MASK;
}

//Will check the condition codes that should be set based on the value and calls the 
//set condition codes method.
void checkCC(ControllerPtr controller, Register value) {
	Register codes = 0x0000;
	if (((value & LOB_MASK)?1:0) == 0) {
		codes |= BR_Z;
	} else if (((value& BIT_F_MASK_REG)?1:0) == 1) {
		codes |= BR_N;
	} else {
		codes |= BR_P;
	}
	setCC(controller, codes);
}

//Sets the condition codes in the struct.
void setCC(ControllerPtr controller, Register codes) {
	controller->codes = codes;
}

//returns the contition codes from the struct.
Register getCC(ControllerPtr controller) {
	return controller->codes;
}


