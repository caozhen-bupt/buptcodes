data segment
block db 00h
var dw 2
str db 5h dup(?)
data ends
code segment
main proc far
     assume cs:code,ds:data
     mov ax, data
     mov ds, ax
     mov dx, block + (6-1)*2
     mov al, 10h
     add al, var
main endp
code ends
     end main