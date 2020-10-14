;write a program that removes duplicate numbers of 
;a sorted sequence stored in memory. The sequence will contain only positive numbers. 
;The sequence starts at memory location x4000 and its end is 
;indicated by the number “0” (0x0). The output sequence should also be sorted.


.ORIG x3000
;;START YOUR CODE HERE

LD R0, SEQ_START ; load x4000 to R0
JSR PULL
BRnzp END

	AND R1, R1, #0		;
	AND R2, R2, #0		;
	AND R3, R3, #0		;
	AND R4, R4, #0		;
	AND R5, R5, #0		;
	AND R6, R6, #0		;
	
	LD R1, SEQ_START	; R1 = M[x4000]
	LD R0, SEQ_START	; R0 = x4000
	

CHECKVAL
	LDR R2, R1, #0		; R2 = M[R1]
	ADD R0, R0, #1		; increment address that is being checked
	LDR R3, R0, #0		; R3 = M[R0]
	BRz END			; If last value is x0, then done.
	NOT R3, R3		;
	ADD R3, R3, #1		; R3 = complemented value in R0 address	
	
	ADD R4, R2, R3		; R4 = M[R1] - M[R0]
	BRnp CHECKVAL		; If no duplicate found, check next one.
	JSR PULL		;
	ADD R1, R1, #1		; increment value being checked
	BRnzp CHECKVAL		;
END
	HALT	


;;;;;;;;;;;;;;;;;;;;;;;;
;Subroutine PULL
;IN: R0(Start Location)
PULL
;; IMPLEMENT SUBROUTINE HERE	
	ST R7, SAVER7		;

	LDR R3, R0, #0		; R3 = M[R0] (duplicate value)
	ADD R5, R0, #1		; R5 = R0 + 1
	LDR R5, R5, #0		;
	STR R5, R0, #0		; M[R5] -> M[R0]


	LD R7, SAVER7		;

RET

SAVER7 .BLKW #1		; stored value of R7
SEQ_START .FILL x4000

.END







