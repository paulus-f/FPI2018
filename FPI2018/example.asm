.586
.model flat, stdcall
includelib libucrt.lib
includelib StaticLib1.lib
includelib kernel32.lib
ExitProcess PROTO :DWORD

show PROTO : DWORD
showfl PROTO : REAL4

.stack 4096
.const
	var1 BYTE "HEllo", 0

	fl REAL4 43.24
.data
	i DWORD ?
	j DWORD ?
.code

addkek PROC adda : DWORD, addb : DWORD 
	MOV	EAX,addb
	ADD	EAX,adda
	ret
addkek ENDP

main PROC

; for()-------------------------------------------------------------
;*
	MOV EAX, 40
	MOV EBX, 4
	mul EBX
;/
	MOV EAX, 40
	MOV EBX, 4
	div EBX

	push 1
	push 2
	call addkek

	; EXAMPLE for(i = 3; i < 10; i=i+2) 
	MOV i, 3
	for1:
		;code
		add 	i, 2
		cmp		i, 10
		jb for1
		je endfor1
		ja endfor1
	endfor1:
; for()-------------------------------------------------------------

; until(j > 10)-------------------------------------------------------------
	MOV j, 1
	until1:
		;code
		add 	j, 1
		cmp		j, 10
		jb until1
		je enduntil1
		ja enduntil1
	enduntil1:
; untill()-------------------------------------------------------------


	push 0
	call ExitProcess
main ENDP
end main