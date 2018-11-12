.586
.MODEL FLAT, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib D:\Proga\Project\FPI2018\asm\Debug\asmd.lib
 getmin : proc
 getmax : proc
 input1 : proc

ExitProcess PROTO: DWORD 

.stack 4096

.const

.data
	intarr2 DD 43, 12, 54, 13, 56, 3, 65, 32, 45, 28
	min DD ?
	max DD ?


.code 

main PROC

		
		push 10
		push OFFSET intarr2 
		call getmax
		mov max, EAX

		push OFFSET intarr2
		call input1
 
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


