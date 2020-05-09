; Add1.asm
;
    .MODEL SMALL
    .STACK 100h
    .DATA
Var1       DW 0
PromptStr DB 'Enter 4 digit number:',13,10,'$'
ResultStr DB 13,10,'XXXX + 1: XXXX',13,10,'$'
Ten       DW 10
                            ;
     .CODE
     MOV AX,@DATA   ; DS can be written to only through a register
     MOV DS,AX      ; Set DS to point to data segment
     MOV AH,9       ; Set print option for int 21h
     MOV DX,OFFSET PromptStr  ;  Set  DS:DX to point to PromptString
     INT 21h                ;  Print DisplayString
;
     MOV Var1,0
;          Read first digit
     MOV AH,1
     INT 21h
     MOV ResultStr[2],AL
     SUB AL,'0'
     MOV AH,0
     MUL Ten
     MOV Var1,AX
     MOV AX,0
;          Read second digit
     MOV AH,1
     INT 21h
     MOV ResultStr[3],AL
     SUB AL,'0'
     MOV AH,0
     ADD AX,Var1
     MUL Ten
     MOV Var1,AX
     MOV AX,0

;           Read third digit
     MOV AH,1
     INT 21h
     MOV ResultStr[4],AL
     SUB AL,'0'
     MOV AH,0
     ADD AX,Var1
     MUL Ten
     MOV Var1,AX
     MOV AX,0
;          Read forth digit
     MOV AH,1
     INT 21h
     MOV ResultStr[5],AL
     SUB AL,'0'
     MOV AH,0
     ADD AX,Var1
;
;  Increment by one

     INC AX
;
;   Convert back to ascii
;
     MOV DX,0
     DIV Ten
     ADD DL,'0'
     MOV ResultStr[15],DL
;
     MOV DX,0
     DIV Ten
     ADD DL,'0'
     MOV ResultStr[14],DL
;
     MOV DX,0
     DIV Ten
     ADD DL,'0'
     MOV ResultStr[13],DL
;
     MOV DX,0
     DIV Ten
     ADD DL,'0'
     MOV ResultStr[12],DL
;
     MOV AH,9
     MOV DX,OFFSET ResultStr
     INT 21h
;
     MOV AH,4Ch       ; Set terminate option for int 21h
     INT 21h       ; Return to DOS (terminate program)
     END  
  

