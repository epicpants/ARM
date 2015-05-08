;*************************************************************************************
;*  TWI_asm.s
;*		Routines for initializing TWI
;*      Jon Eftink & Tyler Ryan
;*		
;*		CpE4151 Experiment #5, Spring 2015
;*************************************************************************************
;*		Version 1.0												Roger Younger
;*************************************************************************************
;*		
;*	CONSTANT DECLARATIONS

			INCLUDE AT91SAM7SE512.INC

TWD EQU 1<<3 ; SDA (PA3)
TWCK EQU 1<<4 ; SCL (PA4)
TWIO_MASK EQU TWD:OR:TWCK
CKDIV EQU 1
DIV EQU 238
DIV8 EQU 238 << 8
CKDIV16 EQU CKDIV << 16 
DIV_MASK EQU DIV:OR:DIV<<8:OR:CKDIV<<16
MSEN EQU 1<<2
SVDIS EQU 1<<5
SWRST EQU 1<<7
TWI_MODE_MASK EQU MSEN:OR:SVDIS
NACK_BIT EQU 1<<8
NACK_ERROR EQU 1
TXRDY_BIT EQU 1<<2
TX_COMP	EQU 1<<0
NO_ERRORS EQU 0

;******************************************************************************
;*	AREA DEFINITION
								 
			PRESERVE8
			AREA TWI,CODE,READONLY
			ARM

;******************************************************************************
;*	INITIALIZATION ROUTINE			void INIT_TWI(void)
;*		
;*		  
;*		
;*******************************************************************************

			EXPORT INIT_TWI

INIT_TWI
	 PUSH {R4, R5, R14}

	 ; Enable the peripheral clock
	 LDR R4, =PMC_BASE
	 MOV R5, #TWI_PID
	 STR R5, [R4, #PMC_PCER]

	 ; Set up I/O pins TWD (PA3) and TWCK (PA4)
	 LDR R4, =PIOA_BASE
	 MOV R5, #TWIO_MASK		 ; TWD | TWCK
	 STR R5, [R4, #PIO_PDR]	 ; controlled by a peripheral
	 STR R5, [R4, #PIO_ASR]	 ; controlled by peripheral A

	 ; Set port pins to be multi-drive and disable pull-up resistor
	 STR R5, [R4, #PIO_MDER] ; Multi-drive Enable Register
	 STR R5, [R4, #PIO_PUDR] ; Pull-up Disable Register

	 ; Set TWI Master mode and disable Slave mode
	 LDR R4, =TWI_BASE
	 MOV R5, #TWI_MODE_MASK
	 STR R5, [R4, #TWI_CR]
	 
	 ; Set the TWI clock frequency
	 
	 ;MOV R5, #DIV_MASK
     MOV R5, #DIV
     ORR R5, R5, #DIV8
     ORR R5, R5, #CKDIV16
	 STR R5, [R4, #TWI_CWGR]

	 POP {R4, R5, R14}
	 BX R14

;******************************************************************************
;*	TWI WRITE ROUTINE			uint32 TWI_WRITE(uint32 device_addr, uint32 internal_addr, uint32 internal_size, uint32 num_bytes, uint32 * values)
;*		
;*		  
;*		
;*******************************************************************************

			EXPORT TWI_WRITE

TWI_WRITE
	PUSH {R4, R5, R6, R14}
	LDR R4, [SP, #0X10] 		; R4 points to values array

	LDR R5, =TWI_BASE
	MOV R6, R0, LSL #16			; DADDR
	ORR R6, R6, R2, LSL #8		; IADRSZ
	STR R6, [R5, #TWI_MMR]
	STR R1, [R5, #TWI_IADR]		; Store internal address to IADR

DO_LOOP
	; Do
	LDR R6, [R4], #0X04			; R6=R4, R4+=4
	STR R6, [R5, #TWI_THR]		; Start sending

WHILE_TXRDY
	; While	(TXREADY is not set)
	LDR R6, [R5, #TWI_SR]
	TST R6, #NACK_BIT
	MOVNE R0, #NACK_ERROR
	BNE EXIT
	TST R6, #TXRDY_BIT
	BEQ WHILE_TXRDY

	; while (num_bytes != 0)
	SUBS R3, R3, #1
	BNE DO_LOOP

WHILE_TXCOMP
	; while (TXCOMP is not set)
	LDR R6, [R5, #TWI_SR]
	TST R6, #TX_COMP
	BEQ WHILE_TXCOMP
	MOV R0, #NO_ERRORS

EXIT
	POP {R4, R5, R6, R14}
	BX R14

    END
