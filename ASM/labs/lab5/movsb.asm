;  	movsb.asm - demonstrate movsb
    	.MODEL SMALL
    	.STACK 100h
    	.DATA

	DisplayString DB 'Hello World!',13,10,'$'
	NewStr        DB 'UVWXYZ'
     	.CODE

ProgStart:
     	MOV AX,@DATA				; DS can be written to only through a register
     	MOV DS,AX					; Set DS to point to data segment
     	MOV ES,AX
     	MOV SI,OFFSET NewStr 		; or LEA SI, NewStr
     	LEA DI,DisplayString 		; or MOV DI,OFFSET DisplayString
     	MOV CX,6
     	REP MOVSB
     	MOV AH,9         			; Set print option for int 21h
     	MOV DX,OFFSET DisplayString ;Set DS:DX to point to DisplayString
     	INT 21h  					;  Print DisplayString
     	MOV AH,4Ch       			; Set terminate option for int 21h
     	INT 21h       				; Return to DOS (terminate program)
     	END ProgStart 
