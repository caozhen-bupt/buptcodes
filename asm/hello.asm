data segment
  string db 'Hello world!','$' 
data ends
 
code segment
main 	proc far
	assume cs:code,ds:data
start:
  mov ax,data  ;�����ݶζε�ַװ��AX�Ĵ���
  mov ds,ax ;�����ݶζε�ַͨ��ͨ�üĴ���AXװ��DS
  mov dx,offset string ;�����Ķ��ڵ�ַװ��DX
  mov ah,09h ;����DOS��09H�Ź��ܣ��������DS:DX=����ַ��'$'�����ַ���
  int 21h
  mov ah,4ch
  int 21h
main endp
code ends  ;����ζ������
end start  ;�������