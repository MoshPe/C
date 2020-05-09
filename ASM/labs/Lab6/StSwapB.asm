;
;  StSwapB.asm - simple stack example of swap usage: swap AX high and low bytes components (AL and AH).
;
    	.MODEL SMALL
    	.STACK 100h
    	.DATA

   
	.CODE

	ProgStart:
     	MOV 	AX,@DATA                ; Set DS to point ...
     	MOV 	DS,AX                   ; ... to data segment
		
		MOV AX, 1ABCh ; set AX register
		; swap AH AL using stack
		PUSH AX
		MOV BP, SP     ; BP points to the top of the stack( wich is AL)
		MOV AH, [BP]   ; AH is set to BCh
		MOV AL, [BP+1] ; BP+1 points to the second byte in the stack( wich is AH)
		               ; AL is set to 1Ah
		               ; Now AX equals BC1Ah
		POP AX         ; AX is set back to 1ABCh

      	MOV 	AH,4Ch          ; Set terminate option for int 21h
     	INT 	21h             ; Return to DOS (terminate program)
     	END  ProgStart
