;******************************************************************************
;* timer.asm:                                                                 *
;* Jon Eftink & Tyler Ryan                                                    *
;******************************************************************************

;*********************************************************************
;    CONSTANT DEFINITIONS
;*********************************************************************
    INCLUDE AT91SAM7SE512.INC
TIOA0 EQU 1 << 0
TIOA1 EQU 1 << 15
TIOB1 EQU 1 << 16
TIOA2 EQU 1 << 17
WAVE_MODE EQU 1 << 15
BURST_MODE EQU 1 << 4  ;Clock is ANDed with XCO
AUTO_TRG EQU 2 << 13   ;UP mode with automatic trigger on RC compare
CLEAR_RA EQU 2 << 16
RISING_RA EQU 1 << 16
FALLING_RB EQU 1 << 19
SET_RB EQU 1 << 24
SET_RC EQU 1 << 18
SWTRG_SET_A EQU 1 << 22
SWTRG_CLR_B EQU 2 << 30
REG_CT0_VAL EQU 599
REG_AT0_VAL EQU 299
REG_AT1_VAL EQU 2396
REG_BT1_VAL EQU 23961    
    
ENABLE_CLK EQU 1 << 16
SEL_XC0 EQU 1 << 10
STOP_ON_RC EQU 1 << 6
STOP_ON_RB EQU 1 << 6
COVENABLE EQU 1 << 0
CLKEN EQU 1 << 0
CLKDIS EQU 1 << 1
        
;***********************************************************
;    AREA DEFINITION AND OPTIONS
;***********************************************************
		PRESERVE8

		AREA EXAMPLE,CODE,READONLY
		ARM
        
	
;***********************************************************
;    Function: STOP_TIMERS
;    This function will disable Timers 0, 1, and 2 to stop
;        them. It will then enable them again so they can  
;        be restarted later.
;***********************************************************
		EXPORT STOP_TIMERS
STOP_TIMERS       
    PUSH{ R4, R5, R14 }

	;Disable Timer 0:
    LDR R4, =TC0_BASE
    MOV R5, #CLKDIS              
    STR R5, [R4, #TC_CCR]   ;Disables clock
    
    ;Disable Timer 1:
    LDR R4, =TC1_BASE
    MOV R5, #CLKDIS              
    STR R5, [R4, #TC_CCR]   ;Disables clock

	; Disable Timer 2:
	LDR R4, =TC2_BASE
	MOV R5, #CLKDIS              
    STR R5, [R4, #TC_CCR]   ;Disables clock
	
	;Enable Timer 0:
    LDR R4, =TC0_BASE
    MOV R5, #CLKEN              
    STR R5, [R4, #TC_CCR]   ;Enables clock
    
    ;Enable Timer 1:
    LDR R4, =TC1_BASE
    MOV R5, #CLKEN              
    STR R5, [R4, #TC_CCR]   ;Enables clock

	; Enable Timer 2:
	LDR R4, =TC2_BASE
	MOV R5, #CLKEN              
    STR R5, [R4, #TC_CCR]   ;Enables clock
	
	POP{ R4, R5, R14 }
	BX R14  
	
	END