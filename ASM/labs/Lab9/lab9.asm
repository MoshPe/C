;lab9
.MODEL SMALL
.STACK 100H
.DATA
.386
.CODE
; extern void sum_col(int n,int m,long int*matrix[],long int new_col[])
PUBLIC _sum_col
	_sum_col PROC NEAR
		PUSH BP
		MOV BP,SP
		PUSH BX
		PUSH CX
		PUSH DI
		PUSH SI
		XOR EAX,EAX
		MOV BX,[BP+4]    	; bx = n row
		MOV CX,[BP+6]	 	; cx = m col
		MOV SI,[BP+10]		;reseting the new_col array
		zeroNewCol:
			MOV WORD PTR [SI],0
			ADD SI,4
		LOOP zeroNewCol
		MOV CX,[BP+4]	 ; cx = n row
		MOV SI,[BP+8]				;mat
		PUSH SI
		Body1:
			PUSH CX
			MOV DI,[SI]				;mat[i]
			MOV CX,BX
			MOV SI,[BP+10]			;new_col array
				Body2:
					MOV EAX,[SI]
					ADD [DI],EAX		;new_col[k] += mat[i][j]
					ADD SI,4			;k++
					ADD DI,4			;j++
			LOOP Body2
			POP CX
			POP SI
		ADD SI,4		;i++
		LOOP Body1
	;
		POP SI
		POP DI
		POP CX
		POP BX
		POP BP
		RET
		_sum_col ENDP
	END