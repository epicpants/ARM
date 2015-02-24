;*********************************************************************
;    Example Assmbly - This file contains three "do-nothing" functions
;        that are setup so that they can be called from a C program
;        using the extern keyword in C.  The exported label is the
;        name of the function in C.  The functions save and restore
;        some registers so that they can be used in the function, but
;        not altered in the C program.
;*********************************************************************
;    Code written by: Roger Younger
;    v1.0 Released: March 3, 2010
;*********************************************************************
;    CONSTANT DEFINITIONS
;*********************************************************************
		INCLUDE AT91SAM7SE512.INC

LED1         EQU 1<<1
LED2         EQU 1<<2
LED_MASK     EQU LED1:OR:LED2	
UP_SW        EQU 1<<23
DOWN_SW      EQU 1<<24
LEFT_SW      EQU 1<<27
RIGHT_SW     EQU 1<<26
PUSH_SW      EQU 1<<25	
LEFT_PB      EQU 1<<25
RIGHT_PB     EQU 1<<22
SW_MASK      EQU UP_SW:OR:DOWN_SW:OR:LEFT_SW:OR:RIGHT_SW:OR:LEFT_PB:OR:RIGHT_PB	




;***********************************************************
;    AREA DEFINITION AND OPTIONS
;***********************************************************
		PRESERVE8
		AREA VARIABLES,DATA,READWRITE
			
var1_g DCD 0
var2_g DCD 25

		AREA EXAMPLE,CODE,READONLY
		ARM
;***********************************************************
;    Function: void INIT_CLOCKS (void)
;       enables the clocks for PIOA and PIOB
;***********************************************************
		EXPORT INIT_CLOCKS

INIT_CLOCKS
		PUSH {R4-R5,R14}
        ; ENABLE PIOA CLOCK
        LDR R4,=PMC_BASE
		MOV R5,#PIOA_PID
        STR R5,[R4,#PMC_PCER]
        ; ENABLE PIOB CLOCK
		;LDR R4,=PMC_BASE      ; R4 ALREADY EQUALS PMC_BASE
		MOV R5,#PIOB_PID
        STR R5,[R4,#PMC_PCER]        		
		POP {R4-R5,R14}
		BX R14


;***********************************************************
;    Function: void INIT_PIOA (void)
;       Sets PIOA pins as outputs to drive LEDs
;***********************************************************
		EXPORT INIT_PIOA

INIT_PIOA
		PUSH {R4-R5,R14}
        ; ENABLE PI0A
        LDR R4,=PIOA_BASE
		MOV R5,#LED_MASK
        STR R5,[R4,#PIO_PER]      		
		POP {R4-R5,R14}
		BX R14


;***********************************************************
;    Function: void INIT_PIOB (void)
;       Sets PIOB pins as inputs to read switches
;***********************************************************
		EXPORT INIT_PIOB

INIT_PIOB
		PUSH {R4-R5,R14}
        ; ENABLE PI0B
        LDR R4,=PIOB_BASE
		MOV R5,#SW_MASK
        STR R5,[R4,#PIO_PER]
        ; ENABLE PIOB INPUTS
		;LDR R4,=PIOB_BASE      ; R4 ALREADY EQUALS PMC_BASE
		;MOV R5,#SW_MASK       ; R5 ALREADY EQUALS LED_MASK
        STR R5,[R4,#PIO_ODR]        
        ; ENABLE PIOB PULL UP RESISTORS
		;LDR R4,=PIOB_BASE      ; R4 ALREADY EQUALS PMC_BASE
		;MOV R5,#SW_MASK       ; R5 ALREADY EQUALS LED_MASK
        STR R5,[R4,#PIO_PUER]        		
		POP {R4-R5,R14}
		BX R14
		
		
;***********************************************************
;    Function: void LEFT_PB_WAIT (void)
;       Sets PIOB pins as inputs to read switches
;***********************************************************
		EXPORT LEFT_PB_WAIT

LEFT_PB_WAIT
		PUSH {R4-R5,R14}
        ; READ PIOB PINS
        LDR R4,=PIOB_BASE
		; WHILE (LEFT_PB IS PRESSED)
BEGIN_LEFT_PB
		LDR R5,[R4,#PIO_PDSR]
        TST R5,#0x00400000
		BEQ END_LEFT_PB
		; NO ACTION 
		B BEGIN_LEFT_PB
		; END_WHILE {LEFT_PB IS PRESSED}
END_LEFT_PB     		
		POP {R4-R5,R14}
		BX R14
;*************************************************************
;    Function: LED_ON
;
;*************************************************************
		EXPORT LED_ON

LED_ON

		PUSH {R4-R7,R14}
		NOP
		NOP
		NOP
		POP {R4-R7,R14}
		BX R14

;*************************************************************
;    Function: LED_OFF
;
;*************************************************************
		EXPORT LED_OFF

LED_OFF

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