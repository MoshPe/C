; find the Greatest common divisor between two numbers
	.MODEL SMALL
	.STACK 100h
	.DATA
	TEN DB 10
	TWO DB 2
	FirstN DB 13,10,'Enter first two digit number',13,10,'$'
	SecoN DB 13,10,'Enter second two digit number',13,10,'$'
	GCD DB 13,10,'gcd(XX, XX) = XX',13,10,'$'
	q1 DB ?
	q2 DB ?
	T DB ?
	.CODE
	MOV AX,@DATA
	MOV DS,AX
			        ; get the first number 
FirstNum:
	MOV AH, 9       ; output first Number string 
	MOV DX, OFFSET FirstN
	INT 21H
	MOV AH, 1       ; get the first digit of the first number
	INT 21h
	MOV GCD[6], AL  ; place it in GCD string
	SUB AL,'0'      ; subtract the ASCII value of the number
	MUL TEN         ; multiplie by 10
	MOV q1, AL
	MOV AH, 1       ; get the second digit of the first number
	INT 21h
	MOV GCD[7], AL
	SUB AL,'0'
	ADD q1,AL     ; add the second digit to the number
	                ; get the second number
SecondNum:
	MOV AH, 9       ; output Second Number string
	MOV DX, OFFSET SecoN
	INT 21H
	MOV AH, 1       ; get the first digit of the second number
	INT 21h
	MOV GCD[10], AL ; place it in GCD string
	SUB AL,'0'
	MUL TEN
	MOV q2, AL
	MOV AH, 1       ; get the second digit of the srcond number
	INT 21h
	MOV GCD[11], AL
	SUB AL,'0'
	ADD q2,AL     ; add the second digit to the number
Compere:
	MOV AL,q1
	CMP AL,q2     ; if q1 >= q2 jump to set label
	JAE Set         ; "else" replace their values
	MOV AH,q2
	MOV q1, AH
	MOV q2, AL
Set:                ; set in cx value for the loop 
	MOV CX,5
Calc:
	CMP q2,0        ; compare between q2 and 0
	JE SetGCD       ; if equal, jump to label SetGCD
	MOV AL, q1      ; al = q1
	CBW             ; spred al to ah
	DIV q2          ; divide ax by q2     
	MOV T, AH       ; set the remain in T
	MOV AL,T        
	MUL TWO         ; 
	CMP AL,q2
	JBE Next        ; if AL(2*T)<=q2 jump to label Next
	                ; "else" set T=q2-T
	MOV AL, q2      
	SUB AL, T
	MOV T, AL
Next:
	MOV AL, q2      ; q1 = q1
	MOV q1, AL
	MOV AH, T       ; q1 = T
	MOV q2, AH
	LOOP Calc       ; loop Calc label - CX times (5)
SetGCD:
	MOV AL, q1
	CBW             ; spred al to ah
	DIV TEN         ; ax / 10 - for answer with 1 digit, we divide the remain with 10
	ADD AL, '0'     ; add ascii value to the numbers
	ADD AH, '0'
	MOV GCD[16], AL ; we set the whole part first
	MOV GCD[17], AH ; then the "remain" of the divide
PrintGCD:           ; printing GCD string
	MOV AH, 9
	MOV DX, OFFSET GCD
	INT 21H
	MOV AH,4Ch               ; Set terminate option for int 21h
    INT 21h                  ; Return to DOS (terminate program)
    END
