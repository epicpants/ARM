
#include <AT91SAM7SE512.H>              /* AT91SAM7SE512 definitions          */
#include ".\AT91SAM7SE-EK.h"           /* AT91SAM7SE-EK board definitions    */
#include "timer.h"
#include "button.h"

int main(void)
{
    TMR_INIT();
	IO_INIT();          //initilize pushbuttons
	init_buttons();     //Initialize the global button structs in button.c
    
    while(1) {
		  update_buttons();

		  /*
		   * Wait for a switch to be pressed
		   */
		  while( buttons[LEFT_SWITCH].status == NOT_PRESSED && buttons[RIGHT_SWITCH].status == NOT_PRESSED ) {
		  		update_buttons();
		  }

		  /*
		   * Start timers, generating a burst of waveforms once a switch has been pressed
		   */
		  START_TIMERS();
	}
    
    
    return 0;
}
