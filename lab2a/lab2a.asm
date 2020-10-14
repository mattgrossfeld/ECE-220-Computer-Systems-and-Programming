;modified POP to store value in R6.
;read comments
;
.ORIG x3000

GET_CHAR
	AND R0, R0, #0		;
	GETC			; Get input from user
	OUT			; Echo input from user
	LD R1, SPACE		; R1 <- SPACE
	NOT R1, R1		; Complement
	ADD R1, R1, #1		;
	ADD R1, R1, R0		; Add character from R0 to R1
	BRz GET_CHAR		; If zero, then it's a space and go to get new character
	LD R1, NEW_LINE		; R1 <- New line
	NOT R1, R1		; Complement 
	ADD R1, R1, #1		;
	ADD R1, R0, R1		; 
	Brz DONE		; If zero, then it's a newline char and you're done 
	LD R1, CHAR_RETURN	;
	NOT R1, R1		;
	ADD R1, R1, #1		;
	ADD R1, R0, R1		; If zero, then it's a return char and you're done
	BRz DONE		;
	
	JSR IS_BALANCED		; Check if stack is balanced by using subroutine.

	BRnzp GET_CHAR		; Loop until Return/Newline is pressed.
	
SPACE		.FILL x0020
NEW_LINE	.FILL x000A
CHAR_RETURN	.FILL x000D
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else not modified.
IS_BALANCED
	
	ST R7, saveR7 		; Save PC address
	
	LD R1, openP		; Put '(' in R1
	NOT R1, R1		;
	ADD R1, R1, #1		; Complement '('
	ADD R1, R1, R0		; Check if R0 has a '('
	BRnp CHECK_C		; Check if closing bracket if its not an open bracket
	JSR PUSH		; Go PUSH
	BRnzp GO_BACK		; If pushed, go back and get new char

CHECK_C	LD R1, closeP		; Put ')' in R1
	NOT R1, R1		;
	ADD R1, R1, #1		; Complement ')'
	ADD R1, R1, R0		; Check if R0 has a ')'
	BRnp GO_BACK		; Go back if not a closing bracket
	JSR POP			; Go and POP

	LDI R1, STACK_TOP	; Put Popped Value into R1
	LD R2, openP		; Put '(' in R2
	NOT R2, R2		;
	ADD R2, R2, #1		; Complement popped value
	ADD R1, R1, R2		; Check if popped value is '('
	BRz SET_ONE		; If popped value is '(', balanced so leave R5 alone.
	AND R5, R5, #0		;
	ADD R5, R5, #-1		; If unbalanced,  set R5 to -1.
	BRnzp GO_BACK		; Go back if its unbalanced
SET_ONE	AND R5, R5, #0		;
	ADD R5, R5, #1		; If balanced, set R5 to 1.

GO_BACK	LD R7, saveR7		; Load PC address to R7

	RET			; Leave subroutine


openP  .FILL x28		; '('
closeP .FILL x29		; ')'
saveR7 .BLKW #1			; Store address of R7

NEG_OPEN .FILL xFFD8
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
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R4
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ;
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

DONE HALT

.END


