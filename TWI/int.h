

#ifndef INTERRUPT_LAB_H
#define INTERRUPT_LAB_H

#include <AT91SAM7SE512.H>
#include "types.h"
#include "timer.h"
#include "TWI.h"
#include "string.h"
//Temporary include:
#include "button.h"

/*
 * Constants also used by main.c
 */
#define COUNTER_MAX (65536)	
#define COVFS_MASK (1)
#define LDRBS_MASK (1 << 6)
#define RA (0)
#define RB (1)
#define SOUND_VELOCITY (1127) // in ft/s
#define MAX_INTERVALS (65)

void init_ISR( void );
void init_PITC( void );
void init_USART0(void);
void uart_tx( uint8 * data, uint8 num_bytes );









#endif
