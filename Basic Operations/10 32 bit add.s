	AREA RESET,DATA,READONLY
		EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA MYCODE,CODE,READONLY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC
	LDR R1, =0xA
UP	LDR R2, [R0]
	ADDS R3, R2
	ADC R4, #0
	SUBS R1, #1
	BNE UP
	LDR R0, =DST
	STR R3, [R0], #4
	STR R4, [R0]
STOP B STOP
SRC DCD 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	AREA MYDATA, DATA, READWRITE
DST DCD 0
	END