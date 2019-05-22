;所谓回文字符串是指一个字符串正读和倒读都是一样的
;例如字符串‘ABCDEFFEDCBA’就是一个回文字符串
;而字符串‘ABCFDDCAB’就不是回文字符串。现在编写完整的16位汇编程序
;输入一个字符串
;判断该字符串是否为回文字符串
;并用“It is a palindrome”或“It is NOT a palindrome”作为输出。

.8086
.model small
.stack
.data
	msgType db "[type]",13,10,'$'
	msgEcho db "[echo]",13,10,'$'
	msgTrue db 13,10,"It is a palindrome",13,10,'$'
	msgFalse db 13,10,"It is not a palindrome",13,10,'$'
	n equ 8fh
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
		;set main loop
		mov bl,actlen
		mov bh,0h		; string head
		dec bx
		mov si,offset string
		add bx,si 		;string end
		;get the front key and the back key
check:	mov dl,[si]
		mov dh,[bx]
		cmp dl,dh
		jne break
		cmp si,bx
		je output
		inc si
		dec bx
		jmp check
break:	mov dx,offset msgFalse
		mov ah,9h
		int 21h
		jmp final		
output:	mov dx,offset msgTrue
		mov ah,09h
		int 21h
		jmp final
		; exit
final:	mov ah, 4ch
		int 21h
end start