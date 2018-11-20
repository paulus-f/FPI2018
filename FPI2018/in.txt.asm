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
	INTLIT5		DWORD	3
	INTLIT6		DWORD	1
	INTLIT7		DWORD	12
	INTLIT8		DWORD	20
	INTLIT9		DWORD	15

.data
	foo__adda			DWORD	0
	foo__addb			DWORD	0
	foo__programb			DWORD	0
	lb_foo__programc			DWORD	0

.code
	foo__add PROC foo__adda : DWORD, foo__addb : DWORD 
		PUSH 	foo__adda
		PUSH 	foo__addb
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
	foo__add ENDP
	main PROC 
		PUSH 	foo__programb
		PUSH 	INTLIT1
		PUSH 	INTLIT2
		CALL		foo__add
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
while0:
		PUSH 	lb_foo__programc
		PUSH 	INTLIT5
		POP 	EAX
		MOV	lb_foo__programc,EAX
		PUSH 	foo__programb
		PUSH 	foo__programb
		PUSH 	lb_foo__programc
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		PUSH 	INTLIT6
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programb,EAX
		MOV	EAX,foo__programb
		CMP	EAX,INTLIT4
		JB		while0
		JA		endwhile0

endwhile0:
		MOV	EAX,foo__programb
		CMP	EAX,INTLIT7
		JA		if01
		JB		endif01

if01:
		PUSH 	foo__programb
		PUSH 	foo__programb
		PUSH 	INTLIT8
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programb,EAX
		JMP		endalias1
endif01:
		PUSH 	foo__programb
		PUSH 	foo__programb
		PUSH 	INTLIT9
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programb,EAX
endalias1:
	PUSH 0
	CALL ExitProcess

	main ENDP
end main

