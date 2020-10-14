;number to print in decimal is in R3.
;it will be positive.
.ORIG x3000

	AND R4, R4, #0		; Clear R4
	ADD R4, R4, #10		; Divisor = #10

LOOP
	JSR DIV			; Go to divide subroutine
	
	AND R3, R3, #0		;
	ADD R3, R3, R0		; Make the quotient the new dividend.

	AND R0, R0, #0		; Clear R0
	ADD R0, R0, R1		; Make remainder the new quotient.
	JSR PUSH		; Push the remainder onto stack. (R0 is input for PUSH)

	ADD R3, R3, #0		; Change condition codes according to quotient.
	BRp LOOP		; Loop if quotient is not zero.

POP_LOOP
	LD R6, ASCII_0		; R6 = '0' in ASCII
	JSR POP			; Pop stack
	ADD R5, R5, #0		; Set condition codes according to R5 (status of stack)
	BRp DONE		; If R5 = 1, underflow happened and we're done because stack is done.
	ADD R0, R0, R6		; Adding offset for ASCII value
	OUT
	BRnzp POP_LOOP		; Repeat

DONE	HALT	



ASCII_0 .FILL x30
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3 - dividend, R4 - divisor
;out R0-quotient, R1-remainder
DIV	
	AND R0, R0, #0		; Clear R0
	ADD R0, R0, #-1		; Set quotient to -1
	AND R1, R1, #0		; Clear R1
	ADD R1, R1, R3		; R1 = R3 (Remainder = Dividend)
	NOT R4, R4		; 
	ADD R4, R4, #1		; R4 = -R4 (Negative divisor for subtracting)

DIV_LOOP
	ADD R0, R0, #1		; Increment quotient (will initially make it 0)
	ADD R1, R1, R4		; R1 = R1-R4
	BRzp DIV_LOOP		; Check if remainder is positive. If it is, keep dividing.
	NOT R4, R4		;
	ADD R4, R4, #1		; Make R4 positive again.
	ADD R1, R1, R4		; Make Remainder positive again. It cannot be negative. 
		
	RET


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

.END
