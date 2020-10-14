 ; Lab 1 
 ; assignment: develop a code to print a value stored in a register 
 ;             as a hexadecimal number to the monitor
 ; algorithm: turnin each group of four bits into a digit
 ;            calculate the corresponding ASCII character;
 ;            print the character to the monitor


;R1 is Printed digit counter
;R2 Checks if less than 4 digits printed.
;R4 is  digit 
;R5 Checks if less than 4 bits from R3.
;R6 Is Bit Counter
 
.ORIG x3000

	AND R1, R1, #0		; Initialize R1 as printed digit counter.
	ADD R1, R1, #4		; Digit Counter = 4
	AND R4, R4, #0		; Initialize R4 as digit counter.
	AND R6, R6, #0		; Initialize R6 as bit counter.


LESS_FOUR_PRINT			; Comparing R1 with 4	

	ADD R6, R6, #4		; Bit counter = 4
	ADD R1, R1, #0		; Check if less than 4 digits printed.
	BRz DONE		;
	AND R4,R4, #0		;

LESS_FOUR_BITS			; Get 4 bits from R3
	
	ADD R6, R6, #0		; Bit Counter = 4.
	BRz CHECK_DIGIT		; 
	ADD R4, R4, R4		; Shift R4 (digit) to the left.
	ADD R3, R3, #0		;
	BRzp SKIP_DIGIT		;
	ADD R4, R4, #1		; Add 1 digit.

SKIP_DIGIT			; If R3 is zero or greater, leave digit alone.
	
	ADD R3, R3, R3		; Shift R3 left.
	ADD R6, R6, #-1		; Increment bit counter by 1.
	BRnzp LESS_FOUR_BITS	; Go back to check if less than 4 bits from R3.

CHECK_DIGIT			; Check if digit is <= 9

	AND R2, R2, #0		; Clear R2.
	ADD R2, R4, #-9		; Check if less than or equal to 9
	BRp ASCII_MINUS_TEN	;
	
	LD R0, ASCII_ZERO	;
	ADD R0, R4, R0		;
 	OUT
	ADD R1, R1, #-1		;
	BRnzp LESS_FOUR_PRINT	;

ASCII_MINUS_TEN			;

	LD R0, A_MINUS_TEN	;
	ADD R0, R4, R0		;
	OUT
	ADD R1, R1, #-1		;
	BRnzp LESS_FOUR_PRINT	;

				; stop the computer
DONE HALT

				; program data section starts here

ASCII_ZERO	.FILL x30	; '0' 
A_MINUS_TEN	.FILL x37	; 'A'- 10

 .END

