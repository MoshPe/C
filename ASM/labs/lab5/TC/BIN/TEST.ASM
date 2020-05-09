;q2.asm
.MODEL SMALL
.STACK 100H
.DATA
	N DW 11
	ARR DW 1234h, 5678h, 0ff11h, 1111h, 2222h, 3333h, 4444h, 5555h, 6666h, 7777h, 8888h
	Signed DB 13,10,'Max for signed array is:XXXXXX',13,10,'$'
	UnSigned DB 13,10,'Max for unsigned array is:XXXXX',13,10,'$'
	MAX DW ?
	TEN DB 10
	.386
	.CODE
		MOV AX,@DATA
		MOV DS,AX
		MOV ES,AX
		MOV CX,N
		LEA SI,ARR
		MOV BX,[SI] ;unsigned
		MOV AX,[SI] ;signed
		ADD SI,2
		JCXZ Skip
			body:
				CMP AX,[SI]
				JG SignedNext
				MOV AX,[SI]
				SignedNext:
				CMP BX,[SI]
				JA UnsignedNext
				MOV BX,[SI]
				UnsignedNext:
				ADD SI,2
	Loop body
		Skip:
		MOV MAX,AX
		LEA SI,Signed
		ADD SI,28
		LEA DI,MAX
		MOV CX,5
		REP MOVSB
		JNS NotSignPrint
		MOV [SI-1],BYTE PTR 2DH ;-
		NotSignPrint:
;
		
		LEA SI,UnSigned
		ADD SI,33
		MOV AX,BX
		MOV CX,5
		JCXZ UnSignedSkip
			PrintUnSigned:
			DIV TEN
			ADD AH,'0'
			MOV [SI],AH
			XOR AH,AH
			DEC SI
		Loop PrintUnSigned
		UnSignedSkip:
;
	MOV AH,9
	MOV DX, OFFSET Signed
	INT 21H
;
	MOV AH,9
	MOV DX, OFFSET UnSigned
	INT 21H
;
	MOV AH,4CH
	INT 21H
	END