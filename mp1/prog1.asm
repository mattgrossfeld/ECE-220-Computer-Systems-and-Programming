;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2


	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here ********
 
; Register USAGE
; R6 : loop counter 
; R3 : contains the histogram's address 
; R0 : contains the ASCII values and are printed from this register
; R4 : contains the number of bins
;
;


; PROGRAM_DESCRIPTION
;  The program starts from the Histogram address and retrieves the ASCII value of the current character at the address and prints it and a space
;  Then it starts with the lab code where it prints off the hexadecimal value after the space for ASCII
;  Then newline is printed, and increment loop counter to get next ASCII value until the bins are equal to 0 and program is done
;  If not 0, loops back to LOOPBIN and executes program




		AND R6,R6,#0		; Clears R6 (loop counter)
LOOPBIN						; Loop back 
		LD R6, R6SAVE		; Loads R6 save data to not interfere with lab code
		ADD R6, R6, #1		; increment Loop counter
		ST R6, R6SAVE		; Stores R6 SAVE into R6

		LD R3, HIST_ADDR	; Load the Histogram address into R3
		ADD R3, R3, R6 		; Add R6 into R3
		LDR R3, R3, #-1		; Decrement R3 by 1		

		
		LD R0, AT			; R4='@'
		ADD R0, R0, R6		; Get ASCII_VALUE of current_char
		ADD R0, R0, #-1		; Decrement R0 by 1
		OUT					; Prints current_char
		LD R0, SPACE		; Loads space into R0 to print
		OUT					; Prints space character



;LAB CODE	
;Register Usage for Lab

;R1 =  First digit counter
;R2 =  Check if printed is less than four 
;R3 =  Print ASCII
;R4 =  Digit 
;R5 =  bit counter
;R6 =  Check for 4 bits from R3




		AND R1, R1, #0 		; Clear R1
		ADD R1, R1, #4		; Set R1 = 4
		AND R2, R2, #0 		; Clear R2
		AND R4, R4, #0		; Clear R4
		AND R5, R5, #0		; Clear R5	

FIRST_LOOP

		ADD R5, R5, #4			; R5 = 4
		ADD R1, R1, #0 			; Init digit counter R1 = 0
		BRz END_PRINT			; If False program is done.
		AND R4, R4, #0			; Initialize digit
		
CHECK_GOT_FOUR_BITS
		; Check for less than four bits in R3

		ADD R5,R5,#0		    ; Check if R3 has less than four bits
		BRz RIGHT  				; If False go to right loop
	
		ADD R4, R4, R4			; shift digit left
		
		ADD R3, R3, #0			; Check R3
		BRzp ADD_ONE			; If R3 is less than 0 go to right loop
		ADD R4, R4, #1			; ADD 1 to digit

ADD_ONE

		ADD R3, R3, R3				; Shift R3 to the left
		ADD R5, R5, #-1				; Decrement bit counter
		BRnzp CHECK_GOT_FOUR_BITS	; Loop back to Check bits for R3
		


;right loop

RIGHT		AND R6, R6, #0		; Clear R6 to reuse
		ADD R6, R4, #-9			; If R4 <= 9 ADD_ZERO

		BRp ADD_A_MINUS_TEN		; False go to 'A' - 10
		
		LD R0, ZERO				; ASCII zero
		ADD R0,R4,R0			; ADD R4 to R0
		OUT						; OUTPUT
		ADD R1,R1, #-1			; Decrement digit counter

		BRnzp FIRST_LOOP
ADD_A_MINUS_TEN
		LD R0, ASCII_A_MINUS_TEN	; ASCII 'A' - 10
		ADD R0,R4,R0				; ADD R4 to R0
		OUT							; OUTPUT
		ADD R1,R1, #-1				; Decrement digit counter
		BRnzp FIRST_LOOP			; Loop back to first loop


; END OF LAB CODE **************

END_PRINT
		LD R6,R6SAVE			; Load R6 save data to use outside lab code
	
		LD R0, NEW_LINE			; Loads newline character into R0 to print
		OUT						; Prints newline char

		LD R4, NUM_BINS			; Load Number of Bins
		NOT R6, R6				; Not R6 to make negative
		ADD R6, R6, #1			; Increment R6 (loop counter)
		ADD R4, R4, R6			; Check if R6 = 0 by adding 27
		BRp LOOPBIN				; LOOP to beginning if not 0
								; Otherwise HALT




DONE	HALT					; Halt the program


; the data needed by the program
NUM_BINS		.FILL #27			; 27 loop iterations
NEG_AT			.FILL xFFC0			; the additive inverse of ASCII '@'
AT_MIN_Z		.FILL xFFE6			; the difference between ASCII '@' and 'Z'
AT_MIN_BQ		.FILL xFFE0			; the difference between ASCII '@' and '`'
HIST_ADDR		.FILL x3F00     	; histogram starting address
STR_START		.FILL x4000			; string starting address
ZERO		 	.FILL x30			; Zero char
ASCII_A_MINUS_TEN 	.FILL x37		; Ascii for A- '10'
NEW_LINE		.FILL x0A			; NewLine character
SPACE			.FILL x20			; Space character
AT			.FILL x40				; At character
R6SAVE			.BLKW	#1			; Save R6




; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING			; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
