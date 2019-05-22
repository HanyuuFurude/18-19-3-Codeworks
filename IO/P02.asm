; 写完整程序16位程序
;在内存中从Table开始的10个单元中连续存放0到9的平方值;
;任给一个0到9的数X
;该数存放在内存单元XX中
;用XLAT指令查表求X的平方值
;并将结果存于内存YY单元中
;编写程序
;并在DEBUG中进行调试和验证结果
;(X，XX，YY都是内存中的变量）
; Author: Hanyuu
.8086
.model small
.stack
.data
	table db 1,4,9,16,25,36,49,64,81
.code
start: 	mov ax,@data
		mov ds,ax
		; input numbers
		mov cl,3
		; fetch the input and query number
		mov bx,offset table-1
		mov al,cl
		xlat
		mov ax,4c00h
		int 21h
end start
