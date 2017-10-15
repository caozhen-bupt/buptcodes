data	segment
	str db "111111111111a",00h
	sbstr db "a",00h
	nomatch db "no match!$"
	match db "match!0$"
	found dw ?
	pos dw ?
data	ends
code 	segment
main	proc far
	assume cs:code,ds:data,es:data
start:	mov bx,data
	mov ds,bx
	mov es,bx
	lea si,str
	lea di,sbstr
	mov bx,si
	mov bp,di
	cld
	sub bx,1
lp1:	add bx,1
	mov si,bx
	cmp byte ptr [si],00h
	jz lp3
	mov di,bp
lp2:	cmp byte ptr [di],00h
	jz lp4
	cmp byte ptr [si],00h
	jz lp1
	cmpsb
	jnz lp1
	jmp lp2
lp3:	mov ah,09h
	mov dx, offset nomatch
	int 21h	
lp4:	mov found, 0ffh
	mov pos, bx
	mov ah,02h
	mov dx, pos
	int 21h
	ret
main	endp
code 	ends
end 	start
