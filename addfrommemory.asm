;Loads two numbers from a memory location and adds them
;together, stores them in a third memory location
;and result is in R1

	.ORIG	X000
	AND	R1, R1, #0	;Clear Result register
	AND	R2, R2, #0	;Clear Operand Register

;Start of actual program
	LD	R1, FIRST	;Load value from address
	LD	R2, SECOND	;Load value from address
	ADD	R1, R1, R2	;Add
	ST	R1, RESULT	;Store result in address
	HALT

FIRST	.FILL	#10
SECOND	.FILL	#7
RESULT	.BLKW	1
	.END