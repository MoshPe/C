.MODEL SMALL
.STACK 100H
	.DATA
		N DB 3
		ARR1 DB 0,0,0
		ARR2 DB 0,0,0	
	.CODE
		MOV AX,@DATA
		MOV DS,AX		; Set DS to point to data segment
		MOV CL,N		; Set the loop action to repeat N times
		XOR CH,CH		; Setting the ch to 0 so have the right N times
		MOV AL,N		
		LEA SI,ARR1		;keeping the relative address of the start of arr1
		JCXZ ALOP		; jump ALOP if cx==0
		LOP:
			MOV [SI],AL		;Putting the numebrs in arr1 according to order
			ADD AL,'0'		;for putting its ascii in arr2
			MOV [SI+3],AL	; save it on arr2 string
			SUB AL,'0'	
			DEC AL			;N=N-1, decreasing the N
			INC SI			;moving the pointer one byte forward
			LOOP LOP
		ALOP:	
		MOV AH,4CH			; Set terminate option for int 21h
		INT 21H				; Return to DOS (terminate program)
		END