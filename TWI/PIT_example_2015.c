/******************************************************************************/
/* PIT_example_2015.C: LED Flasher w/PIT INTERRUPT                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <AT91SAM7SE512.H>              /* AT91SAM7SE512 definitions          */
#include ".\AT91SAM7SE-EK.h"           /* AT91SAM7SE-EK board definitions    */

#include "IO_controlRY.h"


#undef  AT91B_LED_MASK
#define AT91B_LED_MASK      (AT91B_LED1|AT91B_LED2)


 
#define POS_PULSE_OUT (1<<15)
#define NEG_PULSE_OUT (1<<16)
#define OUTPUT_40K    (1<<0)
#define CAPTURE_INPUT (1<<26)

#define TIMER_OUTPUTS (POS_PULSE_OUT|NEG_PULSE_OUT|OUTPUT_40K|CAPTURE_INPUT)

#define interval_time_ms 50
#define interval_value ((AT91B_MCK/(16*1000))*50)

int intervals;


// ISR for Periodic Interval Controller

__irq void PITC_ISR (void)
{
	int temp;
	temp=AT91C_BASE_PITC->PITC_PIVR;  // clears flag that caused interrupt
	if(intervals==0)
	{
     // switch LED on
	}
	else if(intervals==9)
	{
		// switch LED off
	}
	intervals++;
	if(intervals>19) intervals=0;
	AT91C_BASE_AIC->AIC_EOICR=0;    // signals end of interrupt for AIC
}

// ISR for USART0


/*
 * Main Program
 */

int main (void) {
   unsigned int switch_input,temp,num_overflows,num_counts;


  // Enable the Clock of the PIO and all timer channels
  AT91C_BASE_PMC->PMC_PCER  = 1 << AT91C_ID_PIOA;				  
  AT91C_BASE_PMC->PMC_PCER  = 1 << AT91C_ID_PIOB;
  AT91C_BASE_PMC->PMC_PCER  = 1 << AT91C_ID_TC0;
	AT91C_BASE_PMC->PMC_PCER  = 1 << AT91C_ID_TC1;
	AT91C_BASE_PMC->PMC_PCER  = 1 << AT91C_ID_TC2;

  // Configure the PIO Lines for LEDs as Outputs
  AT91C_BASE_PIOA->PIO_PER  = AT91B_LED_MASK;
  AT91C_BASE_PIOA->PIO_OER  = AT91B_LED_MASK;
  AT91C_BASE_PIOA->PIO_PER  = AT91B_POWERLED;
  AT91C_BASE_PIOA->PIO_OER  = AT91B_POWERLED;
	
	// Disable PIO for Timer/Counter pins
	AT91C_BASE_PIOB->PIO_PDR = TIMER_OUTPUTS;
	

	// Initialize Advanced Interrupt Controller
	// for PITC
	AT91C_BASE_AIC->AIC_SMR[1]=0x60;
	AT91C_BASE_AIC->AIC_SVR[1]=(unsigned int)PITC_ISR;
	AT91C_BASE_AIC->AIC_IECR=1<<AT91C_ID_SYS;
	// for USART0
	
	// for Timer/Counter 2 overflow


  // Clear the LEDs. On the Board we must apply a "1" to turn off LEDs
  AT91C_BASE_PIOA->PIO_SODR = AT91B_LED_MASK;
	
  // Intialize Timer/Counter 0 to create 40KHz waveform
	AT91C_BASE_TC0->TC_CMR=0x0089C010;  // MCK/2, Continuous, Clear at RA, Set on RA, Gated with XC0, Wave=1
	AT91C_BASE_TC0->TC_RA=299;  // 12.5usec pulse width
	AT91C_BASE_TC0->TC_RC=598;  // 25.0usec cycle time (40KHz)
	
	// Initialize Timer/Counter 1 to create 100us active high pulse and 1ms active low pulse
  AT91C_BASE_TC1->TC_CMR=0x81428C40;  // MCK/2, One-shot, TIOA Clear at RA, TIOB Set at RB, Wave=1
	AT91C_BASE_TC1->TC_RA=2395;  // 100us pulse (4 - 40KHz clocks)
	AT91C_BASE_TC1->TC_RB=23961;  // 1ms pulse
	AT91C_BASE_TC1->TC_RC=35000;  // Stop at 1.4ms (one-shot pulse)
	
	// Initialize Timer/Counter 2 in capture mode
	AT91C_BASE_TC2->TC_CMR=0x000F0040;  // MCK/2, Capture Mode, LoadA any edge, LoadB & Stop any edge
	
	// Initialize Block mode to connect TIOA1 to XC0 and enable all timers
  AT91C_BASE_TCB->TCB_BMR=0x00000002;  // TIOA1=XC0, TCLK1=XC1, TCLK2=XC2
	AT91C_BASE_TC0->TC_CCR=0x00000001;  // Enable but do not start TC0
	AT91C_BASE_TC1->TC_CCR=0x00000001;  // Enable but do not start TC1
  AT91C_BASE_TC2->TC_CCR=0x00000001;  // Enable but do not start TC2

  // Initialize USART0
	
	
	// Initialize IO for powerLED control and switch input
	IO_INIT();
	INPUT_INIT();
	
  // Initialize global variables
	intervals=0;



  // Loop forever
  while (1) 
	{
      			

  }
}
