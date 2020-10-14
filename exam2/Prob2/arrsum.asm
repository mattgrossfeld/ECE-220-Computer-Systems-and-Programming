.ORIG x3000

;;R5 - frame pointer
;;R6 - stack pointer
;;MAIN - DO NOT CHANGE ANY CODE HERE
	LD R6, STACK
	LD R5, STACK
	ADD R6, R6, 1	; runtime stack is empty
	ADD R6, R6, -1	; space for x

	AND R0, R0, 0	; counter for # of elements in array
	ADD R0, R0, 4	
	AND R1, R1, 0	; values of array
	ADD R1, R1, 4
INITARR
	ADD R6, R6, -1	; space for arr[i]
	STR R1, R6, 0	; initialize array cell with value
	ADD R1, R1, -1	; decrement value(4,3,2,1)
	ADD R0, R0, -1	; decrement R0 by 1	
	BRp INITARR	; check whether its done 4 times 

;IMPLEMENT ME: stack build up - prepare to call ARRAY_SUM
	AND R1, R1, #0		; Clear R1
	ADD R1, R1, #1		; R1 = 1
	ADD R6, R6, #-1		; 
ARRAY_ZERO
	STR R1, R6, #0		; A[0] = 1
	ADD R6, R6, #-1		;
	ADD R1, R1, #1		; R1 = 2
	STR R1, R6, #0		; A[1] = 2
	ADD R6, R6, #-1		;
	ADD R1, R1, #1		; R1 = 3
	STR R1, R6, #0		; A[2] = 3
	ADD R6, R6, #-1		;
	ADD R1, R1, #1		; R1 = 4
	STR R1, R6, #0		; A[3] = 4
	


;IMPLEMENT ME: call ARRAY_SUM
	JSR ARRAY_SUM
	


;IMPLEMENT ME: stack tear down after returning from ARRAY_SUM 
	STR R0, R5, #0;		x = return val
	ADD R6, R6, #5; 	Pops the array from function


;IMPLEMENT ME: return 0
HALT
	

;----------END OF MAIN----------

;ARRAY_SUM subroutine starts here
ARRAY_SUM
;IMPLEMENT ME: stack build up at ARRAY_SUM
	AND R2, R2, #0		; Clear R2. R2 = sum
	
	ADD R6, R6, #-1		; Space allocated for return value
	ADD R6, R6, #-1		; Space for return address (R7)
	STR R7, R6, #0;		; Stores R7 in address
	ADD R6, R6, #-1		; Space for caller's frame pointer
	STR R5, R6, #0		; Stores Frame pointer
	ADD R6, R6, #-1		; Space for int i.
	ADD R5, R6, #0		; R5 = R6 now. points to first local variable
	ADD R6, R6, #-1		; Space for int sum.
	STR R2, R6, #0		; int sum = 0.
	
	
;IMPLEMENT ME: Calculation
	AND R3, R3, #0		; Clear R3
	ADD R3, R3, #-4		; R3 = #-4 R3 = i
	AND R1, R1, #0		; Clear R1
	LDR R1, R5, #4		; R1 = array[0]
	AND R0, R0, #0		; Clear R0
	LEA R0, ARRAY_ZERO	; R0 address of array[0]

FOR_LOOP
	ADD R3, R3, #0		; Get CC codes for R3
	BRn GET_SUM		; If i<4 (set i = -4. increment until zero), loop
	STR R2, R6, #4		; Store in return val address
	BRnzp TEAR_DOWN		; When done looping and values done, tear it all down
	
GET_SUM
	LDR R1, R0, #0		; R1 = A[0]
	ADD R2, R2, R1		; Sum = sum + a[i]
	STR R2, R6, #0		; Store the sum
	ADD R0, R0, #-1		; increment address for next array val
	ADD R3, R3, #1		; Increment i
	STR R3, R5, #0		; Store the i
	BRnzp FOR_LOOP
;IMPLEMENT ME: stack tear down - prepare to go back to main
TEAR_DOWN
	ADD R6, R6, #2		;  Pop the values
	LDR R5, R6, #0		;  Returns original frame pointer
	LDR R7, R6, #1		; Restores original R7
	LDR R0, R6, #2		; R0 = return value
	ADD R6, R6, #2		; Pops rest of the stuff

	RET


STACK .FILL x6000

.END
