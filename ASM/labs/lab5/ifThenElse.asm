.MODEL SMALL
.STACK 100h
.DATA
	Flag1 DW 3

.CODE
	MOV AX,@DATA			; Program prefix
     	MOV DS,AX			; Set DS to point to data segment
        MOV AX,1      
     	MOV BX,1      
     	MOV DX,1      
     	MOV CX,1      
     	MOV SI,5      
     	MOV DI,6      

		CMP AX,BX			;     if( ((AX == BX) && (CX == DX))
  		JNE Or1          
  		CMP CX,DX        
  		JNE Or1           
  		JMP Then1         
Or1:						;	     || (SI == DI) || (SP == BP) )
     	CMP SI,DI
     	JE Then1
     	CMP SP,BP
     	JE  Then1
     	JMP Else1
Then1:		    			;     then
     	MOV Flag1,1			;		flag = 1	
     	JMP Finish
Else1:						;     else
     	MOV Flag1,0			;		flag = 0
Finish:
     	MOV AH,4Ch			; Set terminate option for int 21h
     	INT 21h				; Return to DOS (terminate program)
     	END
