;
;  StSwapW.asm - simple stack example of swap usage.
;
    	.MODEL SMALL
    	.STACK 100h
    	.DATA

	x   DW 1ABCh
	y   DW 2DEFh
	
     
	.CODE

	ProgStart:
     	MOV 	AX,@DATA                ; Set DS to point ...
     	MOV 	DS,AX                   ; ... to data segment
		; swap x y using stack
		PUSH x
		PUSH y
		POP  x
		POP  y

      	MOV 	AH,4Ch          ; Set terminate option for int 21h
     	INT 	21h             ; Return to DOS (terminate program)
     	END  ProgStart
