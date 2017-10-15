data	segment
	str db '877mlsBIG','$'
data	ends
code 	segment
main 	proc far
	assume cs:code,ds:data
start:
	mov bx, data
	mov ds, bx
	lea dx, str
	mov ah, 09h
	int 21h
	
main 	endp
code	ends
end 	start