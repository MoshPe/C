;
;  stack3.asm - demonstrate hardware stack usage.
;
    	.MODEL SMALL
    	.STACK 100h
    	.DATA

	Separator       EQU '#'
	DisplayString   DB  64 DUP('$')
	Numbs           DB '0123456789'
	Stack_Size      DW (?)
     
	.CODE

	ProgStart:
     	MOV 	AX,@DATA                ; Set DS to point ...
     	MOV 	DS,AX                   ; ... to data segment
       	MOV 	DI,OFFSET DisplayString ; Have DI point to start ...
                                    	 ; ... of DisplayString
     	MOV 	Stack_Size,SP           ; Save stack size
       	XOR 	BX,BX                   ;  BX := 0;
     	MOV 	CX,5                    ;  Size(Numbs) = 2*5
StackStore:
     	MOV 	DX,WORD PTR Numbs[BX]   ; Read two bytes in Numbs
      	PUSH 	DX                      ; Store in Stack
       	MOV 	[DI],DX                 ; Store in DisplayString
      	ADD 	BX,2            ; BX point to next word in Numbs
      	ADD 	DI,2            ; DI point to next available position
     	LOOP 	StackStore      ; Repeat 5 times
     	MOV 	DL,Separator            
     	MOV 	[DI],DL                 ; Store '#' ...
    	INC 	DI                      ;   ... to separate
        MOV 	CX,Stack_Size           ;
     	SUB 	CX,SP                   ; Set CX to equal ...
                                    	 ;  .. number of relevant ...
                                    	 ;  ... bytes in stack
     	MOV 	BP,SP                   ;
StackLoop1:                          	 ; Print Stack downward
      	MOV 	BL,[BP]                 
      	INC 	BP                      
        MOV 	[DI],BL         ; Store in DisplayString
       	INC 	DI              ; point to next available position
     	LOOP 	StackLoop1              
       	MOV 	DL,Separator            
     	MOV 	[DI],DL       ; Store '#' ...
     	INC 	DI            ;   ... to separate
     	MOV 	BX,[BP-3]     ;  Retrieve eighth and ninth bytes ...
     	MOV 	[DI],BX       ;   ... in stack
     	ADD 	DI,2                    
      	MOV 	DL,Separator            
     	MOV 	[DI],DL         ; Store '#' ...
     	INC 	DI              ;   ... to seperate
      	MOV 	BP,SP           ;  Retrieve third and forth bytes ...
     	MOV 	BX,[BP+2]       ;   ... in stack
     	MOV 	[DI],BX          
     	ADD 	DI,2                   
     	MOV 	DL,Separator            
     	MOV 	[DI],DL         ; Store '#' ...
     	INC 	DI              ;   ... to seperate
     	MOV 	CX,Stack_Size           
     	SUB 	CX,SP           ; Set CX to equal ...
                               ;  ... number of relevant ...
                               ;  ... bytes in stack
     	MOV 	BP,Stack_Size            
     	DEC 	BP              ; Set BP to point to last ...
                               ; ... byte in stack
StackLoop2:                    ; Print stack, upward
        MOV 	BL,[BP]              	   
        DEC 	BP              ;
        MOV 	[DI],BL         ; Store in DisplayString
        INC 	DI              ; point to next available position
     	LOOP 	StackLoop2              
                                     	
     	MOV 	AH,9            ; Set print option for int 21h
     	MOV 	DX,OFFSET DisplayString ;  Set  DS:DX to point to DisplayString
     	INT 	21h             ;  Print DisplayString
      	MOV 	AH,4Ch          ; Set terminate option for int 21h
     	INT 	21h             ; Return to DOS (terminate program)
     	END  ProgStart
