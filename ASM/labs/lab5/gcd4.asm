;
; gcd4.asm - Compute greatest common divisor, 386 version
;
	.MODEL SMALL
    	.STACK 100h
    	.DATA

	X    DD  881790
	Y    DD  188955
	Gcd  DD  ? 		;(F609H  = 62985D)
     
	.CODE
     	.386           		; Enable 386 code
     
	MOV AX,@DATA   			; Program prefix
     	MOV DS,AX      		; Set DS to point to data segment
     	MOV EAX,X       	; Fisrt operand
     	MOV EBX,Y       	; Second operand
       JMP TestNext    	
 Do1:                 		; while (eax != ebx)
                     		; {
                     		; 	if (eax<ebx)
    	JAE Xhigh        	; 		Skip swap 
    	XCHG EAX,EBX      	;   	Swap them         
Xhigh:                		
     	SUB EAX,EBX      	; 	EAX := EAX - EBX                
TestNext:             		;
     	CMP EAX,EBX      		
     	JNE Do1          	; 	Exit if EAX = EBX
Endlp:                		; } /* while */
     	MOV Gcd,EAX      		; gcd = eax;
     	MOV AH,4Ch     		; Set terminate option for int 21h
     	INT 21h        		; Return to DOS (terminate program)
     	    END
