;假设CX:BX中放了4位非压缩的BCD码表示的十进制数4386,
;请编写完整程序将这个数转成2进制数放到DI寄存器中,
;并用DEBUG调试和验证之
;Author: Hanyuu
.8086
.model small
.stack
.data
.code
start:	mov ax,@data
		mov ds,ax
		mov cx,0403h
		mov bx,0806h
		mov dx,0h
		mov dl,ch
		mov ax,dx
		mov di,10
		mul di
		mov dl,cl
		add ax,dx
		mul di
		mov dl,bh
		add ax,dx
		mul di
		mov dl,bl
		add ax,dx
		mov di,ax
		mov ax,4c00h
		int 21h
end start