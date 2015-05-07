;******************************************************************************
;* timer.asm:                                                                  *
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
;    Function: TMR_INIT_T0
;    This function will initialize timer 0 to generate a 
;        40 kHz square wave. Timer 0 is gated by timer 1. 
;        Timer 1 enables timer 0 for 100us. A software
;        trigger is required to start timer 0 and 1.
;***********************************************************
		EXPORT TMR_INIT
TMR_INIT       
    PUSH{ R4, R5, R14 }
    
    ; Enable Peripheral Clock for Timer 0, 1, and 2:
	LDR R4,=PMC_BASE	                               
    MOV R5, #TC0_PID	                                    
	STR R5,[R4,#PMC_PCER]  
    MOV R5, #TC1_PID
    STR R5, [R4, #PMC_PCER]
	MOV R5, #TC2_PID
    STR R5, [R4, #PMC_PCER]

    ; Set Timer/Counter 0, 1, and 2 pins to be controlled by peripheral:
	LDR R4,=PIOB_BASE
	MOV R5, #TIOA0
    ORR R5, R5, #TIOA1
    ORR R5, R5, #TIOB1
	ORR R5, R5, #TIOA2
	STR R5,[R4,#PIO_PDR]
	STR R5,[R4,#PIO_ASR]
    
    ;Timer 0:
        ;Set the mode register, RA and RC registers to generate 40kHz wave:
    MOV R5, #0
    LDR R4, =TC0_BASE
    ORR R5, R5, #WAVE_MODE ;Set Timer 0 to Waverform mode
    ORR R5, R5, #CLEAR_RA  ;Set TIOA to clear on RA compare
    ORR R5, R5, #SET_RC    ;Set TIOA to set on RC compare 
    ORR R5, R5, #BURST_MODE ;Clock is ANDed with XCO
    ORR R5, R5, #AUTO_TRG  ;Up mode with auto trigger on RC compare
    STR R5, [R4, #TC_CMR]  ;Set Mode Register
    LDR R5, =REG_CT0_VAL
    STR R5, [R4, #TC_RC]   ;Set RC reg
    LDR R5, =REG_AT0_VAL
    STR R5, [R4, #TC_RA]   ;Set RA reg
    
    ;TIMER 1:
        ;Set the mode register, and RA to generate enable burst for Timer 0 wave generation:
    LDR R4, =TC1_BASE
    MOV R5, #0 
    ORR R5, R5, #WAVE_MODE ;Set timer 1 to Waveform mode
    ORR R5, R5, #SEL_XC0   ;Set TIOB1 to external event XCO
    ORR R5, R5, #AUTO_TRG  ;Up mode with auto trigger on RC compare
    ORR R5, R5, #CLEAR_RA  ;Clear TIOA1 on RA compare
    ORR R5, R5, #SWTRG_SET_A ;Set TIOA1 on SWTRG
    ORR R5, R5, #SWTRG_CLR_B ;Clear TIOB1 on SWTRG
    ORR R5, R5, #SET_RB  ;Set TIOB1 on RB compare
    ORR R5, R5, #STOP_ON_RC ;Stop the counter on RC compare
    STR R5, [R4, #TC_CMR] ;Set mode register
    LDR R5, =REG_AT1_VAL
    STR R5, [R4, #TC_RA]  ;Set RA value for 100us
    LDR R5, =REG_BT1_VAL
    STR R5, [R4, #TC_RB]   ;Set RB value for 1ms
    STR R5, [R4, #TC_RC]   ;Set RC value to be equal to RB.
    
    ;Connect TIOA1 to XCO using block mode register:
    MOV R5, #22 ;Select TIOA1 for XCO
    LDR R4, =TC_BASE
    STR R5, [R4, #TC_BMR]
    
	; TIMER 2:
		; Set the mode register
	LDR R4, =TC2_BASE
	;LDR R5, [R4, #TC_CMR]
	;BIC R5, R5, #WAVE_MODE ; Clears the wave bit (enables capture mode)
	MOV R5, #0
	ORR R5, R5, #RISING_RA	; Load RA on rising edge
	ORR R5, R5, #FALLING_RB	; Load RB on falling edge
	ORR R5, R5, #STOP_ON_RB	; Stop capture mode after RA and RB filled (i.e. after RB filled)
	STR R5, [R4, #TC_CMR]	; Set mode register
	MOV R5, #COVENABLE
	STR R5, [R4, #TC_IER]	; Enable Counter Overflow Interrupt
	 
    
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


;***********************************************************
;    Function: START_TIMERS
;    This function will set the sync bit in TC block control 
;        register (TC_BCR). This should synchronously start  
;        timer 0 and timer 1.
;***********************************************************
		EXPORT START_TIMERS
START_TIMERS       
    PUSH{ R4, R5, R14 }

	LDR R4, =TC_BASE
	MOV R5, #1
	STR R5, [R4, #TC_BCR]
	
	POP{ R4, R5, R14 }
	BX R14  
	
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
	
;***********************************************************
;    Function: READ_TC2_SR
;    This function will read the status register of Timer 2. 
;        It returns the 32-bit contents of that register.
;***********************************************************
		EXPORT READ_TC2_SR
READ_TC2_SR       
    PUSH{ R4, R14 }

	LDR R4, =TC2_BASE
	LDR R0, [R4, #TC_SR]
	
	POP{ R4, R14 }
	BX R14
	
;***********************************************************
;    Function: READ_TC2_REGISTER( Register Mask )
;    This function will read RA or RB of Timer 2. 
;        Register Mask = 0 -> RA will be returned.  
;        Register Mask = 1 -> RB will be returned.
;***********************************************************
		EXPORT READ_TC2_REGISTER
READ_TC2_REGISTER       
    PUSH{ R4, R5, R14 }

	LDR R4, =TC2_BASE
	MOVS R5, R0
	LDREQ R0, [R4, #TC_RA]
	LDRNE R0, [R4, #TC_RB]
	
	POP{ R4, R5, R14 }
	BX R14 
    
    END