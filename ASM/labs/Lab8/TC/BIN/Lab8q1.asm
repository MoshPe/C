;lab8
.MODEL SMALL
.STACK 100H
.DATA
	isPermutation DW 10 DUP(0)
.CODE
	PUBLIC _PermutationArray
	_PermutationArray PROC NEAR
		PUSH BP
		MOV BP,SP
		PUSH CX
		PUSH BX
		PUSH SI
		PUSH DI
		MOV AX,1
		MOV SI,[BP+4]
		LEA DI,isPermutation
		MOV BX,[BP+8]
		MOV CX,BX
			Body1:
				ADD DI,[SI]
				ADD DI,[SI]
				INC BYTE PTR [DI]
				SUB DI,[SI]
				INC SI
			LOOP Body1
		MOV SI,[BP+6]
		MOV CX,BX
			Body2:
				ADD DI,[SI]
				ADD DI,[SI]
				DEC BYTE PTR [DI]
				SUB DI,[SI]
				INC SI			
			LOOP Body2
		MOV CX,10
			Body3:
			CMP BYTE PTR [DI],0
				JNE NEXT
				MOV AX,0
				JMP Skip
			NEXT:
			LOOP Body3
		Skip:
		POP DI
		POP SI
		POP BX
		POP CX
		POP BP
		RET
	_PermutationArray ENDP
	END