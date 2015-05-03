REGS512			EQU		1

; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled

; Internal Memory Base Addresses
FLASH_BASE      EQU     0x00100000   
RAM_BASE        EQU     0x00200000



; Timer/Counter (TC)
TC_BASE			EQU		0xFFFA0000
TC0_BASE		EQU 	0xFFFA0000
TC1_BASE		EQU		0xFFFA0040
TC2_BASE		EQU		0xFFFA0080
TC_BCR			EQU		0xC0
TC_BMR			EQU		0xC4
; Timer/Counter Channel Registers
TC_CCR			EQU		0x00
TC_CMR			EQU		0x04
TC_CV			EQU		0x10
TC_RA			EQU		0x14
TC_RB			EQU		0x18
TC_RC			EQU		0x1C
TC_SR			EQU		0x20
TC_IER			EQU		0x24
TC_IDR			EQU		0x28
TC_IMR			EQU		0x2C


; Two Wire Interface (TWI)
TWI_BASE		EQU		0xFFFB8000
TWI_CR			EQU		0x00
TWI_MMR			EQU		0x04
TWI_SMR		    EQU		0x08
TWI_IADR		EQU		0x0C
TWI_CWGR		EQU		0x10
TWI_SR			EQU		0x20
TWI_IER			EQU		0x24
TWI_IDR			EQU		0x28
TWI_IMR			EQU		0x2C
TWI_RHR         EQU     0x30
TWI_THR			EQU		0x34
 
;Universal Synchronous Asynchronous Receiver Transmitter (USART)
USART0_BASE		EQU		0xFFFC0000
USART1_BASE		EQU		0xFFFC4000
US_CR			EQU		0x0000
US_MR			EQU		0x0004
US_IER			EQU		0x0008
US_IDR			EQU		0x000C
US_IMR			EQU		0x0010
US_CSR			EQU		0x0014
US_RHR			EQU		0x0018
US_THR			EQU		0x001C
US_BRGR			EQU		0x0020
US_RTOR			EQU		0x0024
US_TTGR			EQU		0x0028
US_FIDI			EQU		0x0040
US_NER			EQU		0x0044
US_IF			EQU		0x004C
	

;  Pulse Width Modulator (PWM)
PWM_BASE		EQU		0xFFFCC000
PWM_MR			EQU		0x0000
PWM_ENA			EQU		0x0004
PWM_DIS			EQU		0x0008
PWM_SR			EQU		0x000C
PWM_IER			EQU		0x0010
PWM_IDR			EQU		0x0014
PWM_IMR			EQU		0x0018
PWM_ISR			EQU		0x001C
PWM_CMR0		EQU		0x0200
PWM_CDTY0		EQU		0x0204
PWM_CPRD0		EQU		0x0208
PWM_CCNT0		EQU		0x020C
PWM_CUPD0		EQU		0x0210
PWM_CMR1		EQU		0x0220
PWM_CDTY1		EQU		0x0224
PWM_CPRD1		EQU		0x0228
PWM_CCNT1		EQU		0x022C
PWM_CUPD1		EQU		0x0230
PWM_CMR2		EQU		0x0240
PWM_CDTY2		EQU		0x0244
PWM_CPRD2		EQU		0x0248
PWM_CCNT2		EQU		0x024C
PWM_CUPD2		EQU		0x0250
PWM_CMR3		EQU		0x0260
PWM_CDTY3		EQU		0x0264
PWM_CPRD3		EQU		0x0268
PWM_CCNT3		EQU		0x026C
PWM_CUPD3		EQU		0x0270


; Synchronous Serial Controller (SSC)
SSC_BASE		EQU		0xFFFD4000
SSC_CR			EQU		0x00
SSC_CMR			EQU		0x04
SSC_RCMR		EQU		0x10
SSC_RFMR		EQU		0x14
SSC_TCMR		EQU		0x18
SSC_TFMR		EQU		0x1C
SSC_RHR			EQU		0x20
SSC_THR			EQU		0x24
SSC_RSHR		EQU		0x30
SSC_TSHR		EQU		0x34
SSC_RC0R		EQU		0x38
SSC_RC1R		EQU		0x3C
SSC_SR			EQU		0x40
SSC_IER			EQU		0x44
SSC_IDR			EQU		0x48
SSC_IMR			EQU		0x4C
	

; Analog to Digital Converter (ADC)
ADC_BASE		EQU		0xFFFD8000
ADC_CR			EQU		0x0000
ADC_MR			EQU		0x0004
ADC_CHER		EQU		0x0010
ADC_CHDR		EQU		0x0014
ADC_CHSR		EQU		0x0018
ADC_SR			EQU		0x001C
ADC_LCDR		EQU		0x0020
ADC_IER			EQU		0x0024
ADC_IDR			EQU		0x0028
ADC_IMR			EQU		0x002C
ADC_CDR0		EQU		0x0030
ADC_CDR1		EQU		0x0034
ADC_CDR2		EQU		0x0038
ADC_CDR3		EQU		0x003C
ADC_CDR4		EQU		0x0040
ADC_CDR5		EQU		0x0044
ADC_CDR6		EQU		0x0048
ADC_CDR7		EQU		0x004C


; Serial Peripheral Interface (SPI)
SPI_BASE		EQU		0xFFFE0000
SPI_CR			EQU		0x00
SPI_MR			EQU		0x04
SPI_RDR			EQU		0x08
SPI_TDR			EQU		0x0C
SPI_SR			EQU		0X10
SPI_IER			EQU		0x14
SPI_IDR			EQU		0x18
SPI_IMR			EQU		0x1C
SPI_CSR0		EQU		0x30
SPI_CSR1		EQU		0x34
SPI_CSR2		EQU		0x38
SPI_CSR3		EQU		0x3C


; System Controller
SYSC_BASE		EQU 	0xFFFFF000

;Advanced Interrupt Control (AIC)

AIC_BASE		EQU		0xFFFFF000
; SOURCE MODE REGISTERS (SOURCE# * 4)
AIC_SMR1		EQU		0x0004
AIC_SMR2		EQU		0x0008
AIC_SMR3		EQU		0x000C
AIC_SMR4		EQU		0x0010
AIC_SMR5		EQU		0x0014
AIC_SMR6		EQU		0x0018
AIC_SMR7		EQU		0x001C
AIC_SMR8		EQU		0x0020
AIC_SMR9		EQU		0x0024
AIC_SMR10		EQU		0x0028
AIC_SMR11		EQU		0x002C
AIC_SMR12		EQU		0x0030
AIC_SMR13		EQU		0x0034
AIC_SMR14		EQU		0x0038
AIC_SMR15		EQU		0x003C
; SOURCE VECTOR REGISTERS ((SOURCE# * 4) + 0x80)
AIC_SVR1		EQU		0x0084
AIC_SVR2		EQU		0x0088
AIC_SVR3		EQU		0x008C
AIC_SVR4		EQU		0x0090
AIC_SVR5		EQU		0x0094
AIC_SVR6		EQU		0x0098
AIC_SVR7		EQU		0x009C
AIC_SVR8		EQU		0x00A0
AIC_SVR9		EQU		0x00A4
AIC_SVR10		EQU		0x00A8
AIC_SVR11		EQU		0x00AC
AIC_SVR12		EQU		0x00B0
AIC_SVR13		EQU		0x00B4
AIC_SVR14		EQU		0x00B8
AIC_SVR15		EQU		0x00BC
;
AIC_IVR			EQU 	0x0100
AIC_FVR			EQU		0x0104
AIC_ISR			EQU		0x0108
AIC_IPR			EQU		0x010C
AIC_IMR			EQU		0x0110
AIC_CISR		EQU		0x0114
AIC_IECR		EQU		0x0120
AIC_IDCR		EQU		0x0124
AIC_ICCR		EQU		0x0128
AIC_ISCR		EQU		0x012C
AIC_EOICR		EQU		0x0130
AIC_SPU			EQU		0x0134
AIC_DCR			EQU		0x0138
AIC_FFER		EQU		0x0140
AIC_FFDR		EQU		0x0144
AIC_FFSR		EQU		0x0148
	

; Parallel Input Output Controller
PIOA_BASE		EQU		0xFFFFF400
PIOB_BASE		EQU		0xFFFFF600
PIOC_BASE		EQU		0xFFFFF800
PIO_PER			EQU		0x0000
PIO_PDR			EQU		0x0004
PIO_PSR			EQU		0x0008
PIO_OER			EQU		0x0010
PIO_ODR			EQU		0x0014
PIO_OSR			EQU		0x0018
PIO_IFER		EQU		0x0020
PIO_IFDR		EQU		0x0024
PIO_IFSR		EQU		0x0028
PIO_SODR		EQU		0x0030
PIO_CODR		EQU		0x0034
PIO_ODSR		EQU		0x0038
PIO_PDSR		EQU		0x003C
PIO_IER			EQU		0x0040
PIO_IDR			EQU		0x0044
PIO_IMR			EQU		0x0048
PIO_ISR			EQU		0x004C
PIO_MDER		EQU		0x0050
PIO_MDDR		EQU		0x0054
PIO_MDSR		EQU		0x0058
PIO_PUDR		EQU		0x0060
PIO_PUER		EQU		0x0064
PIO_PUSR		EQU		0x0068
PIO_ASR			EQU		0x0070
PIO_BSR			EQU		0x0074
PIO_ABSR		EQU		0x0078
PIO_OWER		EQU		0x00A0
PIO_OWDR		EQU		0x00A4
PIO_OWSR		EQU		0x00A8


; Power Mangement Controller (PMC) definitions
PMC_BASE        EQU     0xFFFFFC00      ; PMC Base Address
PMC_MOR         EQU     0x20            ; PMC_MOR Offset
PMC_MCFR        EQU     0x24            ; PMC_MCFR Offset
PMC_PLLR        EQU     0x2C            ; PMC_PLLR Offset
PMC_MCKR        EQU     0x30            ; PMC_MCKR Offset
PMC_SR          EQU     0x68            ; PMC_SR Offset
PMC_MOSCEN      EQU     (1<<0)          ; Main Oscillator Enable
PMC_OSCBYPASS   EQU     (1<<1)          ; Main Oscillator Bypass
PMC_OSCOUNT     EQU     (0xFF<<8)       ; Main OScillator Start-up Time
PMC_DIV         EQU     (0xFF<<0)       ; PLL Divider
PMC_PLLCOUNT    EQU     (0x3F<<8)       ; PLL Lock Counter
PMC_OUT         EQU     (0x03<<14)      ; PLL Clock Frequency Range
PMC_MUL         EQU     (0x7FF<<16)     ; PLL Multiplier
PMC_USBDIV      EQU     (0x03<<28)      ; USB Clock Divider
PMC_CSS         EQU     (3<<0)          ; Clock Source Selection
PMC_PRES        EQU     (7<<2)          ; Prescaler Selection
PMC_MOSCS       EQU     (1<<0)          ; Main Oscillator Stable
PMC_LOCK        EQU     (1<<2)          ; PLL Lock Status
PMC_MCKRDY      EQU     (1<<3)          ; Master Clock Status
PMC_SCER		EQU		0x0000
PMC_SCDR		EQU		0x0004
PMC_SCSR		EQU		0x0008
PMC_PCER		EQU		0x0010
PMC_PCDR		EQU		0x0014
PMC_PCSR		EQU		0x0018
PMC_PCK0		EQU		0x0040
PMC_PCK1		EQU		0x0044
PMC_PCK2		EQU		0x0048

;// <e> Power Mangement Controller (PMC)
;//   <h> Main Oscillator
;//     <o1.0>      MOSCEN: Main Oscillator Enable
;//     <o1.1>      OSCBYPASS: Oscillator Bypass
;//     <o1.8..15>  OSCCOUNT: Main Oscillator Startup Time <0-255>
;//   </h>
;//   <h> Phase Locked Loop (PLL)
;//     <o2.0..7>   DIV: PLL Divider <0-255>
;//     <o2.16..26> MUL: PLL Multiplier <0-2047>
;//                 <i> PLL Output is multiplied by MUL+1
;//     <o2.14..15> OUT: PLL Clock Frequency Range
;//                 <0=> 80..160MHz  <1=> Reserved
;//                 <2=> 150..220MHz <3=> Reserved
;//     <o2.8..13>  PLLCOUNT: PLL Lock Counter <0-63>
;//     <o2.28..29> USBDIV: USB Clock Divider
;//                 <0=> None  <1=> 2  <2=> 4  <3=> Reserved
;//   </h>
;//   <o3.0..1>   CSS: Clock Source Selection
;//               <0=> Slow Clock
;//               <1=> Main Clock
;//               <2=> Reserved
;//               <3=> PLL Clock
;//   <o3.2..4>   PRES: Prescaler
;//               <0=> None
;//               <1=> Clock / 2    <2=> Clock / 4
;//               <3=> Clock / 8    <4=> Clock / 16
;//               <5=> Clock / 32   <6=> Clock / 64
;//               <7=> Reserved
;// </e>
;PMC_SETUP       EQU     1
;PMC_MOR_Val     EQU     0x00000601
;PMC_PLLR_Val    EQU     0x00491C0E
;PMC_MCKR_Val    EQU     0x00000007



; Reset Controller (RSTC) definitions
RSTC_BASE       EQU     0xFFFFFD00      ; RSTC Base Address
RSTC_MR         EQU     0x08            ; RSTC_MR Offset

;/*
;// <e> Reset Controller (RSTC)
;//   <o1.0>     URSTEN: User Reset Enable
;//              <i> Enables NRST Pin to generate Reset
;//   <o1.8..11> ERSTL: External Reset Length <0-15>
;//              <i> External Reset Time in 2^(ERSTL+1) Slow Clock Cycles
;// </e>
;*/
RSTC_SETUP      EQU     1
RSTC_MR_Val     EQU     0xA5000401


; Real-Time Timer

RTT_BASE		EQU		0xFFFFFD20
RTT_MR			EQU		0x00
RTT_AR			EQU		0x04
RTT_VR 			EQU		0x08
RTT_SR			EQU		0x0C
	
	
; Periodic Interval Timer

PIT_BASE		EQU		0xFFFFFD30
PIT_MR			EQU		0x00
PIT_SR			EQU		0x04
PIT_PIVR 		EQU		0x08
PIT_PIIR		EQU		0x0C

; Watch Dog Timer

WDT_BASE		EQU		0xFFFFFD40
WDT_CR			EQU		0x00
WDT_MR			EQU		0x04
WDT_SR 			EQU		0x08





; Static Memory Controller

SMC_BASE        EQU     0xFFFFFF90
SMC_CSR0        EQU     0x00
SMC_CSR1        EQU     0x04
SMC_CSR2        EQU     0x08
SMC_CSR3        EQU     0x0C
SMC_CSR4        EQU     0x10
SMC_CSR5        EQU     0x14
SMC_CSR6        EQU     0x18
SMC_CSR7        EQU     0x1C
	
	
	
; PID Number Definitions
PIOA_PID		EQU		1<<2
PIOB_PID		EQU		1<<3
PIOC_PID		EQU		1<<4
SPI_PID			EQU		1<<5
USART0_PID		EQU		1<<6
USART1_PID		EQU		1<<7
SSC_PID			EQU		1<<8
TWI_PID			EQU		1<<9
PWMC_PID		EQU		1<<10
UDP_PID			EQU		1<<11
TC0_PID			EQU		1<<12
TC1_PID			EQU		1<<13
TC2_PID			EQU		1<<14
ADC_PID			EQU		1<<15
	
	
				END