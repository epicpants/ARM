/******************************************************************************/
/* main.c:                                                                  */
/* Jon Eftink & Tyler Ryan                                                    */
/******************************************************************************/



#include <AT91SAM7SE512.H>              /* AT91SAM7SE512 definitions          */
#include ".\AT91SAM7SE-EK.h"           /* AT91SAM7SE-EK board definitions    */
#include "timer.h"
#include "button.h"
#include "types.h"
#include "int.h"

int main(void)
{
	uint32 i, TC_SR, reg_A, reg_B, num_overflows, num_counts, velocity;
	float time, distance;
	
	TMR_INIT();
	IO_INIT();          //initialize pushbuttons
	init_buttons();     //Initialize the global button structs in button.c

    init_PITC();
    init_USART0();
    init_ISR();
    
	while(1) 
    {
		//num_overflows = 0;
		//num_counts = 0;
		
		//update_buttons();

		/*
		 * Wait for a switch to be pressed
		 */
		/*while ( buttons[LEFT_SWITCH].status == NOT_PRESSED ) {
			//Delay for ~1 ms
      for(i = 0; i != 5000; i++);	
			update_buttons();
		}*/

		/*
		 * Start timers, generating a burst of waveforms once a switch has been pressed
		 */
		/*START_TIMERS();

		do {
			TC_SR = READ_TC2_SR();
			if ( ( TC_SR & COVFS_MASK ) == COVFS_MASK ) {
				num_overflows++;
			}
		} while ( ( TC_SR & LDRBS_MASK ) == 0 );

		reg_A = READ_TC2_REGISTER( RA );
		reg_B = READ_TC2_REGISTER( RB );

		velocity = SOUND_VELOCITY;
		num_counts = ( num_overflows * COUNTER_MAX ) + reg_B - reg_A;
		time = T_FREQ * num_counts;
		distance = ( time * velocity ) / 2;
		
		if ( distance > 3 );
		i++;*/

	}
      
	return 0;
}
