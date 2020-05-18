;  idiv_mo6.asm - Assembler implementation of 
;                         C-callable function idiv_mod.
;
    .MODEL SMALL
    .CODE
    .386
    ; Implementation of C callable function ...
    ;    ...  int idiv_mod(long int Num, long int Denom,
    ;                        [BP+4]         [BP+8]  
    ;  long int *Q,    long int *Rem)
    ;      [BP+12]    [BP+14]    
    ;  Compute Q := |_ Num / Denom _|  ,Rem := MOD(Num, Denom)
    ;  function  idiv_mod  returns 0 if Denom = 0 (illegal ..
    ;  ... division by zero), 1 otherwise
    ;
     PUBLIC _idiv_mod
_idiv_mod  PROC NEAR
     PUSH BP        ; Preserve BP
     MOV BP,SP      ; Set BP to point to Parameter area
     PUSH SI        ; Preserve register variables
     PUSH DI        ;
;
     MOV ESI,[BP+8]  ; SI := Denom
     CMP ESI,0     ; Denom = 0 ?
     JNE Cont       ; No, continue regular operation
	   ; Yes, Denom = 0
	 MOV AX,0    ; Return value := 0
	 JMP Done            ; Skip following code
Cont:      ; Denom <> 0
     MOV EAX,[BP+4]       ; EAX := Num
     CDQ                 ; EDX:EAX := EAX 
     IDIV ESI             ; EAX := EDX:EAX / ESI,  EDX := MOD(EAX,ESI)
     MOV  DI,[BP+12]      ; DI := Offset Q
     MOV  [DI],EAX        ; *Q := AX
     MOV  DI,[BP+14]     ; DI := Offset Rem
     MOV  [DI],EDX        ; *Rem := DX
     MOV  AX,1   ; Ensure return value := 1
Done:
;
     POP DI    ; Restore register variables
     POP SI    ;
     POP  BP             ; Restore BP register
     RET
_idiv_mod  ENDP
     END





