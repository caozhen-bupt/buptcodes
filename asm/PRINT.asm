CODE SEGMENT
     assume cs:code
main pro far 
     MOV DL,'9'
     mov AH,2
     INT 21H
main endp
code ends