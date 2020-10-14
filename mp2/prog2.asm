;Assuming user will only enter ' ' 0-9 *+/-
;
;
;

;DESCRIPTION:
;For the PRINT_HEX subroutine: We load 'x' into R0 and print it. Then we use R1 as
;a counter to determine when all 4 digits were printed in hex. We use R6 as a bit counter
;and shift R4 digit left. We check R3 and see if its greater than zero, and if it is,
;we shift it left and check digits again. We use R5 to see if value in R4 is less than #-9
;and if it is, we add ASCII 'A'-10 ('A'-10) so that we can print the proper number in hex.
;
;For the EVALUATE subroutine: We first get a character and print it to screen. Then we load
;different values into R1 to determine what was pressed. If a newline character was pressed,
;we check if theres only one value in stack. If a space was pressed, we get another input.
;We check if input is less than ASCII '9' and greater than ASCII '0' to see if input is number.
;If it is a number, we push it to stack. If it's neither, we check to see if its an operator.
;If an operator was pressed, it performs the appropriate operation in a subroutine. If
;an operator was not pressed, than it was an invalid character and we're done with checking
;the input. To perform operations, we pop first operand from stack and store in R3. We check
;for underflow, then pop the second value and store it in R4. Then we apply the operations and
;push the result of it to the stack in R5.
;
;To add, we simply use the ADD instruction.
;To subtract, we complement the second value (R4) and add it with R3.
;To multiply, we use a counter to add the first operand (R3) to R0 and subtract 1 from
;the second operand (R4) and loop this until it R4 = 0.
;To divide, we set the quotient to -1 then add the remainder to the devidend. Then we increment
;the quotient and subtract the divisor from the remainder. If the result is 0 or positive, we 
;loop the instructions and make sure divisor is positive and then add it to the remainder.
;To use an exponent, we loop repeated addition in order to multiply until R4 is 0.
;
;REGISTERS USED:
;R0-Input from KB. Holds result of operations.
;R1-Digit counter (Digits needed to be printed). Holds test values to determine input char. Used for operations.
;R3-Value to print in hexadecimal. First operand.
;R4-Digit that needs to be printed. Second operand.
;R5-Used to check if digit to be pinted is > #-9. Output to stack. Used for exponent subroutine.
;R6-Bit counter. Counter for exponent loop.
;R7-Address of PC for subroutines.

.ORIG x3000


	JSR EVALUATE			; Call the EVALUATE subroutine First to check
	AND R3,R3,#0			; CLEAR R3
	ADD R3,R5,#0			; Load output of Evaluate subroutine into R3 for the PRINT HEX Subroutine

	JSR PRINT_HEX			; Call the PRINT_HEX Subroutine

COMPLETE					

	HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
					
		AND R1, R1, #0		; clear R1
		AND R2, R2, #0		; clear R2 
		AND R4, R4, #0		; clear R4
		AND R5, R5, #0		; clear R5
		AND R6, R6, #0		; clear R6
		ADD R1, R1, #4		; set R1 = 4
	
PRINT_DIGITS

		ADD R1,R1, #0		; initialize R1
				
		BRz DONE			; when all 4 digits printed go to done 

		AND R4, R4, #0		; initialize digit
		ADD R6, R6, #4		; set bit counter to 4
CHECK_BITS
		ADD R6, R6, #0		; initialize R6
		BRz CHECK_DIGIT		; check digits if greater than 4 bits
		
		ADD R4, R4, R4		; shift digit left
		ADD R3, R3, #0		; initialize R3 for checking
		BRzp SKIP_ADD1		; check if R3 is greater than 0	
		ADD R4, R4, #1 		; add 1 to digit

SKIP_ADD1		

		ADD R3, R3, R3		; shift R3 left
		ADD R6, R6, #-1		; deincrement R6
		BRnzp CHECK_BITS	; loop back to check for 4 bits
CHECK_DIGIT
		AND R5, R5, #0		; clear R5 for reuse
		ADD R5, R4, #-9		; add -9 to R5 
		BRp ADD_A_MINUS_TEN	; check if R5 is greater than #-9, if so add 'A'-10

		LD R0, ZERO			; load R0 with ascii '0'
		ADD R0, R4, R0		; add the value loaded in R0 with R4(digit)
		OUT					; output
		ADD R1, R1, #-1		; deincrement R1, the digit counter
		BRnzp PRINT_DIGITS
					
ADD_A_MINUS_TEN
		AND R6, R6, #0				; clear R6 for reuse 
		LD R0, ASCII_A_MINUS_TEN	; load R0 with the ascii value of 'A'-10 
		ADD R0, R0, R4				; add the value loaded in R0 with R4(digit)
		OUT 						; output
		ADD R1, R1, #-1				; deincrement R1
		BRnzp PRINT_DIGITS			; loop back to PRINT_DIGITS

DONE
		LD R7, A_VALUE
		RET
A_VALUE .FILL x3004
									
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R5 - current numerical output
;
;
EVALUATE

ST R7, SaveR7_1


GET_INPUT
		AND R1,R1,#0
		
;Read next input
		GETC
		OUT
;CHeck if value is a newline
		LD R1, NEWLINE_CHAR		; Load the newline character into R1
		NOT R1,R1				; Complement R1
		ADD R1,R1, #1			; R1 = -R1
		ADD R1, R1, R0			; Check if input from keyboard is a newline
		BRz	ONE_VALUE_STACK		; R1 = 0 if newline is found

;Check if input is a space
		LD R1, SPACE			; Load space character into R1
		NOT R1,R1				; Complement R1
		ADD R1,R1, #1			; R1 = -R1
		ADD R1,R1,R0			; Check if input is a space
		BRz GET_INPUT			; IF R1 = 0 space is found

;CHECK FOR EXPONENT

		LD R1, EXP_OP
		NOT R1,R1
		ADD R1,R1, #1
		ADD R1,R1,R0				; Check if input is '^'
		BRnp MINUS_FALSE_TWO		; 
		JSR EXP_TWO					;
		BRnzp RESULT_OF_OPERATION	
		
MINUS_FALSE_TWO

		LD R1, MINUS_OP
		NOT R1,R1
		ADD R1,R1, #1
		ADD R1,R1,R0				; Check if input is '-'
		BRnp CHECK_NUMBERS			;
		JSR MINUS_TWO				; 
		BRnzp RESULT_OF_OPERATION
		
		
		
;Check if input character is a number (x30 - x39)
CHECK_NUMBERS
		LD R1, NINE					; Load nine into R1
		NOT R1, R1					; Complement R1
		ADD R1,R1, #1				; ADD 1 to R1
		ADD R1, R1, R0				; Check if input is <= 9
		BRnz CHECK_GREATER_ZERO		; IF R1 = Negative or Zero then it is less than 9
		BRnzp GET_INPUT				; Return to Get input


CHECK_GREATER_ZERO
		LD R1, ZERO					; Load zero into R1
		NOT R1, R1					; Complement R1
		ADD R1,R1, #1				; ADD 1 to R1
		ADD R6, R1, R0				; Check if input is >= 0
		BRzp PUSH_FIRST				; IF Positive or zero then its valid otherwise its false
		BRnzp CHECK_OPERATORS		; Branch to Check_OPERATORS


; CHeck if input is an OPERATOR
PUSH_FIRST
		ADD R0,R1,R0				; Load into R0
		JSR PUSH					; Push operand before check to stack
		BRnzp GET_INPUT				; Go get input 

CHECK_OPERATORS

		LD R1, PLUS_OP				; 
		NOT R1, R1					; 
		ADD R1,R1, #1				; 
		ADD R1, R1, R0				; Check if input is '+'
		BRnp PLUS_FALSE				;
		JSR PLUS_TWO				; Call addition subroutine
		BRnzp RESULT_OF_OPERATION		
PLUS_FALSE
		

		LD R1, MINUS_OP
		NOT R1,R1
		ADD R1,R1, #1
		ADD R1,R1,R0				; Check if input is '-'
		BRnp MINUS_FALSE
		JSR MINUS_TWO				; Call subtraction subroutine
		BRnzp RESULT_OF_OPERATION

		
		
MINUS_FALSE
		
		LD R1, DIV_OP			
		NOT R1,R1
		ADD R1,R1, #1
		ADD R1,R1,R0				; Check if input is '/'
		BRnp DIV_FALSE
		JSR DIV_TWO					; Call division subroutine
		BRnzp RESULT_OF_OPERATION	
DIV_FALSE		
		

		LD R1, MULT_OP
		NOT R1,R1
		ADD R1,R1, #1
		ADD R1,R1,R0				; Check if input is '*'
		BRnp MULT_FALSE
		JSR MUL_TWO					; Call Mult subroutine
		BRnzp RESULT_OF_OPERATION	
MULT_FALSE		


		LD R1, EXP_OP
		NOT R1,R1
		ADD R1,R1, #1
		ADD R1,R1,R0				; Check if input is '^'
		BRnp EXP_FALSE				; 
		JSR EXP_TWO					; Call exponent subroutine
		BRnzp RESULT_OF_OPERATION	
EXP_FALSE
	
		BRnzp PRINT_COMMENT

; POP Subroutine 
POP_TWO

		ST R7, SaveR7_2 

		JSR POP						; POP first operand
		ADD R4,R0, #0				; Stores the first operand into R1
		JSR CHECK_UNDERFLOW   		; Call the check underflow subroutine
		JSR POP						; POP second operand will be in R0
		ADD R3,R0,#0
		JSR CHECK_UNDERFLOW     	; Call the check_underflow subroutine

		LD R7, SaveR7_2 			; restore R7 from memory		

		RET

		SaveR7_2  		.BLKW 1 	; memory for saving R7

; DEAL WITH Stack Underflow
CHECK_UNDERFLOW
		
		ST R7, SaveR7_3 
		ADD R5,R5, #0				; Check R5 for underflow
		BRp PRINT_COMMENT			; If R5 != 0 underflow detected

		LD R7, SaveR7_3 			; restore R7 from memory		
		RET

		SaveR7_3         .BLKW 1 	; memory for saving R7

; APPLY OPERAND


		PLUS_TWO

			ST R7, SaveR7_4 
			JSR POP_TWO				
			JSR PLUS
			LD R7, SaveR7_4 		; restore R7 from memory
			RET		

SaveR7_4  				.BLKW 1 	; memory for saving R7


		MINUS_TWO
			ST R7, SaveR7_5 
			JSR POP_TWO
			JSR MIN
			LD R7, SaveR7_5			; restore R7 from memory
			RET
SaveR7_5  				.BLKW 1 	; memory for saving R7

		EXP_TWO
			ST R7, SaveR7_6 
			JSR POP_TWO
			JSR EXP
			LD R7, SaveR7_6			; restore R7 from memory
			RET

SaveR7_6 				.BLKW 1 	; memory for saving R7

		DIV_TWO
			ST R7, SaveR7_7 
			JSR POP_TWO
			JSR DIV
			LD R7, SaveR7_7			; restore R7 from memory
			RET
		
SaveR7_7  				.BLKW 1 	; memory for saving R7

		MUL_TWO
			ST R7, SaveR7_8 
			JSR POP_TWO
			JSR MUL
			LD R7, SaveR7_8 		; restore R7 from memory
			RET
			
SaveR7_8  				.BLKW 1 	; memory for saving R7



; RESULT OF OPERATION / PUSH VALUE TO STACK
RESULT_OF_OPERATION
		JSR PUSH				; Push the result to stack (contained in R5)
		BRnzp GET_INPUT			; Return to get input
		
ONE_VALUE_STACK
;Check if Stack has one value
		JSR POP
		ADD R5,R5,#0			; Check if R5 = 0 or if POP suceeded
		BRz CHECK_AGAIN			; R5 = 0 there is definitley one value in stack
		BRnzp PRINT_COMMENT
		
CHECK_AGAIN
		JSR POP					; Call Pop subroutine
		ADD R5,R5,#0			; Check for another value in stack
		BRp ONE_VALUE			; If R5 != 0 then only one value in stack
		BRnzp PRINT_COMMENT
PRINT_COMMENT
								;LD R0, NEWLINE_CHAR		; Load the newline char into R0
								;OUT						; OUTPUT A NEWLINE CHAR
		LEA R0, STRING			; Loads the memory adress
		PUTS					; Prints the String
		BRnzp COMPLETE			

ONE_VALUE
		ADD R5, R0, #0			; Load the result into R5
		
FINISH
		LD R7, SaveR7_1 		; restore R7 from memory

		RET						; 
SaveR7_1  				.BLKW 1 ; memory for saving R7

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here

AND R0,R0,#0			; Clears R0
ADD R0,R3,R4			; R0 = R3 + R4

	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

	ST R5, SaveR5_2
	;(R3 - R4)
	AND R0,R0,#0		; Clears R0
	NOT R4,R4			; Complement R4
	ADD R4, R4, #1		; R4 = -R4
	ADD R0, R3, R4		; R0 = R3 -R4

RET					

SaveR5_2 .BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	

;your code goes here okay

AND R0,R0,#0			; Clear R0

COUNTER
	ADD R0, R0, R3		; R0 = R0 + R3		
	ADD R4, R4, #-1		; R4 = R4 - 1
	BRp COUNTER		    ; If R4 != Zero continue adding until R4 = 0

	RET					

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
;DIV	
;your code goes here

DIV	
	AND R0,R0, #0		; Clear R0
	ADD R4,R4,#0		; CHeck that for divide by zero error
	BRz PRINT_COMMENT	; Branch to Print Comment
	ADD R0, R0, #-1		; Set quotient to -1
	AND R1,R1, #0		; Clear R1
	ADD R1,R1,R3		; R1(remainder) = R1 + R3 (dividend)
	NOT R4,R4			; Complement R4
	ADD R4,R4, #1		; R4 = -R4

DIVLOOP
	ADD R0, R0, #1		; Increment quotient
	ADD R1, R1, R4		; R1 = R1(Remainder) - R4(Divisor)
	BRzp DIVLOOP		; If zero or positive go to DIVLOOP
	NOT R4,R4			; Complement R4
	ADD R4, R4, #1		; R4 is positive here
	ADD R1, R1, R4		; R1(remainder) = R1(Remainder) + R4 (divisor)

	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

;your code goes here
EXP
		AND R0,R0, #0		; clear R0
		AND R6, R6, #0 		; clear R6
		ADD R6, R6, R3		; Add the base into R6
		ST R6, SAVER6		; Save R6 in order to restore value later

		ADD R4, R4, #0		; Checks if the exponent is 0
		BRz ONE				;

		ADD R4, R4, #-1		; Checks if the exponent is 1
		BRz EXP_ONE
	EXP_COUNTER

	
	MULT_COUNT_EXP

		ADD R0, R0, R3		; Add the base to itself
		ADD R6, R6, #-1		; deincrement the counter for multiplication 
		BRp MULT_COUNT_EXP	; 
		LD R6, SAVER6		; reload R6
		ADD R3, R0, #0		; store value in R0 to R3 
		AND R0, R0, #0		; clear R0
		ADD R4, R4, #-1		; deincrement the exponent counter
		BRp EXP_COUNTER		;
		ADD R0, R3, #0		; result stored in R3

	DONE_EXP
		RET					;

	ONE
		ADD R0, R0, #1		; if exponent is 0, R0 = 1
		BRnzp DONE_EXP		;

	EXP_ONE
		ADD R0, R3, #0		; if exponent equal to 1, R0 = base 
		BRnzp DONE_EXP
	
	RET
	
SAVER6 .BLKW #1				;

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
	NOT R3, R3			;
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
	NOT R3, R3			;
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



POP_SaveR3				.BLKW #1	;
POP_SaveR4				.BLKW #1	;
STACK_END				.FILL x3FF0	;
STACK_START				.FILL x4000	;
STACK_TOP				.FILL x4000	;
ZERO		 			.FILL x30	; FOR PRINT_HEX
ASCII_A_MINUS_TEN 		.FILL x37	; FOR PRINT_HEX
SPACE					.FILL x20	; Space Character
NEWLINE_CHAR			.FILL x0A	; Newline Character ***x0A*****CHANGE
NINE				    .FILL x39	; the difference between ASCII '9' and '0'
PLUS_OP					.FILL x2B	; '+' operator
MINUS_OP				.FILL x2D	; '-' operator
MULT_OP					.FILL x2A	; '*' operator
DIV_OP					.FILL x2F	; '/' operator
EXP_OP					.FILL x5E	; '^' operator
STRING					.Stringz "Invalid Expression"

.END
