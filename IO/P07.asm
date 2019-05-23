;;已知数据段有以下定义：
;  STRING BYTE 'It is palindrome',0DH,0AH,'$'
;  LEN	WORD ?
;  NUM   BYTE 5 DUP(20H),'$'    ; 20H为空格的ASCII码
;请编写完整16位汇编程序，
;统计以‘$’字符结束的字符串STRING的字符个数（不算'$'）,
; 将个数放入LEN中，并在屏幕上以十进制的形式将LEN打印出来，
;可以借助NUM这个字符串。
;Author: Hanyuu
.8086
.model small
.stack
.data
    string db "It is palindrome",0dh,0ah,'$'
    len dw ?
    num db 5 dup(20h),'$'
.code
start:  mov ax,@data
        mov ds,ax

        lea si,string
        mov bx,0h   ;length/offset of the string
        mov cx,0h   ;cache for character
lp:     mov cl,byte ptr [bx+si]
        cmp cl,'$'
        jz finish   ;finish go to print program
        inc bx
        jmp lp
finish: mov si,offset len
        mov word ptr[si],bx
        mov si,offset num
        mov ax,len
		mov bx,4h	;offset of the string
		mov cx,0ah	;base
llp:	mov dx,0h	;higher div
		div cx
		or dx,30h
		mov byte ptr[bx+si],dl
		dec bx
		cmp ax,0
		jnz llp
		;output the result
		mov dx,si
		add dx,bx
		mov ah,09h
		int 21h
		;end program
		mov ax,4c00h
		int 21h
end start