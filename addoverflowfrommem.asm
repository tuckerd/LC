;Add two positive numbers in mem location that will force overflow
;Stores result in a third memory location
;Branch on overflow and store R1 to mem location 4
;Otherwise store R2 to the mem location 4

	.ORIG	X0000
	AND	R1, R1, #0	;Clear Operand Register
	AND	R2, R2, #0	;Clear Operand Register
	AND	R3, R3, #0	;Clear Result Register

	LD	R1, FIRST	;Load value from address
	LD	R2, SECOND	;Load value from address
	ADD	R3, R1, R2	;Add
	ST	R3, RESULT	;Store result in address
	BRo	STOREOP		;"branch on overflow"
	LD	R2, SECOND
	ST	R2, OPERAND
	LEA	R3, FIN
	JMP	R3
STOREOP ST	R1, OPERAND
FIN	HALT

FIRST	.FILL	x7FFF
SECOND	.FILL	#5
RESULT	.BLKW	1
OPERAND	.BLKW	1
	.END