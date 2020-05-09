.MODEL SMALL
.STACK 100H
	.DATA
		NUM DQ 0
		ARR DW 60000,1,1,1
		TEN DD 10
		Print DB 13,10,'Last digit in the sum is: X',13,10,'$'
	.386
	.CODE
		MOV AX,@DATA
		MOV DS,AX	; Set DS to point to data segment
		LEA SI,ARR	;keeping the relative address of the start of arr1
		MOV CX,4	; Set the loop action to repeat 4 times as the arr length
		JCXZ Skip	;Jump to Skip if cx==0
		body:
			XOR EAX,EAX		;resseting the whole EAX
			MOV AX,[SI]		;moving the array values to AX
			MUL EAX			;Multiply EAX by itself to get the power of EAX
			ADD DWORD PTR NUM,EAX		;adding the result to the right size variable(DQ size)
			ADC DWORD PTR NUM +4,EDX	;adding the carry of the previous sum in the right place,4 bytes forward
			ADD SI,2		;adding 2 to si so si will move to bytes as the size of each variable in the array
		LOOP body
		Skip:
		XOR EAX,EAX		;resseting the whole EAX and prep for Div
		XOR EDX,EDX		;resseting the whole EAX and prep for Div
		MOV EAX, DWORD PTR NUM	;moving the variable num to EDX:EAX respectively
		MOV EDX,DWORD PTR NUM +4		
	;
		DIV TEN		;Divide by ten and extract the units
		ADD DL,'0'	;adding ascii'0' for printing
		MOV Print[28],DL	;replacing the 'x' in the array with the units result
	;screen output units result
		MOV AH,9
		MOV DX,OFFSET Print
		INT 21H
	;
		MOV AH,4CH			; Set terminate option for int 21h
		INT 21H				; Return to DOS (terminate program)
		END