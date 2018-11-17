.586
.model FLAT, C , stdcall
includelib libucrt.lib 
includelib StanLib.lib 
includelib kernel32.lib 
ExitProcess PROTO : DWORD 
.stack 4096

.const
	INTLIT0		DWORD	10
	INTLIT1		DWORD	10
	INTLIT2		DWORD	60
	INTLIT3		DWORD	0
	INTLIT4		DWORD	1
	INTLIT5		DWORD	12
	INTLIT6		DWORD	20
	INTLIT7		DWORD	15

.data
	adda			DWORD	0
	addb			DWORD	0
	programb			DWORD	0

.code
	add PROC adda : DWORD, addb : DWORD 
		PUSH 	adda
		PUSH 	addb
		POP 	EAX
		POP 	EBX
		ADD	EAX,EBX
		PUSH 	EAX
		PUSH 	INTLIT0
		POP 	EAX
		POP 	EBX
		DIV	EBX
		PUSH 	EAX
		POP 	EAX
		ret
	add ENDP
	Main PROC 
		PUSH 	INTLIT1
		PUSH 	INTLIT2
		CALL		add
		PUSH 	EAX
		POP 	EAX
		MOV	programb,EAX
while0:
		PUSH 	programb
		PUSH 	INTLIT4
		POP 	EAX
		POP 	EBX
		ADD	EAX,EBX
		PUSH 	EAX
		POP 	EAX
		MOV	programb,EAX
		CMP	programb,INTLIT3
		JA		while0
		JB		endwhile0
endwhile0:
		CMP	programb,INTLIT5
		JB		if01
		JA		endif01
if01:
		PUSH 	programb
		PUSH 	INTLIT6
		POP 	EAX
		POP 	EBX
		ADD	EAX,EBX
		PUSH 	EAX
		POP 	EAX
		MOV	programb,EAX
		JMP		endalias1
endif01:
		PUSH 	programb
		PUSH 	INTLIT7
		POP 	EAX
		POP 	EBX
		ADD	EAX,EBX
		PUSH 	EAX
		POP 	EAX
		MOV	programb,EAX
endalias1:
	PUSH 0
	CALL ExitProcess

	Main ENDP

