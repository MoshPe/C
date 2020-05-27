;
; lab 8 - asm+c
; ; int  PermutationArray (int arr1[],int arr2[], int size)
.MODEL SMALL
.STACK 100h
.DATA
countArr DW 10 DUP(0)	;set an arr to be count to check if the arr are equal
TWO DW 2
.CODE
PUBLIC _PermutationArray
_PermutationArray PROC NEAR

	PUSH BP
	MOV BP,SP
	
	PUSH DI
	PUSH SI
	MOV CX,10
	MOV SI,0
	L_REST:		;resat the countArr to be all zero
		MOV countArr[SI],0
		ADD SI,2
	LOOP L_REST
	
	MOV DI,[BP+4]		;set DI to point the arr1 in the first place
	MOV SI,[BP+6]		;set SI to point the arr2 in the first place
	MOV CX,[BP+8]
	
	loopi:
		MOV AX,[SI]			
		MUL TWO		
		MOV BX,AX
		INC countArr[BX]	;add 1 to the countArr 
		
		MOV AX,[DI]			
		MUL TWO		
		MOV BX,AX
		DEC countArr[BX]	;sub 1 from the countArr
		
		ADD SI,2
		ADD DI,2
	LOOP loopi
	
	MOV CX,10
	MOV SI,0
	Check_ifEqual:
		CMP countArr[SI],0
		JE NEXT
		;If arr1[si]!=0 the the arrays are not Permutation
		MOV AX,0
		JNE EXIT
	   NEXT:
		ADD SI,2
	LOOP Check_ifEqual
	MOV AX,1
	
	EXIT:
	POP SI
	POP DI
	POP BP
	RET
_PermutationArray ENDP
END