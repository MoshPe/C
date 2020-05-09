;
; gcd3.asm - Compute greatest common divisor, 386 version
;
    .MODEL SMALL
    .STACK 100h
	.DATA

	X    DD  881790
	Y    DD  188955
	Gcd  DD  ?
     
    .CODE
	.386				;  Enable 386 code
     
	MOV AX,@DATA		; Program prefix
	MOV DS,AX			; Set DS to point to data segment
    MOV EAX,X			;  Fisrt operand
    MOV EBX,Y			;  Second operand        
Do1:					;                           while (eax != ebx)
    CMP EAX,EBX			;                           {
    JE  Endlp			; Exit if EAX = EBX,               if (eax<ebx)
    JAE Xhigh			; Skip XCHG IF EAX=>EBX            {
    XCHG EAX,EBX		; EAX < EBX, Swap them					temp = eax;
						;										eax = ebx;
						;										ebx = temp;
Xhigh:					;                                  }
     SUB EAX,EBX		; EAX := EAX - EBX				   eax = eax - ebx;
     JMP Do1			;
Endlp:					;                           } /* while */
     MOV Gcd,EAX		; Store result              gcd = eax;
						;
     MOV AH,4Ch			; Set terminate option for int 21h
     INT 21h			; Return to DOS (terminate program)
     END  
  


