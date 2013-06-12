;Subtracts two positive numbers in a memory location
;Stores them in a third memory location and in R3
;Branch on neg and store R1 to mem location 4
;Otherwise store R2 to the mem location 4

	.ORIG	X0000
	AND	R1, R1, #0	;Clear Operand Register
	AND	R2, R2, #0	;Clear Operand Register
	AND	R3, R3, #0	;Clear Result Register

	LD	R1, FIRST	;Load value from address
	LD	R2, SECOND	;Load value from address
	SUB	R3, R1, R2	;Subtract R1-R2
	ST	R3, RESULT	;Store result in address
	BRn	STOREOP
	LD	R2, SECOND
	ST	R2, OPERAND
	LEA	R3, FIN
	JMP	R3
STOREOP ST	R1, OPERAND
FIN	HALT

FIRST	.FILL	#10
SECOND	.FILL	#7
RESULT	.BLKW	1
OPERAND	.BLKW	1
	.END