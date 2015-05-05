

#ifndef INTERRUPT_LAB_H
#define INTERRUPT_LAB_H

#include <AT91SAM7SE512.H>
#include "types.h"
#include "timer.h"
#include "string.h"
//Temporary include:
#include "button.h"



void init_ISR( void );
void init_PITC( void );
void init_USART0(void);
void uart_tx( uint8 * data, uint8 num_bytes );









#endif
