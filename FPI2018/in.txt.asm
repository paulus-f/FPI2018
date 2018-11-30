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
 outputintfpi PROTO : DWORD
 msin  PROTO : REAL4
 mcos  PROTO : REAL4
 mtan  PROTO : REAL4
 mctan PROTO : REAL4
 mln   PROTO : REAL4
 mabs  PROTO : DWORD
 msqr  PROTO : DWORD
 strlenfpi PROTO : DWORD
 strfind   PROTO : DWORD, : DWORD

.const
	INTLIT0		DWORD	10
	BLLIT0		DWORD	0
	INTLIT1		DWORD	10
	BLLIT1		DWORD	1
	BLLIT2		DWORD	0
	FLLIT0		REAL4	12.3
	FLLIT1		REAL4	1.54
	STRLIT0		DB	"fisrts string", 0
	STRLIT1		DB	"second string", 0
	STRLIT2		DB	"str", 0
	INTLIT2		DWORD	123
	BLLIT3		DWORD	0
	BLLIT4		DWORD	0
	FLLIT2		REAL4	1.01
	FLLIT3		REAL4	1.01
	FLLIT4		REAL4	23.43
	INTLIT3		DWORD	30
	INTLIT4		DWORD	40
	INTLIT5		DWORD	2
	INTLIT6		DWORD	1
	INTLIT7		DWORD	1
	INTLIT8		DWORD	0
	INTLIT9		DWORD	10
	INTLIT10		DWORD	1
	INTLIT11		DWORD	2

.data
	system_pause_fpi			DB	255 dup(0)
	foo__retflb			REAL4	0.0
	foo__statecheckstate			DWORD	0
	foo__programtestflone			REAL4	0.0
	foo__programstrokaa			DB	255 dup(0)
	foo__programsrokabb			DB	255 dup(0)
	foo__programkek			DWORD	0
	foo__programchek			DWORD	0
	foo__programlolb			DB	255 dup(0)
	foo__programsizestrokaaa			DWORD	0
	foo__programflag			DWORD	0
	foo__programlol			DB	255 dup(0)
	foo__programtestfltwo			REAL4	0.0
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
	foo__retfl PROC foo__retfla : REAL4, foo__retflc : REAL4 
		FLD	foo__retfla
		FLD	foo__retflc
		FADD
		FSTP	[foo__retflb]
		FLD	foo__retflb
		FSTP	[foo__retflb]
		MOV	EAX,OFFSET foo__retflb
		ret
	foo__retfl ENDP
	foo__state PROC foo__stateinta : DWORD 
		PUSH 	BLLIT0
		POP 	EAX
		MOV	foo__statecheckstate,EAX
		JA		if00
		JE		if00
		JB		endif00

if00:
		PUSH 	BLLIT1
		POP 	EAX
		MOV	foo__statecheckstate,EAX
		JMP		endalias0
endif00:
		PUSH 	BLLIT2
		POP 	EAX
		MOV	foo__statecheckstate,EAX
endalias0:
		PUSH 	foo__statecheckstate
		POP 	EAX
		ret
	foo__state ENDP
	main PROC 
		PUSH 	FLLIT0
		PUSH 	FLLIT1
		CALL		foo__retfl
		FLD	DWORD PTR [EAX]
		FSTP	[foo__programtestflone]
		MOV	ESI,OFFSET STRLIT0
		MOV	EDI , OFFSET  foo__programstrokaa + 0
		MOV	ECX,14
		REP MOVSB
		MOV	ESI,OFFSET STRLIT1
		MOV	EDI , OFFSET  foo__programsrokabb + 0
		MOV	ECX,14
		REP MOVSB
		PUSH 	OFFSET STRLIT2
		PUSH 	OFFSET foo__programsrokabb
		CALL		strfind
		PUSH 	EAX
		POP 	EAX
		MOV	foo__programkek,EAX
		PUSH 	INTLIT2
		CALL		foo__state
		PUSH 	EAX
		POP 	EAX
		MOV	foo__programchek,EAX
		MOV	ESI,OFFSET foo__programstrokaa
		MOV	EDI , OFFSET foo__programlolb + 0
		MOV	ECX,14
		REP MOVSB
		PUSH 	OFFSET foo__programsrokabb
		CALL		strlenfpi
		PUSH 	EAX
		POP 	EAX
		MOV	foo__programsizestrokaaa,EAX
		PUSH 	BLLIT3
		POP 	EAX
		MOV	foo__programflag,EAX
		MOV	EAX,foo__programflag
		CMP	EAX,BLLIT4
		JE		if00
		JZ		endif00

if00:
		FLD	foo__programtestflone
		FLD	[FLLIT2]
		FADD
		FSTP	[foo__programtestflone]
		JMP		endalias0
endif00:
		FLD	[FLLIT3]
		FSTP	[foo__programtestflone]
endalias0:
		MOV	ESI,OFFSET foo__programstrokaa
		MOV	EDI , OFFSET foo__programlol + 0
		MOV	ECX,14
		REP MOVSB
		MOV	ESI,OFFSET foo__programsrokabb
		MOV	EDI , OFFSET foo__programlol + 13
		MOV	ECX,14
		REP MOVSB
		PUSH 	OFFSET foo__programlol
		CALL		outputstrfpi
		FLD	[FLLIT4]
		FLD	foo__programtestflone
		FADD
		FSTP	[foo__programtestfltwo]
		PUSH 	INTLIT3
		PUSH 	INTLIT4
		CALL		foo__funadd
		PUSH 	EAX
		PUSH 	INTLIT5
		POP 	EBX
		POP 	EAX
		MOV	EDX,0
		MUL	EBX
		MOV	EBX,EAX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programb,EAX
		PUSH 	INTLIT6
		POP 	EAX
		MOV	foo__programi,EAX
		PUSH 	INTLIT7
		POP 	EAX
		MOV	foo__programb,EAX
		PUSH 	INTLIT8
		POP 	EAX
		MOV	foo__programi,EAX
for1:
		PUSH 	foo__programb
		PUSH 	INTLIT11
		POP 	EBX
		POP 	EAX
		MOV	EDX,0
		MUL	EBX
		MOV	EBX,EAX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programb,EAX
		PUSH 	foo__programi
		PUSH 	INTLIT10
		POP 	EDX
		POP 	EBX
		ADD	EBX,EDX
		PUSH 	EBX
		POP 	EAX
		MOV	foo__programi,EAX
		MOV	EAX,foo__programi
		CMP	EAX,INTLIT9
		JB		for1
		JA		endfor1

endfor1:
	PUSH OFFSET system_pause_fpi
	call inputfpi
	PUSH 0
	CALL ExitProcess

	main ENDP
end main

