.586
.MODEL FLAT, stdcall
includelib kernel32.lib
ExitProcess PROTO: DWORD
includelib D:/Proga/Project/JaP/asm/Debug/asmA.lib
 getmin PROTO C: DWORD,: DWORD
 getmax PROTO C: DWORD,: DWORD

.stack 4096

.const

.data
	intarr2 DD 43, 12, 54, 13, 56, 3, 65, 32, 45, 2
	min DD ?
	max DD ?


.code 

main PROC

		
		push 10
		push OFFSET intarr2 
		call getmax
		mov max, EAX

 
		push 10
		push OFFSET intarr2
		call getmin
		mov min, EAX
		
		mov EAX, max
		sub EAX, min
		
		push 0
		call ExitProcess

 main ENDP
end main


