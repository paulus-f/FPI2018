.586
.model FLAT, C , stdcall
includelib libucrt.lib 
includelib StanLib.lib 
includelib kernel32.lib 
ExitProcess PROTO : DWORD 
.stack 4096

.const
	INTLIT0		DWORD	10
	INTLIT1		DWORD	30
	INTLIT2		DWORD	40
	INTLIT3		DWORD	2
	INTLIT4		DWORD	10
	INTLIT5		DWORD	1
	INTLIT6		DWORD	12
	INTLIT7		DWORD	20
	INTLIT8		DWORD	15

.data
	adda			DWORD	0
	addb			DWORD	0
	programb			DWORD	0

.code
	add PROC adda : DWORD, addb : DWORD 
		PUSH 	adda
		PUSH 	addb
		POP 	EBX
		POP 	EAX
		ADD	EAX,EBX
		PUSH 	EAX
		PUSH 	INTLIT0
		POP 	EBX
		POP 	EAX
		DIV	EBX
		PUSH 	EAX
		POP 	EAX
		ret
	add ENDP
	main PROC 
		PUSH 	INTLIT1
		PUSH 	INTLIT2
		CALL		add
		PUSH 	EAX
		PUSH 	INTLIT3
		POP 	EBX
		POP 	EAX
		MUL	EBX
		MOV	EDX,0
		MOV	EBX,EAX
		PUSH 	EBX
		POP 	EAX
		MOV	programb,EAX
while0:
		PUSH 	programb
		PUSH 	INTLIT5
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	programb,EAX
		MOV	EAX,programb
		CMP	EAX,INTLIT4
		JB		while0
		JA		endwhile0

endwhile0:
		MOV	EAX,programb
		CMP	EAX,INTLIT6
		JA		if01
		JB		endif01

if01:
		PUSH 	programb
		PUSH 	INTLIT7
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	programb,EAX
		JMP		endalias1
endif01:
		PUSH 	programb
		PUSH 	INTLIT8
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	programb,EAX
endalias1:
	PUSH 0
	CALL ExitProcess

	main ENDP
end main

