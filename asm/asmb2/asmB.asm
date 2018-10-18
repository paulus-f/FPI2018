.586
.MODEL FLAT,C, stdcall
 option casemap :none ; case sensitive
 include \masm32\include\windows.inc
 include \masm32\include\kernel32.inc
 include \masm32\include\user32.inc
 include \masm32\include\masm32.inc
 includelib \masm32\lib\masm32.lib
includelib kernel32.lib
includelib "D:/Proga/Project/JaP/asm/Debug/asmA.lib" 

SetConsoleTitleA PROTO :DWORD
GetStdHandle PROTO     :DWORD
WriteConsoleA PROTO    :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
ExitProcess PROTO      :DWORD
Sleep PROTO            :DWORD

ExitProcess PROTO : DWORD 

getmin PROTO C: DWORD,: DWORD
getmax PROTO C: DWORD,: DWORD
.stack 4096

.const
 sConsoleTitle  db 'My First Console Application',0
sWriteText  db 'hEILo, Wo(R)LD!!'

.data
	intarr2 DD 43, 12, 54, 13, 56, 3, 65, 32, 45, 2
	sym db ?
	min DD ?
	max DD ?


.code 

main PROC
 LOCAL hStdout :DWORD
 start:
		
		
		INVOKE getmax, OFFSET intarr2, 10
		mov max, EAX

		INVOKE getmin, OFFSET intarr2, 10
		mov min, EAX
		
		mov EAX, max
		sub EAX, min
		
		mov sym, AL
		
		invoke SetConsoleTitle, offset sConsoleTitle
		invoke GetStdHandle, STD_OUTPUT_HANDLE
		mov hStdout,EAX
		invoke WriteConsole, hStdout, OFFSET sym, 01d, NULL, NULL
		invoke Sleep, 2000d
		
		
		push 0
		call ExitProcess

 main ENDP
end main


