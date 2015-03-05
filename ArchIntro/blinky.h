/*
 * Authors: Jon Eftink and Tyler Ryan
 * Assembly function prototypes
 */
#ifndef BLINKY_H
#define BLINKY_H

extern void IO_INIT( void );
extern unsigned int READ_SWITCHES( void );
extern void CONTROL_LED( unsigned int value);
extern void DELAY_ASM( unsigned int delay );
#endif
