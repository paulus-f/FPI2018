.586
.model FLAT, C , stdcall
.stack 4096
.code

getmin PROC C USES  edx ebx ecx arr:DWORD, arrsize:DWORD
	mov eax, 0
	
	mov ECX, arrsize
	mov EBX, arr
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
	ret 

getmin ENDP

getmax PROC C USES edx ebx ecx arr:DWORD, arrsize:DWORD
	mov eax, 0
	
	mov ECX, arrsize
	mov EBX, arr
	mov edx, 0
	mov eax, [ebx]
	
	
	metka1:
		 cmp eax, [ebx+edx];
		 ja elemarrless; above
		 je elemarrmore
		 jb elemarrmore
			elemarrmore: 
				mov eax, [ebx+edx]
				add EDX, 4
				loop metka1

			elemarrless: 
				cmp ecx, 0
				je endcycle
				add EDX, 4 
				loop metka1
	
endcycle:

	ret 
getmax ENDP

end
