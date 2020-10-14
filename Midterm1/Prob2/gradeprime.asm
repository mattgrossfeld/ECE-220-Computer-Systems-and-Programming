;Write a program to check whether a given number is a weird number.
;Weird numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 6, 8 are weird while 14 is not since it includes another prime factor 7. You do not need to consider 1 for your program.
;input: a number stored in R3 (a number being set during testing)
;output: if the number stored in R3 is weird, R6 should be set to 1; otherwise R6 should not be set to 1 (can be any other number).


ECEGRADE .FILL  x3000

;; START YOUR CODE HERE

	AND R1, R1, #0		;
	AND R2, R2, #0		;
	AND R4, R4, #0		;
	AND R5, R5, #0		;
	AND R6, R6, #0		;
CHECK_2
	AND R4, R4, #0		; Clear R4
	ADD R4, R4, #2		; R4 = 2
	JSR DIVIDE		; Divide R3/2
	ADD R1, R1, #0		; Check R1 (remainder)
	BRnp CHECK_3
	ADD R3, R0, #0		; R3 = quotient
	BRnzp CHECK_2		;

CHECK_3
	LD R3, SAVER3
	AND R4, R4, #0		; Clear R4
	ADD R4, R4, #3		; R4 = #3
	JSR DIVIDE		; Divide R3/3
	ADD R1, R1, #0		; Check R1 (remainder)
	BRnp CHECK_5
	ADD R3, R0, #0		; R3 = quotient
	BRnzp CHECK_3		;
	
CHECK_5
	LD R3, SAVER3
	AND R4, R4, #0		;
	ADD R4, R4, #5		; R4 = 5
	JSR DIVIDE		; Divide R3/5
	ADD R1, R1, #0		; Check R1 (remainder)
	BRnp STEP5		;
	ADD R3, R0, #0		; R3 = quotient
	BRnzp CHECK_5		;

STEP5
	ADD R6, R3, #0		; R6 = R3
	HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;DIVIDE SUBROUTINE
;input: R3, R4 
;calculate R3/R4
;out: R0-quotient, R1-remainder
DIVIDE
;;IMPLEMENT SUBROUTINE HERE
	ST R7, SAVER7
	ST R3, SAVER3
	NOT R2, R4		; R2 = -R4
	ADD R2, R2, #1		; R2 = complemented # in R4
	AND R6, R6, #0		;
	
DIVLOOP
	ADD R3, R3, R2		; R5 = #R3 - #R2
	ADD R6, R6, #1		; Increment quotient
	ADD R0, R6, #0		; R0 = quotient
	ADD R3, R3, #0		; Check if last value subtracted is positive
	BRp DIVLOOP		; As long as there is still a remainder, keep dividing
	ADD R6, R6, #-1	; Go back down one.
	ADD R1, R3, R4		; R1 = remainder
	ADD R0, R6, #0		; R0 = quotient
	LD R7, SAVER7		;
RET

SAVER7 .BLKW #1		; Saved value of R7
SAVER3 .BLKW #1		; Saved value of R3
.END 
