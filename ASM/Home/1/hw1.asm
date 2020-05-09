	.SMALL MODEL
	.STACK 100H
	.DATA
	First DB 13,10,'Enter first two digit number',13,10,'$'
	Second DB 13,10,'Enter second two digit number',13,10,'$' 
	gcd DB 13,10,'gcd(xx,xx) = xx',13,10,'$'
	Error1 DB 13,10,'Num2 is equal to zero!'
			DB ''please restart the program!',13,10,'$'
	NUM1 DB 0
	NUM2 DB 0
	TEN DB 10
	TWO DB 2
	T DB 0
	
	.CODE
	.386
		MOV AX,OFFSET @DATA
		MOV DS,AX
		MOV AH,9
		MOV DX,OFFSET First
		INT 21H
	;	
		MOV AH,1
		INT 21H
	;	
		MOV GCD[6],AL
		SUB AL,'0'
		XOR AH,AH
		MUL TEN
		MOV NUM1,AL
	;
		MOV AH,1
		INT 21H
		MOV GCD[7],AL
		SUB AL,'0'
		XOR AH,AH
		ADD NUM1,AL
	;
		MOV DX,OFFSET Second
		INT 21H
	;
		MOV AH,1
		INT 21H
	;	
		MOV GCD[10],AL
		SUB AL,'0'
		XOR AH,AH
		MUL TEN
		MOV NUM2,AL
	;
		MOV AH,1
		INT 21H
		MOV GCD[11],AL
		SUB AL,'0'
		XOR AH,AH
		ADD NUM2,AL
	;
		CMP NUM1,NUM2
		JA Skip1
		MOV AL, NUM1
		MOV AH,NUM2
		MOV NUM1,AH
		MOV NUM2,AL
		Skip1:
			MOV CX,5
			JCXZ End
			body:
				CMP NUM1,0
				JE Error
				XOR AX,AX
				MOV AX,NUM1
				DIV NUM2
				MOV T,AL
				MUL TWO
				CMP AL,NUM2
				JB End
				MOV AL,NUM2
				MOV NUM1,AL
				MOV AL,T
				SUB NUM2,AL
			LOOP body
		End:
			XOR AX,AX
			DIV NUM1
			ADD AL,'0'
			ADD AH,'0'
			MOV GCD[16],AL
			MOV GCD[17],AL
			JMP EndProg
		Error:
			MOV AH,9
			MOV DX,OFFSET Error1
			INT 21H
		EndProg:
			MOV AH,4Ch       ; Set terminate option for int 21h
			INT 21h       ; Return to DOS (terminate program)
			END 
			
			
			
			
			
			
			
			
			
			
		
		
		
		