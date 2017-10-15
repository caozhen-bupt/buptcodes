data segment
var db 2
str db 5h dup(?)
data ends
code segment
main proc far
     assume cs:code,ds:data
     mov ax,[bx+si]
     mov str,'adsdfsdf'
main endp
code ends
     end main