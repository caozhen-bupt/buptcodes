DATA SEGMENT
BUF DB 10,20,30,40,50,45,35,25,15,5,4,3,2,1,9,8,7,6,14,13,12,11,19,18,17,16,24,23,22,21,29,28,27,26,34,33,32,31,39,38,37,36,44,43,42,41,49,48,47,46
TEMP DB 3 DUP (?)
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE,DS:DATA
START:
	MOV AX, DATA
	MOV DS, AX
	MOV CX, 5
	XOR BX, BX
LP3:
	MOV DI, CX
	MOV CX, 10
LP4:	
	XOR SI, SI
	MOV DL, 10
	MOV AL, BUF[BX]
LP5:
	XOR AH, AH
	DIV DL
	MOV TEMP[SI], AH
	INC SI
	CMP AL, 0
	JNE LP5
LP6:	
	DEC SI
	MOV DL, 30H
	ADD DL, TEMP[SI]
	MOV AH, 02H
	INT 21H
	CMP SI, 0
	JNZ LP6

	MOV DL, 32
	MOV AH, 02H
	INT 21H
	INC BX
	LOOP LP4

	MOV DL, 0DH
	MOV AH, 02H
	INT 21H
	MOV DL, 0AH
	MOV AH, 02H
	INT 21H
	MOV CX, DI
	LOOP LP3
	
	MOV AX, 4C00H
	INT 21H

CODE ENDS
END START