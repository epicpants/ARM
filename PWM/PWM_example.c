/******************************************************************************/
/* PWM_example.C:                                                             */
/* Jon Eftink & Tyler Ryan                                                    */
/******************************************************************************/

/******************************************************************************/
                  
#include <AT91SAM7SE512.H>              /* AT91SAM7SE512 definitions          */
#include ".\AT91SAM7SE-EK.h"           /* AT91SAM7SE-EK board definitions    */
#include "PWM_example.h"
#include "types.h"
#include "button.h"
#include <stdio.h>


#define PERIOD     256
#define CLK_DIV    1872
#define ACTIVE_LOW 0
#define LEFT_ALIGN 0

#define LED_OFF     1
#define LED_ON      2
 
/*
 * Main Program
 */

int main (void) {
    uint32 flag;       //flag to to be raised if brightness has been changed.
    uint32 i;          //Index variable
    uint32 brightness; // value for the brightness of an LED. Range: [0, 255]
    uint32 LED_value;  //Status of the right LED
    
    LED_value = LED_ON; // Initialize the right LED to on.
    brightness = 128;   //Initialize the brightness to half of the max.
    flag = TRUE;        //Update the duty cycle on the first iteration of the super loop.
    
    IO_INIT();          //initilize pushbuttons and right LED.
    CONTROL_LED( LED_value ); //turn on the LED.
    
    init_buttons();     //Initialize the global button structs in button.c
    
    // Initialize PWM and set PWM clock
    INIT_PWM( PWM1, CLKA, (uint32)ACTIVE_LOW, (uint32)LEFT_ALIGN );
	  SET_PWM_CLK( (uint32)CLK_DIV, CLKA );
    
    ENABLE_PWM( PWM1, (uint32)PERIOD );
    
    while( TRUE )
    {
        if( flag == TRUE )
        {
            UPDATE_PWM( PWM1, brightness );
            flag = FALSE;
        }

        //Delay for ~1 ms
        for(i = 0; i != 5000; i++);
        
        //Flip the LED (used to determine how long the previous for loop should delay)
        if( LED_value == LED_ON )
        {
            CONTROL_LED( LED_OFF );
            LED_value = LED_OFF;
        }
        else
        {
            CONTROL_LED( LED_ON );
            LED_value = LED_ON;
        }
        
        update_buttons();
        
        if( buttons[LEFT_SWITCH].status == PRESSED )
        {
            if( brightness > 20 )
            {
                brightness = brightness - 20;
            }
            else
            {
                brightness = 0;
            }
            
            flag = TRUE;
        }
        if( buttons[RIGHT_SWITCH].status == PRESSED )
        {
            if( brightness < ( PERIOD - 20 ) )
            {
                brightness = brightness + 20;
            }
            else
            {
                brightness = PERIOD - 1;
            }
            flag = TRUE;
        }
        
    }
	
	
}
