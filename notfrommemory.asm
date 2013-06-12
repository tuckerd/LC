;Load pos value from mem and not to different register
;Branch on negative and store value in NEGVAL
;Not the original destination reg and store back in 
;the original load register.  Branch on pos and store.

	.ORIG X0000
	LD	R1, OP1
	NOT	R2, R1
	BRn	STORE
NEXTOP	NOT	R1, R2
	BRp	STORE2
STORE	ST	R2, NEGVAL
	BRnzp	NEXTOP
STORE2	ST	R1, POSVAL	
	HALT

OP1	.FILL	#10
NEGVAL 	.BLKW	1
POSVAL 	.BLKW	1

	.END