;在附加段中有一个从小到大排序的无符号数字数组，
;其首地址在DI中，
;数组的第一个单元存放数组长度。
;要求用折半查找法在数组中查找数N，
;假设该数已在AX中，
;如找到，
;CF=0，
;并在SI中给出该元素在数组中的偏移地址；如未找到，
;CF=1。
;Author: Hanyuu
.8086
.model small
.stack
.data
		arr db 10,2,3,5,7,11,13,17,19,23,27
		n db 17
.code
start:	mov ax,@data
		mov ds,ax
		mov al,byte ptr arr
		mov ah,0h
		mov cl,2h
		div cl
		mov dl,al
		mov dh,0h
		mov al,n
		mov ah,0h
		lea di,arr
		mov bx,dx
		mov dx,1h
		mov cl,byte ptr arr
		mov ch,0h
		call bs
		mov ax,4c00h
		int 21h
bs proc near
lp: 	cmp dx,cx
		jae notfound
		cmp al,byte ptr [bx+di]
		je found
		ja back
		jb form
found: 	clc
		mov si,bx
		ret
notfound: stc
		 ret
back: 	push ax
		push bx
		add bx,cx
		mov ax,bx
		push cx
		mov cl,2h
		div cl
		pop cx
		and ah,0h
		pop bx
		mov dx,bx
		mov bx,ax
		pop ax
		jmp lp
form: 	push ax
		push bx
		add bx,dx
		mov ax,bx
		push cx
		mov cl,2h
		div cl
		pop cx
		and ah,0h
		pop bx
		mov cx,bx
		mov bx,ax
		pop ax
		jmp lp
bs endp
end start
