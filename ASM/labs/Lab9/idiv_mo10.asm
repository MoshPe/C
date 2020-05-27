;  idiv_m10.asm - Assembler implementation of
;                         C-callable function idiv_mod32.
;
    .MODEL LARGE
    .CODE
    .386
    ; Implementation of C callable function ...
    ;    ...  int idiv_mod32(long int Num, long int Denom,
    ;                         [BP+6]         [BP+10]
    ;  long int *Q,    long int *Rem)
    ;      [BP+14]       [BP+18]
    ;  Compute Q := |_ Num / Denom _|  ,Rem := MOD(Num, Denom)
    ;  function  idiv_mod32  returns 0 if Denom = 0 (illegal ..
    ;  ... division by zero), 1 otherwise
    ;
     PUBLIC _idiv_mod32
_idiv_mod32  PROC FAR
     PUSH BP        ; Preserve BP
     MOV BP,SP      ; Set BP to point to Parameter area
     PUSH SI        ; Preserve register variables
     PUSH DI        ;
     PUSH ES
;
     MOV ESI,[BP+10]  ; ESI := Denom
     CMP ESI,0     ; Denom = 0 ?
     JNE Cont       ; No, continue regular operation
           ; Yes, Denom = 0
         MOV AX,0    ; Return value := 0
         JMP Done            ; Skip following code
Cont:      ; Denom <> 0
     MOV EAX,[BP+6]       ; EAX := Num
     CDQ                 ; EDX:EAX := EAX
     IDIV ESI             ; EAX := EDX:EAX / ESI,  EDX := MOD(EAX,ESI)
     MOV  DI,[BP+14]      ; DI := Offset Q
     MOV  ES,[BP+16]      ; ES := Seg Q
     MOV  ES:[DI],EAX        ; *Q := AX
     MOV  DI,[BP+18]     ; DI := Offset Rem
     MOV  ES,[BP+20]      ; ES := Seg Rem
     MOV  ES:[DI],EDX        ; *Rem := DX
     MOV  AX,1   ; Ensure return value := 1
Done:
;
     POP ES    ;
     POP DI    ; Restore register variables
     POP SI    ;
     POP  BP             ; Restore BP register
     RET
_idiv_mod32  ENDP
     END

