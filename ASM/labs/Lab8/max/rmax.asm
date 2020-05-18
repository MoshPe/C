;
;  rmax.asm
;
;
   .MODEL SMALL
   .CODE
;
;  extern int rmax(int arr[], int n);
;                   [BP+4]    [BP+6]

   PUBLIC _rmax
_rmax PROC NEAR
    PUSH BP
    MOV BP,SP
    MOV AX,[BP+6]
    MOV BX,[BP+4]
    CMP AX,1
    JNE Cont
    MOV AX,[BX]
    JMP ToRet
Cont:   
    DEC AX
    PUSH AX
    PUSH BX
    CALL _rmax
    POP BX
    POP CX
    SHL CX,1
    ADD BX,CX
    CMP AX,[BX]
    JG ToRet
      MOV AX,[BX]
ToRet:
    POP BP
    RET
_rmax  ENDP

     END




