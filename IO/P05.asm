
;利用跳转表技术实现根据用户输入的星期几的数字代号在屏幕上显示星期几的英文名称的功能。
;（提示：1）键盘输入的是数字的aSCII码，需要转换成数字。
;		2）建立一张跳转表，表中存放打印每个星期的程序段的入口地址。
;		3）考虑怎么使程序代码量最小。
;author: hanyuu
.8086
.model small
.stack
.data
	table db "Mon$"
	db "Tue$"
	db "Wed$"
	db "Thu$"
	db "Fri$"
	db "Sat$"
	db "Sun$"
.code
start:  mov ax, @data
		mov ds, ax
		; input the character
		mov ah,01h
		int 21h	; character storged in al
		xor al,30h	; convery to number
		dec al
		cmp al,6h
		ja finish
		cmp al,0h
		jb finish
		mov dx,4
		mul dx
		; get string form table
		mov si,OFFSET table
		mov ah,0h	;clear ah
		add si,ax
		mov dx,si
		mov ah,9h
		int 21h
finish:	mov ax,4c00h
		int 21h
end start