;在内存中有一个数组,
;里面是放着10个学生的某科的成绩,
;分别是：85,73,92,66,91,98,52,87,83,68,
; 请用冒泡排序法将这10个数从大到小排序,
;并将排序的结果在屏幕上打印出来,
;要求一个数一行的格式输出。
;Author: Hanyuu.8086
.model small
.stack
.data
		org 100h
		arr db 85,73,92,66,91,98,52,87,83,68
		rf db 10,13,'$'
		num db 2 dup(?)
.code
start: 	mov ax,@data
		mov ds,ax
		lea bx,arr
		call sort
		call print
		mov ah,4ch
		int 21h
sort proc near
		mov cx,10
lp:   	dec cx
		cmp cx,0
		je finish
		mov si,0
		mov di,0
		dec si
nlp: 	inc si
		inc di
		cmp di,cx
		ja lp
		mov dl,byte ptr [bx+si]
		mov dh,byte ptr [bx+di]
		cmp dl,dh
		jae nlp
		mov ah,byte ptr [bx+si]
		push ax
		mov ah,byte ptr [bx+di]
		xchg byte ptr [bx+si],ah
		pop ax
		xchg byte ptr [bx+di],ah
		jmp nlp
finish:  ret
sort endp
print proc near
		mov dl,0ah
		mov si,0h
		dec si
clp:  	inc si
		cmp si,0ah
		je  finish
		mov al,byte ptr [bx+si]
		mov ah,0h
		div bl
		or al,30h
		or ah,30h
		mov byte ptr num,al
		mov byte ptr num[1],ah
		push bx
		push si
		mov si,2h
		lea bx,num
		mov byte ptr [bx+si],'$'
		pop si
		pop bx
		push dx
		mov dx,offset num
		mov ah,09h
		int 21h
		mov dx,offset rf
		mov ah,09h
		int 21h
		pop dx
		jmp clp
 finish:  ret
print endp
end start
