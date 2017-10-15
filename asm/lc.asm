data	segment
	str db "8#77mlsBIG$"
data	ends
code 	segment
main 	proc far
	assume cs:code,ds:data
start:	mov ax, data
	mov ds, ax
	lea si, str
rotate:	cmp byte ptr [si], '$'
	jz exit
	cmp byte ptr [si], 'z'
	jl lower
	inc si
	jmp rotate
lower:	cmp byte ptr [si], 'a'
	jg change
	inc si
	jmp rotate
change:	sub byte ptr [si], 20h
	inc si
	jmp rotate
exit:	mov ah, 9	
	mov dx, offset str
	int 21h
	mov ah,4ch
	int 21h
main 	endp
code	ends
end 	start