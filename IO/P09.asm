;请编写完整16位汇编程序从键盘读取字符
;如果是十进制的‘0’～‘9’则在屏幕上输出该数的8位二进制码
;并将数字依次存放到BUF开头的数组中
;如果读入的字符是’Q’或者‘q’
;则程序退出
;其他情况在屏幕上打印“You must input 0~9
; or ‘q’ or ‘Q’”。
;（如输入的字符是‘9’
;则输出“00001001”）
;.提示：输出一个数的2进制形式应该从最高位开始输出。
;要求打印一个数的2进制形式和输出回车换行分别定义
;成一个子程序可以将此段程序定义成一个过程。
;Author: Hanyuu
.8086
.model small
.stack
.data
    msg db "you must input 0-9, or 'q' or 'Q'",13,10,'$'
    rf db 13,10,'$'
    rec db 0ffh dup(?)
.code
start:  mov ax,@data
        mov ds,ax
        mov cx,0ffh
        mov si,0h
        lea bx,msg
lp:     mov ah,01h  ;request for input
        int 21h
        cmp al,"Q"
        je finish
        cmp al,"q"
        je finish
        cmp al,30h
        jb hint
        cmp al,39h
        ja hint
        xor al,30h
        mov byte ptr [bx+si],al
        inc si
        cmp si,0ffh
        ja finish
        call print
        mov ah,02h
        mov dl,0ah
        int 21h
        mov dl,0dh
        int 21h
        jnz lp
print proc near
        mov ah,09h
        lea dx,rf
        int 21h
        mov ah,2h
        mov cx,8h
nlp:    mov dl,0h
        sal al,1h
        adc dl,30h
        push ax
        int 21h
        pop ax
        loop nlp
        ret
print endp
hint:  mov ah,09h
        lea dx,msg
        int 21h
        jmp lp
finish: mov ax,4c00h
        int 21h
end start


