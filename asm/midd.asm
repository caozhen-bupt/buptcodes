data segment
t_ptr dw array
xyz equ 2000h
count dw -1
array db 33h, 66h, 92h, 29h
data ends

code segment
assume cs:code,ds:data,es:data
start:
     mov ax, data
     mov ds, ax
     mov es, ax
     mov ax, 0005h
     mov bx, 0001h
     mov sp,1008h
     mov ax, [bx]
     mov ax, 4c00h
     int 21h
code ends
end start