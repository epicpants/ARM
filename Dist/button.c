/******************************************************************************/
/* Button.c:                                                                  */
/* Jon Eftink & Tyler Ryan                                                    */
/******************************************************************************/

#include "button.h"

#define DEBOUNCE_NUM 50

button buttons[NUM_BUTTONS];

//Initialize the buttons' status to not pressed.
void init_buttons()
{
    uint32 index;
    
    for( index = 0; index < NUM_BUTTONS; index++)
    {
        buttons[index].count = 0;
        buttons[index].status = NOT_PRESSED;
        buttons[index].mask = ( 1 << index );
    }
}

//Update the buttons
void update_buttons()
{   
    uint32 pressed_buttons;
    uint32 index;
    
    pressed_buttons = READ_SWITCHES();
    
    for( index = (uint32)0; index < NUM_BUTTONS; index++ )
    {
        if( buttons[index].mask == 0 )
            buttons[index].status = ERR;
        
        switch( buttons[index].status )
        {
            case NOT_PRESSED:
                //If the button is pressed:
                if( ( pressed_buttons & buttons[index].mask ) == buttons[index].mask )
                {
                    buttons[index].count = 0;
                    buttons[index].status = DEBOUNCE;
                }
                break;
            case DEBOUNCE:
                //If the button is pressed:
                if( ( pressed_buttons & buttons[index].mask ) == buttons[index].mask )
                {
                    buttons[index].count++;
                    //If the count is greater than the debounce value:
                    if( buttons[index].count > DEBOUNCE_NUM )
                    {
                        buttons[index].count = 0;
                        buttons[index].status = PRESSED;
                    }
                }
                else // if the button has been released:
                {
                    buttons[index].count = 0;
                    buttons[index].status = NOT_PRESSED;
                }
                break;
            case PRESSED:
                //Immediately go to the HELD state
                buttons[index].count = 0;
                buttons[index].status = HELD;
                break;
            case HELD:
                //If the button is not pushed:
                if( ( pressed_buttons & buttons[index].mask ) != buttons[index].mask )
                {
                    buttons[index].count = 0;
                    buttons[index].status = DEBOUNCE_R;
                }
                break;
            case DEBOUNCE_R:
                //If the button is pushed again, go back to HELD
                if( ( pressed_buttons & buttons[index].mask ) == buttons[index].mask )
                {
                    buttons[index].count = 0;
                    buttons[index].status = HELD;
                }
                else //if the button is not pushed:
                {
                    buttons[index].count++;
                    //If the count is greater than the debounce value, go to NOT_PRESSED.
                    if( buttons[index].count > DEBOUNCE_NUM )
                    {
                        buttons[index].count = 0;
                        buttons[index].status = NOT_PRESSED;
                    }
                }
                break;
            case ERR:
                break;
        }
    }           
}
