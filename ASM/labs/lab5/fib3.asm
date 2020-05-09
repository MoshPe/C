;
; fib3.asm - Compute fibo
;
    .MODEL SMALL
    .STACK 100h
    .DATA
n       DW  20
Fibo_n  DD  ?
     .CODE
     .386           ;  Enable 386 code
     MOV AX,@DATA   ; Program prefix
     MOV DS,AX      ; Set DS to point to data segment
                    ;
     MOV CX,n       ;            *****  C  *****
     SUB CX,2       ;             cx = n-2;
     JS  Endlp      ;
     MOV EBX,1       ;            
     MOV EDX,1       ;             eax = ebx = edx = 1;
     MOV EAX,1       ;
     JCXZ EndLp      ;                     
Do1:                 ;             for(cx = n-3; cx > 0; cx-- )
     MOV EAX,EBX     ;               {
     ADD EAX,EDX     ;                 eax = ebx + edx;
                     ;                 edx = ebx;
     MOV EDX,EBX     ;                 ebx = eax;
     MOV EBX,EAX      ;              }
                      ;
TestNext:             ;
     LOOP Do1         ;
                      ;
Endlp:                ;                                          
     MOV Fibo_n,EAX   ; Store result     fibo_n = eax                    
                    ;
     MOV AH,4Ch     ; Set terminate option for int 21h
     INT 21h        ; Return to DOS (terminate program)
     END  
  


   


