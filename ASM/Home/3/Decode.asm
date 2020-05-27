;decode.asm
.MODEL LARGE
.STACK 100H																;	ip 
.DATA																	;	cs	2																		
.386																	;	OLD BP 4							
.CODE																	;ip code_array 6 				
;  decode(code_array, encoded_msg, decoded_msg);						;cs code array 8
PUBLIC _encode 															;IP encMsg 10
	_encode PROC FAR													;	CS encMsg 12
	PUSH BP																;	IP deCODED 14
	MOV BP,SP																;	CS deCODED 16
	PUSH SI
	PUSH DI
	PUSH ES
	PUSH DS
	PUSH CX
	PUSH BX

	MOV SI,[BP+10]	;;; encMsg
	MOV ES,[BP+12]	;;;
	MOV DI,[BP+14] ;;;;decoded ARRAY
	MOV DS,[BP+16]
	Body1:
		CMP ES:[SI],BYTE PTR 0
		JE EndProg
		PUSH SI
		PUSH ES
		MOV SI,[BP+6]
		MOV ES,[BP+8]
			Body2:
			CMP ES:[SI],DS:[DI]
			MOV AX,256
			SUB AX,CX
			LOOP Body2
		POP ES
		POP SI
		MOV AL,ES:[SI]
		MOV DS:[DI],BL
		INC DI
		INC SI
	JMP Body1
	EndProg:
	POP BX
	POP CX
	POP DS
	POP ES
	POP DI
	POP SI
	POP BP
	RET
	_encode ENDP
	END