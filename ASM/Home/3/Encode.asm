;encode.asm
.MODEL LARGE
.STACK 100H																;	ip 
.DATA																	;	cs	2																		
.386																	;	OLD BP 4							
.CODE																	;ip code_array 6 				
;encode(char code_array[], char msg[], char encoded_msg[]);				;cs code array 8
PUBLIC _encode 															;IP MSG 10
	_encode PROC FAR													;	CS MSG 12
	PUSH BP																;	IP ENCODED 14
	MOV BP,SP																;	CS ENCODED 16
	PUSH SI
	PUSH DI
	PUSH ES
	PUSH DS
	PUSH CX
	PUSH BX
	MOV CX,256
	MOV SI,[BP+10]
	MOV ES,[BP+12]	;;;FORMULA ARRAY
	MOV DI,[BP+14] ;;;;NORMAL ARRAY
	MOV DS,[BP+16]
	Body1:
		CMP ES:[SI],BYTE PTR 0
		JE EndProg
		XOR BX,BX
		MOV BL,ES:[SI]
		PUSH SI
		PUSH ES
		MOV SI,[BP+6]
		MOV ES,[BP+8]
		ADD SI,BX
		MOV BL, ES:[SI]
		MOV DS:[DI],BL
		INC DI
		POP ES
		POP SI
		INC SI
	LOOP Body1
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