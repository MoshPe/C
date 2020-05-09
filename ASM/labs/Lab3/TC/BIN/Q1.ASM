;q1.asm
;
.MODEL SMALL
.STACK 100h
.DATA
	NUM DW 0
	DIG DW 0
	Ten DW 10
	Error1 DB 13,10,'Division error',13,10,'$'
	EnterNum DB 'Please Enter Number (from 00 up to 99):',13,10,'$'
	EnterDig DB 13,10,'Please Enter Digit (from 0 up to 9):',13,10,'$'
	RoundUp DB 13,10,'The result should be round up','$'
	RoundDown DB 13,10,'The result should be round down','$'
	Claculates DB 13,10,'XX^2 mod X = X',13,10,'$'
.CODE
	MOV AX,@DATA
	MOV DS,AX
	MOV AH,9
	MOV DX, OFFSET EnterNum
	INT 21H
;
	MOV AH,1
	INT 21H
	MOV Claculates[2],AL
	SUB AL,'0'
	XOR AH,AH
	MUL Ten
	MOV NUM,AX
;	
	MOV AH,1
	INT 21H
	MOV Claculates[3],AL
	SUB AL,'0'
	XOR AH,AH
	ADD NUM,AX
	XOR AX,AX
;
	MOV AH,9
	MOV DX, OFFSET EnterDig
	INT 21H
	MOV AH,1
	INT 21H
	MOV Claculates[11],AL
	CMP AL,'0'
	JE Error
	SUB AL,'0'
	XOR AH,AH
	MOV DIG,AX
;
	XOR DX,DX
	MOV AX,NUM
	MUL NUM
	DIV DIG
	ADD DL,'0'
	MOV Claculates[15],DL	
	SUB DL,'0'
	MOV AX,DX
	MOV DX,2
	MUL DX
;
    CMP AX,DIG
    JAE RoundUp1
	MOV AH,9
	MOV DX, OFFSET Claculates
	INT 21H
	MOV AH,9
	MOV DX, OFFSET RoundDown
	INT 21H
	JMP End1
;
RoundUp1:
	MOV AH,9
	MOV DX, OFFSET Claculates
	INT 21H
	MOV AH,9
	MOV DX, OFFSET RoundUp
	INT 21H
	JMP End1		
Error:
	MOV AH,9
	MOV DX, OFFSET Error1
	INT 21H
End1:
	MOV AH,4CH
	INT 21H
	END