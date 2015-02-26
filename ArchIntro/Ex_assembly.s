;*********************************************************************
;    Example Assmbly - This file contains three "do-nothing" or stub 
;        functions that are setup so that they can be called from a 
;        C program using the extern keyword in C.  The exported label is 
;        the name of the function in C.  The functions save and restore
;        some registers so that they can be used in the function, but
;        not altered in the C program.
;*********************************************************************
;    Code written by: Roger Younger
;	 Modified by: Jon Eftink and Tyler Ryan
;    v1.0 Released: February 5, 2014
;	 v2.0 Released: February 26, 2015
;*********************************************************************
;    CONSTANT DEFINITIONS
;*********************************************************************
         INCLUDE AT91SAM7SE512.INC

		 PB27 EQU 1<<27		; left joystick
		 PB26 EQU 1<<26		; right joystick
		 PA0 EQU 1
		 JOYSTICK_MASK EQU PB27:OR:PB26
;***********************************************************
;    AREA DEFINITION AND OPTIONS
;***********************************************************
		PRESERVE8

		AREA EXAMPLE,CODE,READONLY
		ARM
;***********************************************************
;    Function: IO_INIT
;
;***********************************************************
		EXPORT IO_INIT

	
IO_INIT

	PUSH {R4-R7,R14}		; save values altered by this routine
	; Enable Peripheral Clock for PIOA
	LDR R4,=PMC_BASE	    ; puts the base address of the Power 
                            ; Management Controller into R4
    MOV R5,#PIOA_PID	    ; move the value to be placed in 
                            ; PMC_PCER into R5
	STR R5,[R4,#PMC_PCER]   ; stores the value in R5 into PMC_BASE (R4)
					        ; + the offset PMC_PCER (#0x0010)
					        ; R4 and R5 are not altered by the instruction	
	; Enable Peripheral Clock for PIOB
	MOV R5,#PIOB_PID
	STR R5,[R4,#PMC_PCER]
	; Enable PB27(left) and PB26(right)as inputs
	LDR R4,=PIOB_BASE
	MOV R5,#JOYSTICK_MASK
	STR R5,[R4,#PIO_PER]
	STR R5,[R4,#PIO_ODR]
	STR R5,[R4,#PIO_PUER]
	; Enable PA0(power LED) as an output
	LDR R4,=PIOA_BASE
	MOV R5,#PA0
	STR R5,[R4,#PIO_PER]
	STR R5,[R4,#PIO_OER]
	STR R5,[R4,#PIO_SODR]	; PA0 (power LED) initialized off
	POP {R4-R7,R14}		    ; restores the saved registers
	BX R14 			        ; return to calling program using link reg.


;*************************************************************
;    Function: READ_SWITCHES
;
;*************************************************************
		EXPORT READ_SWITCHES

READ_SWITCHES

		PUSH {R4-R7,R14}
		LDR R4,=PIOB_BASE
		; Read PIO_PDSR of PIOB (read switches)
		LDR R5,[R4,#PIO_PDSR]
		; If (left joystick pressed)
		TST R5,#PB27
		BNE ELSE_IF_SW
		; Then
		MOV R0,#2
		B END_IF_SW
ELSE_IF_SW
		; Else if (right joystick pressed)
		TST R5,#PB26
		; Then
		MOVEQ R0, #1
		; Else (no joystick pressed)
		MOVNE R0, #0
END_IF_SW
		; End-if {switches pressed}
		POP {R4-R7,R14}
		BX R14

;*************************************************************
;    Function: CONTROL_LED
;
;*************************************************************
		EXPORT CONTROL_LED

CONTROL_LED

		PUSH {R4-R7,R14}
		NOP
		NOP
		NOP
		POP {R4-R7,R14}
		BX R14
		
		
;*************************************************************
;    Function: DELAY_ASM(int)
;		          
;*************************************************************
		EXPORT DELAY_ASM

DELAY_ASM

		PUSH {R14}
		NOP
		NOP
		NOP
		POP {R14}
		BX R14

		END