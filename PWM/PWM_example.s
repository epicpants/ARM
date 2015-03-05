;*************************************************************************************
;*  PWM_example.s
;*		Routines for initializing and updating PWM
;*		
;*		CpE4151 Experiment #2, Spring 2015
;*************************************************************************************
;*		Version 1.0												Roger Younger
;*************************************************************************************
;*		
;*	CONSTANT DECLARATIONS

			INCLUDE AT91SAM7SE512.INC





;******************************************************************************
;*	AREA DEFINITION
								 
			PRESERVE8
			AREA PWM,CODE,READONLY
			ARM

;******************************************************************************
;*	INITIALIZATION ROUTINE			void INIT_PWM(R0=PWM_Num,R1=Prescale, R2=Polarity,R3=Align)
;*		Sets up the specified PWM channels
;*		  
;*		
;*******************************************************************************


			EXPORT INIT_PWM

INIT_PWM
			PUSH {R4,R5,R6,R14}

            ; Enable the peripheral clock
			LDR R4,=PMC_BASE
			MOV R5,#PWMC_PID
			STR R5,[R4,#PMC_PCER]

			; Setup I/O pins
			LDR R4,=PIOA_BASE
			MOV R5,#PA2_PA0
			AND R5,R5,R0
			STR R5,[R4,#PIO_PDR]
			STR R5,[R4,#PIO_ASR]

			LDR R4,=PIOB_BASE
			MOV R5,#PB14_PB11
			AND R5,R5,R0,LSL #11
			STR R5,[R4,#PIO_PDR]
			STR R5,[R4,#PIO_ASR]

			; Create Channel Mode Register (PWM_CMRx) value using Clock_Sel, Polarity, and Alignment
			AND R5,R1,#0x0F ; limit to 4 bits
			AND R2,R2,#0x01 ; limit to 1 bit
			AND R3,R3,#Ox01 ; limit to 1 bit
			ORR R5,R5,R2,LSL #9
			ORR R5,R5,R3,LSL #8

			; Write to CMR for each PWM_num
			; DO
			LDR R4,=PWM_BASE
			MOV R6,#0x01 ; Channel mask

BEGIN_CMR_LOOP
			; If ( ( channel_mask & PWM_Num ) != 0 )
			TST R6,R0
			; Then write value to CMRx
			STRNE R5,[R4,#PWM_CMR0]
			; End-If {channel_mask}
			; Point to next channel
			MOV R6,R6,LSL #1
			ADD R4,R4,#0x20 ; offset CMR by 1
			; While ( ( channel_mask & all_channels ) != 0 )
			TST R6,#0x0F
			BNE BEGIN_CMR_LOOP
			; End-Do-While {channel_mask}

			POP {R4,R5,R6,R14}
			BX R14


;******************************************************************************
;*	SET PWM PRESCALE	error_flag SET_PWM_CLK(R0=DIVIDER,R1=CLK)
;*		Sets up the specified DIVA or DIVB clk
;*		  
;*		
;*******************************************************************************			
			
			EXPORT SET_PWM_CLK

SET_PWM_CLK
            PUSH {R4,R5,R6,R7,R14}
            NOP
            POP {R4,R5,R6,R7,R14}
            BX R14


;******************************************************************************
;*	Enable PWM	void ENABLE_PWM(R0=PWM_NUM,R1=PERIOD)
;*		Enables the selected PWM channels with the specified period 
;*		  
;*		
;*******************************************************************************			
			
			EXPORT ENABLE_PWM

ENABLE_PWM
            PUSH {R4,R5,R6,R14}
            NOP
			POP {R4,R5,R6,R14}
			BX R14


;******************************************************************************
;*	UPDATE PWM 			ERROR_FLAG UPDATE_PWM(R0=PWM_NUM,R1=UPDATE_VAL)
;*		Assumes that the duty cycle register is the default for update
;*		and writes input value to PWM_CUPDX registerS 
;*******************************************************************************
			

			EXPORT UPDATE_PWM

UPDATE_PWM
			PUSH {R4,R5,R6,R7,R8,R9,R14}
            NOP
			POP {R4,R5,R6,R7,R8,R9,R14}
			BX R14




			END





