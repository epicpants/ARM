/******************************************************************************/
/* BLINKY.C: LED Flasher                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <AT91SAM7SE512.H>              /* AT91SAM7SE512 definitions          */
#include "AT91SAM7SE-EK.h"           /* AT91SAM7SE-EK board definitions    */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


//#include "serialRY.h"

#define SPEED (AT91B_MAIN_OSC/1000)

#undef  AT91B_NB_LEB
#define AT91B_NB_LEB        2
#undef  AT91B_LED_MASK
#define AT91B_LED_MASK      (AT91B_LED1|AT91B_LED2)

extern void INIT_CLOCKS(void);
extern void INIT_PIOA(void);
extern void INIT_PIOB(void);
extern void LEFT_PB_WAIT(void);

const int led_mask[] = { AT91B_LED1, AT91B_LED2 };

unsigned int LEDSpeed = 50*SPEED;


/* 
 * Change Speed depending on SW1 and SW2
 */

void change_speed (void) {
  if ((AT91C_BASE_PIOB->PIO_PDSR & AT91B_SW1) == 0) {
    if (LEDSpeed > SPEED) LEDSpeed -= SPEED;
  }
  if ((AT91C_BASE_PIOB->PIO_PDSR & AT91B_SW2) == 0) {
    if (LEDSpeed < AT91B_MCK)   LEDSpeed += SPEED;
  }
}


/*
 * Wait Function (SW Waiting Loop)
 *   Waiting Time defined by global variable LEDSpeed
 */
 
void wait (void) {
  unsigned int n;

  change_speed();
  for (n = 0; n < LEDSpeed; n++);
	

  // While joystick (middle) pressed pause the LED blinking
  LEFT_PB_WAIT();
  
}
 
/*
 * Main Program
 */

int main (void) {
  int i;
	

  // Enable the Clock of the PIO
  INIT_CLOCKS();

  // Configure the PIO Lines for LEDs as Outputs
  INIT_PIOA();
  INIT_PIOB();

  // Clear the LEDs. On the Board we must apply a "1" to turn off LEDs
  AT91C_BASE_PIOA->PIO_SODR = AT91B_LED_MASK;
	

  // Loop forever
  for (;;) {
    for (i = 0; i < AT91B_NB_LEB; i++) {
      AT91C_BASE_PIOA->PIO_CODR = led_mask[i];
      wait();
      AT91C_BASE_PIOA->PIO_SODR = led_mask[i];
      wait();
    }
    for (i = (AT91B_NB_LEB - 1); i >= 0; i--) {
      AT91C_BASE_PIOA->PIO_CODR = led_mask[i];
      wait();
      AT91C_BASE_PIOA->PIO_SODR = led_mask[i];
      wait();
    }
  }
}
