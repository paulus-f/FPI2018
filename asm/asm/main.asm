.586
.MODEL FLAT, stdcall 
includelib kernel32.lib 
ExitProcess PROTO : DWORD 
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD
.stack 4096

.const
 
.data
	intarr2 DD 43, 12, 54, 13, 56, 3, 65, 32, 45, 2
	sizearr dd 0ah
	sum DD ?
	min DD ?
	count DD 0
	intarr DD ?
.code 
getmin PROC 
	push ebp; в стек помещ текующее положение в стеке
	mov ebp, esp ; помещение в bp где мы находимся в стеке
	;[ss: bp + 2]
	mov eax, 0
	
	mov ECX, [ebp+8]
	mov EBX, [ebp+12]
	mov edx, 0
	mov eax, [ebx]
	
	
	metka1:
		 cmp eax, [ebx+edx];
		 ja elemarrless; above
		 je elemarrless
		 jb elemarrmore
			elemarrless: 
				mov eax, [ebx+edx]
				add EDX, 4
				loop metka1

			elemarrmore: 
				cmp ecx, 0
				je endcycle
				add EDX, 4 
				loop metka1
	
endcycle:
	pop ebp			; в bp адрес на который нужно перейти после call
	ret 8
getmin ENDP

 main PROC
start:
		mov EBX, 0
		mov ECX, 10
		LabelInitArray:
			mov [intarr+EBX], ECX
			add EBX, 4
			loop LabelInitArray
		
		mov sum, 0

		push OFFSET intarr2
		push sizearr
	
		call getmin 
		
		mov sum, eax;
		
		push 0
		call ExitProcess

 main ENDP
end main


