.MODEL SMALL
.STACK 100h
.DATA

	Menu DB 13,10,'Enter 1.push 2.pop 3.min 4.max 5.exit',13,10,'$'
	Buffer DW 0
	StackF DB 13,10,'Stack is FULL',13,10,'$'
	StackE DB 13,10,'Stack is empty',13,10,'$'
	WrongInput DB 13,10,'Wrong input, please try again',13,10,'$'
	Getdown DB 13,10,13,10,'$'

.CODE
.386

	Dos_Print PROC NEAR			; set the value from AL Reg' in PrintHelp string and print 
		MOV DL, AL
		MOV AH, 2
		INT 21h
		RET
	Dos_Print ENDP
	
	Get_Down PROC NEAR			; print Getdown string (enter twice)
		MOV AH, 9
		MOV DX, OFFSET Getdown
		INT 21h
		RET
	Get_Down ENDP

	Print_String PROC NEAR     ; Help us print stuff, we need to set in DX Reg' offset first.
		MOV AH, 9
		INT 21h
		RET
	Print_String ENDP
	
	Get_Num PROC NEAR			; Get the option from the user and check if its currect
		MOV AH, 1h
		INT 21h
		XOR AH, AH
		CALL Get_Down
		CMP AL, '5'
		JA WrongInp
		CMP AL, '1'
		JL WrongInp
		RET
	Get_Num ENDP

	Get_Value PROC NEAR			; Get value from the user and check if its between 0-9
		MOV AH, 1h
		INT 21h
		CMP AL, '9'
		JA WrongInp
		CMP AL, '0'
		JL WrongInp
		RET
	Get_Value ENDP

Main:
		MOV AX, @DATA
		MOV DS, AX

Lop:
		MOV DX, OFFSET Menu
		CALL Print_String
		CALL Get_Num
; Switch
		CMP AL, '5'
		JE EndL
		CMP AL, '4'
		JE Maximum
		CMP AL, '3'
		JE Minimum
		CMP AL, '2'
		JE PopOp
					; Option 1: Push
		CMP SP, 0
		JE StackFull
		CALL Get_Value
		CMP Buffer, 0
		JA MaxMin
		MOV BH, AL
		MOV BL, AL
		PUSH AX
		PUSH BX
		INC Buffer
		JMP Lop
	MaxMin:			; Check if the current value we received is maximum or minimum in the stack
		POP BX		; Get our Max and Min from stack and put it back
		PUSH BX
	MAX:
		CMP AL, BH
		JB MIN
		MOV BH, AL
	MIN:
		CMP AL, BL
		JA AF
		MOV BL, AL
	AF:
		PUSH AX
		PUSH BX
		INC Buffer
		JMP Lop

PopOp:				; Option 2: POP
		CMP Buffer, 0
		JE StackEmp
		POP BX
		POP AX
		CALL Dos_Print
		DEC Buffer
		JMP Lop
Minimum:				; Option 3: Min
		CMP Buffer, 0
		JE StackEmp
		POP BX
		PUSH BX
		MOV AL, BL
		CALL Dos_Print
		JMP Lop
Maximum:				; Option 4: Max
		CMP Buffer, 0
		JE StackEmp
		POP BX
		PUSH BX
		MOV AL, BH
		CALL Dos_Print
		JMP Lop

StackFull:
		MOV DX, OFFSET StackF
		CALL Print_String
		JMP Lop
StackEmp:
		MOV DX, OFFSET StackE
		CALL Print_String
		JMP Lop
WrongInp:
		MOV DX, OFFSET WrongInput
		CALL Print_String
		JMP Lop

EndL:
		CMP Buffer, 0
		JE EndPro
		MOV CX, Buffer
		REP POP AX
EndPro:
	    MOV AH,4Ch     		; Set terminate option for int 21h
     	INT 21h        		; Return to DOS (terminate program)
     	END Main