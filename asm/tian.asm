DATA SEGMENT
STR1 DB 'h','e','l','l','o','w','o','r','l','d',00H
STR2 DB 'l','o','w',00H
FOUND DB 00H
POS DW 0000H
DATA ENDS

CODE SEGMENT
ASSUME CS : CODE, DS : DATA
START:
MOV BX, DATA
MOV DS, BX
MOV ES, BX
LEA SI, STR1
LEA DI, STR2
MOV CX, 0000H
L1:CMP BYTE PTR[DI], 00H
JZ L3
LODSB
SCASB
JZ L1
LEA SI, STR1
LEA DI, STR2
ADD CX, 1
ADD SI, CX
CMP BYTE PTR[SI], 00H
JZ L2
JMP L1
L2: MOV FOUND, 00H
JMP L4
L3: MOV FOUND, 0FFH
MOV POS, CX
L4:
CODE ENDS
END START