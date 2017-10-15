data segment
var db 2
STRING1 DB "Enter keyword:$"
data ends
code segment
main proc far
     assume cs:code,ds:data
     and var,offset var
     add bx,ss:var

	LEA?DX,STRING1
?	MOV?AH,09H
?	INT?21H
main endp
code ends
     end main