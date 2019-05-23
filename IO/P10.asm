.8086
.model small
.stack
.data
		fac db 20h, 4 dup(20h), '$'
.code


start:  mov ax, @data
		mov ds, ax
		mov ah, 01h
		int 21h
		mov cl, al
		mov ch, 0
		xor cl, 30h
		cmp cl, 1h
		jb  finish
		cmp cl, 6h
		ja  finish
		call dac
finish:	mov ah, 4ch
		int 21h
dac proc near
		mov ax, 1h
		mov dx, 0h
lp:	mul cx
		loopnz lp
		mov bx, 10
		div bx
		add dx, 30h
		mov fac[3], dl
		mov dx, 0
		div bx
		add dx, 30h
		mov fac[2], dl
		mov dx, 0
		div bx
		add dx, 30h
		mov fac[1], dl
		mov dx, 0
		lea dx, fac
		mov ah, 09h
		int 21h
		ret
dac endp
end start
