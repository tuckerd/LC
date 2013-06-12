all: lc-plus

lc-plus: lc-plus.h lc-plus.c Register.o ALU.o fullAdder.o logic_gates.o bit_man.o debug.o Memory.o
	gcc -g lc-plus.c debug.o Controller.o CPU.o Memory.o Register.o ALU.o fullAdder.o logic_gates.o bit_man.o -o lc-plus
	
debug.o: debug.h debug.c Controller.o CPU.o Memory.o
	gcc -c debug.c
	
Controller.o: Controller.c Controller.h fullAdder.o ALU.o logic_gates.o bit_man.o
	gcc -c Controller.c

CPU.o: CPU.c CPU.h Memory.o
	gcc -c CPU.c

Memory.o: Memory.c Memory.h
	gcc -c Memory.c
	
Register.o: Register.c Register.h
	gcc -c Register.c

ALU.o : ALU.c ALU.h fullAdder.o logic_gates.o bit_man.o 
	gcc -c ALU.c
	
fullAdder.o: fullAdder.c logic_gates.o bit_man.o fullAdder.h
	gcc -c fullAdder.c
	
logic_gates.o: logic_gates.c bit_man.o logic_gates.h
	gcc -c logic_gates.c

bit_man.o: bit_man.c bit_def.h
	gcc -c bit_man.c