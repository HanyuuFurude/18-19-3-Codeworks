;NUM  WORD  3570
;STRING  BYTE 5 DUP(20H),’$’;20H为空格的ASCII码
;请编写完整程序,
;在屏幕上以十进制的形式将NUM这个数打印出来,
;可以借助STRING这个字符串。（NUM这个数可以定义为一个任意字型数）。
;Author: Hanyuu
.8086
.model small
.stack
.data
	num dw 3570
	string db 5 dup(20h),'$'
.code
start:	mov ax,@data
		mov ds,ax
		mov si,offset string
		mov ax,num	;lower div
		mov bx,4h	;offset of the string
		mov cx,0ah	;base
lp:		mov dx,0h	;higher div
		div cx
		or dx,30h
		mov byte ptr[bx+si],dl
		dec bx
		cmp ax,0
		jnz lp
		;output the result
		mov dx,si
		add dx,bx
		mov ah,09h
		int 21h
		;end program
		mov ax,4c00h
		int 21h
end start