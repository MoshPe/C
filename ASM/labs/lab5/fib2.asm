;
; fib2.asm - Compute fibo
;
    .MODEL SMALL
    .STACK 100h
    .DATA
n       DD  20
Fibo_n  DD  ?
     .CODE
     .386           ;  Enable 386 code
     MOV AX,@DATA   ; Program prefix
     MOV DS,AX      ; Set DS to point to data segment
                    ;
     MOV ECX,n       ;             *****  C  *****
     MOV ESI,3       ;             ecx = n;
     MOV EBX,1       ;        
     MOV EDX,1       ;             ebx = edx = 1;
     JMP TestNext    ;                     
Do1:                 ;             for(esi = 3; esi <= ecx; esi++)
     MOV EAX,EBX     ;               {
     ADD EAX,EDX     ;                 eax = ebx + edx;
                     ;                 edx = ebx;
     MOV EDX,EBX     ;                 ebx = eax;
     MOV EBX,EAX      ;              }
                      ;
     INC ESI          ;
                      ;
TestNext:             ;
     CMP ESI,ECX      ;
     JNA Do1          ;
Endlp:                ;                                          
     MOV Fibo_n,EAX   ; Store result    fibo_n = eax
                    ;
     MOV AH,4Ch     ; Set terminate option for int 21h
     INT 21h        ; Return to DOS (terminate program)
     END  
  


   


