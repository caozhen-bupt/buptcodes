data segment
var db 'hit key!'
data ends

code segment
assume cs:code,ds:data,es:data
start:
     mov ax, data
     mov ds, ax
     mov es, ax
     sub var, cx
     mov [di], al
     mov al, var
     add [si], 2
     mov ax, 4c00h
     int 21h
code ends
end start