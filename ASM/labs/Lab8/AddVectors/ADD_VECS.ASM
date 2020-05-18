;
; add_vecs.asm
;
 .MODEL SMALL
 .DATA
;
 .CODE
; Implementation of c call function
;       int _add2Vecs( int v1[],  int v2[], int v1_plus_v2[], int n)
;                       [BP+4]       [BP+6]     [BP+8]       [BP+10]    
; add v1 and v2 vectors elements and set the result in v1_plus_v2:
; v1_plus_v2[0]=v1[0]+v2[0]
; v1_plus_v2[1]=v1[1]+v2[1]
; ...
; v1_plus_v2[n-1]=v1[n-1]+v2[n-1]
; Return value: sum of all v1_plus_v2 vector elements
PUBLIC _add2Vecs
;
_add2Vecs  PROC NEAR
   PUSH BP
   MOV BP,SP
   PUSH SI ;Preserve registers
   PUSH DI
;
   MOV AX, 0    ;    
   MOV BX,[BP+4]; set BX to v1
   MOV SI,[BP+6]; set SI to v2
   MOV DI,[BP+8]; set  DI to v1_plus_v2
   MOV CX,[BP+10]; set CX to n
AddLoop:
   MOV DX, [SI]								;for(i=0; i<n; i++)
   MOV [DI], DX								;{    
   MOV DX,[BX]								;	
   ADD [DI], DX								;	v1_plus_v2[i]=v1[i]+v2[1];
   ADD AX, [DI] ; sum v1_plus_v2 elemens	;   AX=AX+v1_plus_v2[i] //sum 
   ADD DI, 2								;}	
   ADD SI, 2
   ADD BX, 2
   LOOP AddLoop
;
   POP DI
   POP SI
   POP BP
   RET										;returm AX
   _add2Vecs ENDP
 ;
   END
