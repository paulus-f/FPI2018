.586
.model FLAT, C , stdcall
includelib libucrt.lib 
includelib StanLib.lib 
includelib kernel32.lib 
ExitProcess PROTO : DWORD 
.stack 4096

.const
	INTLIT0		DWORD	10
	INTLIT1		DWORD	0
	INTLIT2		DWORD	0
	INTLIT3		DWORD	1
	INTLIT4		DWORD	12
	INTLIT5		DWORD	20
	INTLIT6		DWORD	15

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
while0:
		 cmp	programb,INTLIT2
		 ja		while0
		 jb		endwhile0
endwhile0:
		 cmp	programb,INTLIT4
		 jb		if01
		 ja		endif1
if01:
		 jmp		endalias1
endif1:
endalias1:
	push 0
	call ExitProcess

	Main ENDP

