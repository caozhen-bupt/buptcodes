code 	segment
main	proc far
	assume cs:code
	mov bx,40abh
	add bl,09ch
	mov al,0e5h
	cbw
	add bh,al
	sbb bx,ax
	adc ax, 20h
	sub bh,-9h
main 	endp
code 	ends
end 	main