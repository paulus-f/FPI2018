.586
.model FLAT, C , stdcall
includelib libucrt.lib 
includelib StanLib.lib 
includelib kernel32.lib 
ExitProcess PROTO : DWORD 
.stack 4096
inputfpi PROTO: DWORD
 outputstrfpi PROTO : DWORD
 outputflfpi  PROTO : REAL4
 outputintfpi  PROTO : DWORD
 msin  PROTO : REAL4
 mcos  PROTO : REAL4
 mtan  PROTO : REAL4
 mctan PROTO : REAL4
 mln   PROTO : REAL4
 mabs  PROTO : DWORD
 msqr  PROTO : DWORD
 strlen  PROTO : DWORD
 strfind PROTO : DWORD, : DWORD

.const
	INTLIT0		DWORD	10
	INTLIT1		DWORD	30
	INTLIT2		DWORD	40
	INTLIT3		DWORD	2
	INTLIT4		DWORD	1
	INTLIT5		DWORD	1
	INTLIT6		DWORD	0
	INTLIT7		DWORD	10
	INTLIT8		DWORD	1
	INTLIT9		DWORD	2

.data
	foo__programb			DWORD	0
	foo__programi			DWORD	0

.code
	foo__funadd PROC foo__funadda : DWORD, foo__funaddc : DWORD 
		PUSH 	foo__funadda
		PUSH 	foo__funaddc
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		PUSH 	INTLIT0
		POP 	EBX
		POP 	EAX
		MOV	EDX,0
		DIV	EBX
		MOV	EBX,EAX
		PUSH 	EBX
		POP 	EAX
		ret
	foo__funadd ENDP
	main PROC 
		PUSH 	INTLIT1
		PUSH 	INTLIT2
		CALL		foo__funadd
		PUSH 	EAX
		PUSH 	INTLIT3
		POP 	EBX
		POP 	EAX
		MOV	EDX,0
		MUL	EBX
		MOV	EBX,EAX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programb,EAX
		PUSH 	INTLIT4
		POP 	EAX
		MOV	foo__programi,EAX
		PUSH 	INTLIT5
		POP 	EAX
		MOV	foo__programi,EAX
		PUSH 	INTLIT6
		POP 	EAX
for0:
		PUSH 	foo__programb
		PUSH 	INTLIT9
		POP 	EBX
		POP 	EAX
		MOV	EDX,0
		MUL	EBX
		MOV	EBX,EAX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programi,EAX
		PUSH 	foo__programi
		PUSH 	INTLIT8
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	EAX,foo__programi
		CMP	EAX,INTLIT7
		JB		for0
		JA		endfor0

endfor0:
	PUSH 0
	CALL ExitProcess

	main ENDP
end main

