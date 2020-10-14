.ORIG x3000

LEA r0, stringInput ;input character
PUTS
;;START YOUR CODE HERE

	AND R0, R0, #0		;
	AND R1, R1, #0		;
	AND R2, R2, #0		;
	AND R3, R3, #0		;
	AND R4, R4, #0		;
	AND R5, R5, #0		;
	AND R6, R6, #0		;
	AND R7, R7, #0		;
INPUT
	ST R0, previous	; put previous value of input into "previous"
	GETC		; Get input character
	ST R0, current	; Store the new value into "current"
	OUT		; Print it out

CHECK_INPUT
	LD R3, ASTER		; R3 = '*'
	ADD R4, R0, #0		; R4 = input given.
	
	NOT R3, R3		; Complement asterisk
	ADD R3, R3, #1		; R3 = complemented asterisk
	ADD R5, R0, R3		; R5 = Input - *
	BRz DONE		; If zero, then done.

LENGTHS
	ST R1, maxLength	; maxLength = 1
	ST R1, length		; length = 1

CHECK
	LD R5, current		; R5 = current input
	LD R6, previous		; R6 = previous input
	
	NOT R6, R6		; 
	ADD R6, R6, #1		; R6 = complemented previous input

	ADD R3, R5, R6		; R3 = Current - previous
	BRp INCREMENT		; If current input > previous input, increment current length

	BRnz RESET		; If Current input is less than or equal to previous input, reset length


INCREMENT
	ADD R1, R1, #1		; Length = Length + 1
	ST R1, length		; length incremented put into length
	LD R2, maxLength	; R2 = maxLength
	NOT R2, R2		;
	ADD R2, R2, #1		; Complemented maxLength

	ADD R3, R1, R2		; R3 = currentLength - maxLength
	
	BRp NEWMAX		; if currentLength bigger than maxLength, replace it
	BRnzp INPUT		; repeat input

NEWMAX
	ST R1, maxLength	; make current length new maxLength
	BRnzp INPUT
	
RESET
	AND R1, R1, #0		; Clear R1
	ADD R1, R1, #1		; R1 = #1
	ST R1, length		; #1 = current length
	BRnzp INPUT		; Loop back to input

DONE
	LD R6, maxLength	; Put final maxLength into R6.	
	HALT			; Done


ASTER .FILL x2A		; ASCII '*'
ASCII_0 .FILL x30	; ASCII '0'
ASCII_9 .FILL x39	; ASCII '9'
stringInput .stringz "Please input number: "
maxLength .fill 0
length .fill 0
previous .fill 0
current .fill 0
.END
