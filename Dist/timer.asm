
;*********************************************************************
;    CONSTANT DEFINITIONS
;*********************************************************************
    INCLUDE AT91SAM7SE512.INC
TIOA0 EQU 1 << 0
WAVE_MODE EQU 1 << 15
CLEAR_RA EQU 2 << 16
SET_RC EQU 1 << 18
REG_C_VAL EQU 599
REG_A_VAL EQU 299
ENABLE_CLK EQU 1 << 16
        
;***********************************************************
;    AREA DEFINITION AND OPTIONS
;***********************************************************
		PRESERVE8

		AREA EXAMPLE,CODE,READONLY
		ARM
        
;***********************************************************
;    Function: TMR_INIT_T0
;    This function will initialize timer 0 to generate a 
;        40 kHz square wave.
;***********************************************************
		EXPORT TMR_INIT
TMR_INIT       
    PUSH{ R14 }
    
    ; Enable Peripheral Clock for Timer/Counter 0:
	LDR R4,=PMC_BASE	                               
    MOV R5, #TC0_PID	                                    
	STR R5,[R4,#PMC_PCER]  

    ; Set Timer/Counter 0 pin to be controlled by peripheral:
	LDR R4,=PIOB_BASE
	MOV R5, #TIOA0
	STR R5,[R4,#PIO_PER]
    
    ;Set the mode register, RA and RC registers to generate 40kHz wave:
    MOV R5, #0
    LDR R4, =TC0_BASE
    ORR R5, R5, #WAVE_MODE ;Set Timer 0 to Waverform mode
    ORR R5, R5, #CLEAR_RA  ;Set TIOA to clear on RA compare
    ORR R5, R5, #SET_RC    ;Set TIOA to set on RC compare   
    STR R5, [R4, #TC_CMR]  ;Set Mode Register
    LDR R5, =REG_C_VAL
    STR R5, [R4, #TC_RC]   ;Set RC reg
    LDR R5, =REG_A_VAL
    STR R5, [R4, #TC_RA]   ;Set RA reg
    
    ;Enable/start timer 0:
    MOV R5, #ENABLE_CLK
    STR R5, [R4, #TC_SR]


    POP{ R14 }
    BX R14 
    
    
    END