;q2.asm  - GradeExplener 
   .MODEL SMALL
   .STACK 100H
   .DATA
	EnterGrade DB 'Please enter your grade ',13,10,'$'
	A DB 13,10 
                DB 'Very Good',13,10,'$'
	B DB 13,10
                DB 'Good',13,10,'$'
	C DB 13,10 	
                 DB 'Not Good',13,10,'$'
	F DB 13,10
                 DB 'Very Bad. You Failed',13,10,'$'
 	Error DB 13,10
                 DB 'Input Error!!!',13,10,'$'
.code
ProgStart:	
		MOV AX,@DATA
		MOV DS,AX
        MOV DX,OFFSET EnterGrade  ; DX point to EnterGrade
        MOV AH,9                  ; set print for int 21h
        INT 21H                   ; Print EnterGrade
        MOV AH,1                  ; Get character function
		INT 21H					  ; Get a single character from keyboard
		CMP AL,'A'				  ; If AL = 'A' then go to IsA
		JE isA
		CMP AL,'B'				  ; If AL = 'B' then go to IsB
		JE isB
		CMP AL,'C'				  ; If AL = 'C' then go to IsC
		JE isC
		CMP AL,'F'			      ; If AL = 'F' then go to IsF
		JE isF
        MOV DX,OFFSET Error		  ; Any other input point to Error string
        JMP DisplayGrade
isA:
	MOV DX,OFFSET A				  ; Point to A string
	JMP DisplayGrade
isB:
	MOV DX,OFFSET B				  ; Point to B string
	JMP DisplayGrade
isC:
	MOV DX,OFFSET C				  ; Point to C string
	JMP DisplayGrade
isF:
	MOV DX,OFFSET F				  ; Point to F string
	JMP DisplayGrade
DisplayGrade:
	MOV AH,9					  ; Print command for 21h exe
	INT 21H						  ; Execute the printing command
	MOV AH,4CH					  ; End program
	INT 21H
	END ProgStart
