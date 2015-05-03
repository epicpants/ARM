/******************************************************************************/
/* timer.h:                                                                  */
/* Jon Eftink & Tyler Ryan                                                    */
/******************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#define T_FREQ (41.7334E-9)
#include "types.h"

//This function will initialize timer 0 to generate a 40 kHz square wave.
extern void TMR_INIT(void);
extern void START_TIMERS(void);
extern uint32 READ_TC2_SR(void);
extern uint32 READ_TC2_REGISTER(uint32 register_mask);



#endif
