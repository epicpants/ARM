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

PIOA_B_val     EQU  0x0000000C       ; Bit 2 for PIOA, Bit 3 for PIOB
PIOA_val       EQU  0x00000004       ; Bit 2 for PIOA
RSW_val       EQU  1<<22       ; Bit 22 right sw
LSW_val       EQU  1<<25       ; Bit 25 left sw
SWITCHES_val  EQU  RSW_val:OR:LSW_val       ; Bits for left sw right sw	
PA0_val        EQU  0x00000001       ; Bit 0 for PA0 (powerLED)
PA11_val       EQU  0x00000800       ; Bit 11 for PA11 (DS75 output)
NO_SW_PRESSED  EQU  0x00000000       ; 0 = no swtiches pressed return value
LEFT_SW_PRESSED  EQU  0x00000002       ; 2 = left swtich pressed return value (ON)
RIGHT_SW_PRESSED  EQU  0x00000001       ; 1 = right swtich pressed return value (OFF)
ON_val         EQU  0x00000002       ; 2 = left swtich pressed return value (ON)
OFF_val        EQU  0x00000001       ; 1 = right swtich pressed return value (OFF)
OUTPUT_INACTIVE EQU 0x00000000       ; 0 = output is high (inactive)
OUTPUT_ACTIVE   EQU 0x00000004	     ; 4 = output is low (active)
;***********************************************************
;    AREA DEFINITION AND OPTIONS
;***********************************************************
		PRESERVE8

		AREA EXAMPLE,CODE,READONLY
		ARM
;***********************************************************
;    Function: IO_INIT
;    void IO_INIT(void)
;    
;    Enables the peripheral clocks for PIOA and PIOB.
;    Sets PB27 and PB26 as inputs with internal pull-up resistors.
;    Sets PA0 as an output and clears the output.
;***********************************************************
		EXPORT IO_INIT

IO_INIT

	PUSH {R4-R7,R14}		; save values altered by this routine
	; Enable Peripheral Clocks for PIOA and PIOB
	LDR R4,=PMC_BASE	    ; puts the base address of the Power 
                            ; Management Controller into R4
    MOV R5,#PIOA_B_val	    ; move the value to be placed in 
                            ; PMC_PCER into R5
	STR R5,[R4,#PMC_PCER]   ; stores the value in R5 into PMC_BASE (R4)
					        ; + the offset PMC_PCER (#0x0010)
					        ; R4 and R5 are not altered by the instruction	
	; Enable PB27(left) and PB26(right)as inputs
	LDR R4,=PIOB_BASE       ; Load Base Address of PIOB 
	MOV R5,#SWITCHES_val   ; '1's set for PB27 and PB26
	STR R5,[R4,#PIO_PER]    ; Enable PIO, disable peripheral
	STR R5,[R4,#PIO_ODR]    ; Disable as output, Enable as input
	STR R5,[R4,#PIO_PUER]   ; Enable internal pull-up resistor
	; Enable PA0(power LED) as an output
	LDR R4,=PIOA_BASE       ; Load Base Address of PIOA
	MOV R5,#PA0_val         ; '1' set for PA0
	STR R5,[R4,#PIO_PER]    ; Enable PIO, Disable peripheral
	STR R5,[R4,#PIO_OER]    ; Enable as output, Disable as input
	STR R5,[R4,#PIO_CODR]    ; Clear output to a '0' (off)
	POP {R4-R7,R14}		    ; restores the saved registers
	BX R14 			        ; return to calling program using link reg.


;*************************************************************
;    Function: READ_SWITCHES
;    uint READ_SWITCHES(void)
;
;    Reads the Pin Data Satus Reg of PIOB and outputs 
;    LEFT_SW_PRESSED (2) is PB27 is pressed, RIGHT_SW_PRESSED (1)
;    if PB26 is pressed and NO_SW_PRESSED (0) if neither is pressed.
;*************************************************************
		EXPORT READ_SWITCHES

READ_SWITCHES

		PUSH {R4-R7,R14}
		LDR R4,=PIOB_BASE
		LDR R5,[R4,#PIO_PDSR]
		; default return_val = NO_SW_PRESSED (0)
		MOV R0,#NO_SW_PRESSED
		; else if (PB27==0) return_val = LEFT_SW_PRESSED (2)
		TST R5,#LSW_val
		MOVEQ R0,#LEFT_SW_PRESSED
		; if (PB26==0) return_val = RIGHT_SW_PRESSED (1)
		TST R5,#RSW_val
		MOVEQ R0,#RIGHT_SW_PRESSED		
		POP {R4-R7,R14}
		BX R14

;*************************************************************
;    Function: CONTROL_LED
;    void CONTROL_LED(uint CONTROL_val)
;
;    if(CONTROL_VAL==OFF (1)) pewerLED switched OFF;
;    else if (CONTROL_VAL==ON (2)) powerLED switched ON;
;    else no change to powerLED;
;*************************************************************
		EXPORT CONTROL_LED

CONTROL_LED

		PUSH {R4-R7,R14}
		LDR R4,=PIOA_BASE
		MOV R5,#PA0_val
		; R0=CONTROL_VAL
		; else if (CONTROL_VAL==ON) powerLED switched ON, output a '1'
		TEQ R0,#ON_val
		STREQ R5,[R4,#PIO_SODR]
		; if (CONTROL_VAL==OFF) powerLED switched OFF, output a '0'
		TEQ R0,#OFF_val
		STREQ R5,[R4,#PIO_CODR]
		POP {R4-R7,R14}
		BX R14
		
		
;*************************************************************
;    Function: DELAY_ASM
;    void DELAY_ASM(uint DELAY_val)
;		          
;*************************************************************
		EXPORT DELAY_ASM

DELAY_ASM
		PUSH {R14}
		ADD R0, R0, R0     ; doubles DELAY_val
Delay_Loop		
		SUBS R0,R0,#1      ; Decrement DELAY_val by 1
		BNE Delay_Loop     ; Loop until DELAY_val==0
		POP {R14}
		BX R14
		
;***********************************************************
;    Function: INPUT_INIT
;    void INPUT_INIT(void)
;    
;    Enables the peripheral clocks for PIOA.
;    Sets PA11 as an input with internal pull-up resistor.
;    
;***********************************************************
		EXPORT INPUT_INIT

INPUT_INIT

	PUSH {R4-R7,R14}		; save values altered by this routine
	; Enable Peripheral Clocks for PIOA
	LDR R4,=PMC_BASE	    ; puts the base address of the Power 
                            ; Management Controller into R4
    MOV R5,#PIOA_val	    ; move the value to be placed in 
                            ; PMC_PCER into R5
	STR R5,[R4,#PMC_PCER]   ; stores the value in R5 into PMC_BASE (R4)
					        ; + the offset PMC_PCER (#0x0010)
					        ; R4 and R5 are not altered by the instruction	
	; Enable PA11(DS75 output) as an input
	LDR R4,=PIOA_BASE       ; Load Base Address of PIOB 
	MOV R5,#PA11_val        ; '1' set for PA11 
	STR R5,[R4,#PIO_PER]    ; Enable PIO, disable peripheral
	STR R5,[R4,#PIO_ODR]    ; Disable as output, Enable as input
	STR R5,[R4,#PIO_PUER]   ; Enable internal pull-up resistor
	POP {R4-R7,R14}		    ; restores the saved registers
	BX R14 			        ; return to calling program using link reg.


;*************************************************************
;    Function: READ_INPUT
;    uint READ_INPUT(void)
;
;    Reads the Pin Data Satus Reg of PIOA and outputs 
;    OUTPUT ACTIVE(4) if PA11 is low, and OUTPUT INACTIVE (0) 
;    if PA11 is high.
;*************************************************************
		EXPORT READ_INPUT

READ_INPUT

		PUSH {R4-R7,R14}
		LDR R4,=PIOA_BASE
		LDR R5,[R4,#PIO_PDSR]
		; default return_val = OUTPUT_INACTIVE (0)
		MOV R0,#OUTPUT_INACTIVE
		; if (PA11==0) return_val = OUTPUT_ACTIVE (4)
		TST R5,#PA11_val
		MOVEQ R0,#OUTPUT_ACTIVE	
		POP {R4-R7,R14}
		BX R14
		
		

		END