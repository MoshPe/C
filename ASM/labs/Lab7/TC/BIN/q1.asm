;Lab7q1
.MODEL SMALL
.STACK 100H

.DATA
	SUM DD 0
	inputNum DB 13,10,'Please enter number 2 numbers:',13,10,'$'
	notAmicable DB 13,10,'Not Amicable Numbers',13,10,'$'
	Amicable DB 13,10,'Amicable Numbers',13,10,'$'
	NUM DB 12 DUP(0)
	NUM11 DD 0
	NUM22 DD 0 
	numSize EQU 12
	DIVIDE DD 0
	TEN DD 10
	X DD 0
	
.CODE
.386
	DELETE_ENTER PROC NEAR
	LEA SI,NUM
	ADD SI,AX
	DEC SI   		;point to the last char in the string
	MOV CX,2		;The "ENTER" string is assembled by 2 chars, 13 and 10
	XOR BL,BL
	EnterCheck:			;the loop goes through the last 2 chars and check their value
		CMP [SI],BYTE PTR '0'
		JB DELETE
		CMP [SI],BYTE PTR '9'
		JA DELETE
		JMP CONTINUE1
	DELETE:
		MOV [SI],BYTE PTR 0
		INC BL		;counts the amount of times that the loop deleted a char
	CONTINUE1:
		DEC SI
		LOOP EnterCheck
	RET
	DELETE_ENTER ENDP

getNum PROC NEAR
;Input num 
	PUSH ECX
	MOV DX,OFFSET NUM
	MOV CX,numSize		;getting input to num string for up to Nsize,4,chars
	MOV AH,3FH
	MOV BX,0
	INT 21H
	CALL DELETE_ENTER
	MOV CX,AX
	DEC CX
	LEA SI,NUM
	XOR EAX,EAX
	Body1:
		MOV BL,[SI]
		CMP BL,BYTE PTR 0
		JE NEXT
		SUB BL,'0'
		MUL TEN
		ADD EAX,EBX
		NEXT:
		INC SI
	LOOP Body1
	POP ECX
RET
getNum ENDP

PNum PROC NEAR
;calculate the sum of self divides 
	PUSH BP
	PUSH ECX
	MOV SUM, DWORD PTR 0
	MOV BP,SP
	MOV EAX,[BP+8]
	MOV X,EAX
	MOV ECX,EAX
	SHR ECX,1
	Body:
		JECXZ Skip1
		XOR EDX,EDX
		MOV EAX,X
		MOV DIVIDE,ECX
		DIV DIVIDE
		CMP EDX, DWORD PTR 0
		JNE Skip
		ADD SUM,ECX
	Skip:
	LOOP Body
	Skip1:
	MOV EAX,SUM
	POP ECX
	POP BP
RET 4
PNum ENDP


Main:
	MOV AX,@DATA
	MOV DS,AX 		;Set DS to point to data segment
	MOV ES,AX		;Set ES to point to data segment for movsb command
	MOV AH,9
	MOV DX,OFFSET inputNum	;print the EnterNum string
	INT 21H
;
	CALL getNum
	MOV NUM11,EAX
	PUSH EAX
	CALL PNum
	MOV SUM,EAX		;saving the sum of divisors in sum
;
	CALL getNum
	MOV NUM22,EAX
;
	CMP SUM,EAX		; check if the sum == num22
	JNE Not_Amicable
;
	PUSH EAX
	CALL PNum
;
	CMP NUM11,EAX
	JNE Not_Amicable
;
	MOV AH,9
	MOV DX,OFFSET Amicable	;print the EnterNum string
	INT 21H
	JMP EndMain
;
	Not_Amicable:
	MOV AH,9
	MOV DX,OFFSET notAmicable	;print the EnterNum string
	INT 21H
;	
EndMain:
MOV AH,4CH		; Set terminate option for int 21h
	INT 21H			; Return to DOS (terminate program)
	END Main