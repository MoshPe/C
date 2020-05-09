.MODEL SMALL
.STACK 100h
.DATA
	source DB 12 DUP (0)
	EnterNum DB 13,10,'Enter number N for sqrt(up to 12 digits):',13,10,'$'
	InvaliDigit DB 13,10,'Invalid number, please try again!!',13,10,'$'
	PrintSqrt DB 13,10,'Sqrt(','$' 
	EndSqrt DB ')=','$'
	PrintNum DB 13 DUP ('$')
	Nsize EQU 12
	result DB 7 DUP ('$') 
	C DD ?
	P DD 0
	X DD ?
	Y DD ?
	REM DD 0
	M DD ?
	SPOS DW 0
	RPOS DW 0
	TEN DB 10
.CODE
.386
;Function to remove the 13,10 from the string,the ENTER
	DELETE_ENTER PROC NEAR
	LEA SI,source
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
;
	DigitCheck PROC NEAR
	MOV BL,1
	LEA SI,source
	MOV CX,AX
	isDigit:
		CMP [SI],BYTE PTR '0'
		JB Terminate
		CMP [SI],BYTE PTR '9'
		JA Terminate
		JMP CONTINUE2
	Terminate:
		MOV AH,9		; Set print option for int 21h
		MOV DX,OFFSET InvaliDigit		; Point display string to result
		INT 21H			; Print  chosen message
		MOV BL,0
		JMP TryAgain		
	CONTINUE2:
		INC SI
		LOOP isDigit
	TryAgain:
	RET
	DigitCheck ENDP
	
MAIN:
	MOV AX,@DATA
	MOV DS,AX 		;Set DS to point to data segment
	MOV ES,AX		;Set ES to point to data segment for movsb command
inputNum:
	MOV AH,9
	MOV DX,OFFSET EnterNum	;print the EnterNum string
	INT 21H
	MOV DX,OFFSET source  
	MOV CX,Nsize			;getting input to source string for up to Nsize,12,chars
	MOV AH,3FH
	MOV BX,0
	INT 21H
; Calling to a function to remove the 13,10 from the string
	CALL DELETE_ENTER
	SUB AX,BX				;Decrease the unwanted chars amount from the string length
	CALL DigitCheck	
	CMP BL,BYTE PTR 0
	JE inputNum
	LEA DI,PrintNum
	LEA SI,source
	MOV CX,AX
;copy the source string to printNum string
	REP MOVSB
;check if the sum of the digits is odd or not
	TEST AL,1
;Moving the num 1 byte forward and add 0 at the beginning 
	JZ EVEN1
		MOV CX,AX
		LEA SI,source
		ADD SI,AX
		BODY:
		MOV BL,[SI-1]
		MOV [SI],BL
		DEC SI
	LOOP BODY
	MOV [SI], BYTE PTR '0'
	EVEN1:
;
	XOR EAX,EAX
	LEA SI,source
	ADD SI,SPOS
;	
	CMP [SI], BYTE PTR '0'       ;While(source[spos]!=NULL)
	JB PrintSolution
	;making a 2 digit num    m=[si]*10 +[si+1]
		MOV AL,BYTE PTR [SI]
		SUB AL,'0'
		MUL TEN
		INC SI
		ADD AL,BYTE PTR [SI]
		SUB AL,'0'
		MOV M,EAX
	;c = rem * 100 + m
		MOV EAX,100
		MUL REM
		MOV C,EAX
		MOV EAX,M
		ADD C,EAX
;	
	MOV X,0
	MOV Y,0
;
	While1:
	MOV EAX,Y
	CMP EAX,C       ;while(y<c)
	JAE AfterWhile
		INC X		;x++
		MOV EAX,20
		MUL P		;20*p
		ADD EAX,X	;20*p+x
		MUL X
		MOV Y,EAX	;y=x*(20*p+x)
	JMP While1
	AfterWhile:
;					if(y>c)
	MOV EAX,Y
	CMP EAX,C
	JBE SmallerThanC
		DEC X		;x--
		MOV EAX,20
		MUL P		;20*p
		ADD EAX,X	;20*p+x
		MUL X
		MOV Y,EAX	;y=x*(20*p+x)
	SmallerThanC:
;					putting X result in the result string
	ADD X,'0'
	LEA SI,result
	ADD SI,RPOS
	MOV AL,BYTE PTR X
	SUB X,'0'
	MOV [SI],AL 
;
	ADD SPOS,2		;increase source string position
	INC RPOS		;increase result string position
	MOV EAX,C
	SUB EAX,Y
	MOV REM,EAX		;rem = c – y
	MOV EAX,10
	MUL P 
	ADD EAX,X 
	MOV P,EAX		;p = 10*p + x
;
	JMP EVEN1
	PrintSolution:
;
	MOV AH,9    	; Set print option for int 21h
	MOV DX,OFFSET PrintSqrt		; Point display string to PrintSqrt
	INT 21H			; Print  chosen message
;
	MOV AH,9		; Set print option for int 21h
	MOV DX, OFFSET PrintNum		; Point display string to PrintNum
	INT 21H			; Print  chosen message
;
	MOV AH,9		; Set print option for int 21h
	MOV DX,OFFSET EndSqrt		; Point display string to EndSqrt
	INT 21H			; Print  chosen message
;
	MOV AH,9		; Set print option for int 21h
	MOV DX,OFFSET result		; Point display string to result
	INT 21H			; Print  chosen message
;
	MOV AH,4CH		; Set terminate option for int 21h
	INT 21H			; Return to DOS (terminate program)
	END MAIN