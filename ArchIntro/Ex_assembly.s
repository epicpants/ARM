;*********************************************************************
;    Example Assmbly - This file contains three "do-nothing" or stub 
;        functions that are setup so that they can be called from a 
;        C program using the extern keyword in C.  The exported label is 
;        the name of the function in C.  The functions save and restore
;        some registers so that they can be used in the function, but
;        not altered in the C program.
;*********************************************************************
;    Code written by: Roger Younger
;    v1.0 Released: February 5, 2014
;*********************************************************************
;    CONSTANT DEFINITIONS
;*********************************************************************
         INCLUDE AT91SAM7SE512.INC


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
	NOP
	NOP
	; Enable PB27(left) and PB26(right)as inputs
	NOP
	NOP
	; Enable PA0(power LED) as an output
	NOP
	NOP
	POP {R4-R7,R14}		    ; restores the saved registers
	BX R14 			        ; return to calling program using link reg.


;*************************************************************
;    Function: READ_SWITCHES
;
;*************************************************************
		EXPORT READ_SWITCHES

READ_SWITCHES

		PUSH {R4-R7,R14}
		NOP
		NOP
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