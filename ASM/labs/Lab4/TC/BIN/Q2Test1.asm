.MODEL SMALL
.STACK 100H
	.DATA
		NUM DQ 0
		ARR DW 1,23,450,67
		TEN DD 10
		TEN1 DB 10
		Print DB 13,10,'Last digit in the sum is: X',13,10,'$'
	.386
	.CODE
		MOV AX,@DATA
		MOV DS,AX	
		LEA SI,ARR
		MOV CX,4
		JCXZ Skip
		body:
			XOR EAX,EAX
			MOV AX,[SI]
			MUL EAX
			ADD DWORD PTR NUM,EAX
			ADC DWORD PTR NUM +4,EDX	
			ADD SI,2
		LOOP body
		Skip:
		XOR EAX,EAX
		MOV EAX, DWORD PTR NUM +1
		XOR EDX,EDX		
	;
		DIV TEN
		MOV AL,DL
		MUL TEN
		ADD AL,BYTE PTR NUM
		DIV TEN
		ADD AH,'0'
		MOV Print[28],DL
	;
		MOV AH,9
		MOV DX,OFFSET Print
		INT 21H
	;
		MOV AH,4CH
		INT 21H
		END