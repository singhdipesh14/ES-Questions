	AREA RESET, CODE, READONLY
		EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA myCode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC
	MOV R1, #0 ;I
TOP	CMP R1, #40
	BEQ EXI
	MOV R2, #0
	MOV R3, #36
	SUB R3, R1
UP	CMP R2, R3
	BEQ NEX
	LDR R4, [R0, R2]
	ADD R2, #4
	LDR R5, [R0, R2]
	SUB R2, #4
	CMP R4, R5
	BLS MEH
	STR R5, [R0, R2]
	ADD R2, #4
	STR R4, [R0, R2]
	SUB R2, #4
MEH ADD R2, #4
	B UP
NEX ADD R1, #4
	B TOP
	
EXI MOV R12, #0xFFFFFFFF
	
STOP B STOP
	AREA MYDATA, DATA, READWRITE
SRC	DCD 4, 5, 0, 8, 3, 7, 2, 6, 9, 1
	END