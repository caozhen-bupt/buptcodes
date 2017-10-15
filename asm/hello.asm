data segment
  string db 'Hello world!','$' 
data ends
 
code segment
main 	proc far
	assume cs:code,ds:data
start:
  mov ax,data  ;将数据段段地址装入AX寄存器
  mov ds,ax ;将数据段段地址通过通用寄存器AX装入DS
  mov dx,offset string ;将串的段内地址装入DX
  mov ah,09h ;调用DOS的09H号功能，传入参数DS:DX=串地址，'$'结束字符串
  int 21h
  mov ah,4ch
  int 21h
main endp
code ends  ;代码段定义结束
end start  ;程序结束