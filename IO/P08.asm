;请编写16位完整汇编程序,
;在一个升序字节数组BUFF中查找数N,
;找到后将此数从数组中删除,
;并使得CF=0；没找到返回CF＝1。
;Author: Hanyuu
.8086
.model small
.stack
.data
    buff db 2,3,5,7,11,13,17,19
    n db 7
.code
start:  mov ax,@data
        mov ds,ax
        mov bx,0000h    ;ptr
        mov dl,n    ;key
        mov ch,8    ;sum
        ; mov si,offset buff  ;offset of buff
        lea si,buff
lp:     cmp dl,[si][bx]
        je found
        inc bx
        cmp ch,bl
        je noFound
        jmp lp
found:  inc bx
        mov ch,[si+bx]
        dec bx
        mov [si+bx],ch
        inc bx
        cmp dl,ch
        je finish
        jmp found
noFound: clc
        jmp ending
finish: stc
        jmp ending
ending:    mov ax,4c00h
        int 21h
end start
