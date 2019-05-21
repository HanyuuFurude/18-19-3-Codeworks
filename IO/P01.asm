; 写16位汇编程序，从键盘输入一个字符串，然后换行后将该字符串输出到屏幕。
; Author: Hanyuu
.8086
.model small
.stack
.data
	msgType db "[type]",13,10,'$'
	msgEcho db "[echo]",13,10,'$'
	n equ 50
	maxlen db n
	actlen db ?
	string db n dup(?)
	rn db 13,10,'$'
.code
start:	mov ax,@data
		mov ds,ax
		; hint for user input
		mov dx,offset msgType
		mov ah,09h
		int 21h
		; wait for user input
		mov ah,0ah
		mov dx,offset maxlen
		int 21h
		; print line feed
		mov ah,09h
		mov dx,offset rn
		int 21h
		; mov input context
		mov bl,actlen
		mov bh,0
		mov si,offset string
		mov byte ptr [si+bx],'$'
		; print feed back banner
		mov dx,offset msgEcho
		mov ah,09h
		int 21h
		; print user feedback
		mov dx,si
		mov ah,09h
		int 21h
		; exit
		mov ah, 4ch
		int 21h
end start