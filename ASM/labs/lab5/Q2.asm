;
; finding max number in array for signed and unsigned numbers
;
.MODEL SMALL
.STACK 100h
.DATA
	ARR DW 8234h, 8678h, 0ff11h, 8111h, 8222h, 8333h, 8444h, 8555h, 8666h, 8777h, 8888h
	N DW 11
	TEN DW 10
	TEMP DW ?
	UNSIGNED DB 13,10,'Max for unsigned array is:      ',13,10,'$'
	SIGNED DB 13,10,'Max for signed array is:      ',13,10,'$'
.CODE
	MOV AX, @DATA
	MOV DS, AX
	MOV CX, N
	CMP CX, 0           
	JCXZ ProgEnd       ; if N is zero it means the array size is zero
	MOV BX, ARR        ; set in BX and DX the first value in ARR (BX represent max for signed and DX max for unsigned)
	MOV DX, ARR
	CMP CX, 1          ; if the size of ARR is 1, the max for signed and unsigned is the first cell
	JE SETLOPu         ; so we jump to SETLOPu lable
	MOV SI, OFFSET ARR+2    ; set SI pointer to the second ARR variable
	DEC CX     ; already set the value of the ARR cell in BX and DX, we need to set loop to N-1 times
MAX:                   ; finding the max value for signed and unsigned in ARR
; SIGNED
	CMP [SI], BX       ; if the value in cell [SI] is lower or equal to the value in BX, jump to SNEXT lable
	JLE SNEXT    ; JLE for signed
	MOV BX, [SI]       ; if not, BX = [SI]
SNEXT:
; UNSIGNED
	CMP [SI], DX
	JBE UNEXT    ; JBE for unsigned
	MOV DX, [SI]
UNEXT:
	ADD SI, 2    ; encounter the pointer to the next cell
LOOP MAX
		; we found the max value of the ARR for signed and unsigned
		;
		; set the values in the string
SETLOPu:                              ; set the loop for the UNSIGNED string
	MOV CX, 5
	LEA SI, UNSIGNED + 34
	MOV AX, DX
ADDTOSTRu:
	XOR DX, DX
	DIV TEN
	ADD DL, '0'   ; add the value of 0 for the decimal value
	MOV [SI], DL
	SUB SI, 1
LOOP ADDTOSTRu
SETLOPS:                              ; set the loop for the SIGNED string
	MOV CX, 5
	LEA SI, SIGNED + 32
	MOV AX, BX
	XOR BX, BX          ; format BX for later use
	OR AX, 0            ; using OR operation to change SF for the value in AX
	JNS ADDTOSTRS
	NEG AX              ; if SF is 1, we switch AX to the negative value 
	MOV BL, 1           ; save in BL 1 as a flag for negative number
ADDTOSTRS:
	XOR DX, DX
	IDIV TEN            ; idiv for signed
	ADD DL, '0'
	MOV [SI], DL
	SUB SI, 1
LOOP ADDTOSTRS
	CMP BL, 1           ; checking our flag to see if the number is negative
	JNE USIG
	MOV [SI], BYTE PTR 2Dh ; -    ; if our flag equal 1 we put in the string -
USIG:                          ; printing unsigned string
	MOV AH, 9h
	MOV DX, OFFSET UNSIGNED
	INT 21h
SIG:                           ; printing signed string
	MOV AH, 9h
	MOV DX, OFFSET SIGNED
	INT 21h
ProgEnd:                       ; end of program
	MOV AH, 4Ch
	INT 21h
	END