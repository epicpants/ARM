
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
    uint32 i;
    
    pressed_buttons = READ_SWITCHES();
    
    for( i = 0; i < NUM_BUTTONS; i++ );
    {
        if( buttons[i].mask == 0 )
            buttons[i].status = ERR;
        
        switch( buttons[i].status )
        {
            case NOT_PRESSED:
                //If the button is pressed:
                if( ( pressed_buttons & buttons[i].mask ) == buttons[i].mask )
                {
                    buttons[i].count = 0;
                    buttons[i].status = DEBOUNCE;
                }
                break;
            case DEBOUNCE:
                //If the button is pressed:
                if( ( pressed_buttons & buttons[i].mask ) == buttons[i].mask )
                {
                    buttons[i].count++;
                    //If the count is greater than the debounce value:
                    if( buttons[i].count > DEBOUNCE_NUM )
                    {
                        buttons[i].count = 0;
                        buttons[i].status = PRESSED;
                    }
                }
                else // if the button has been released:
                {
                    buttons[i].count = 0;
                    buttons[i].status = NOT_PRESSED;
                }
                break;
            case PRESSED:
                //Immediately go to the HELD state
                buttons[i].count = 0;
                buttons[i].status = HELD;
                break;
            case HELD:
                //If the button is not pushed:
                if( ( pressed_buttons & buttons[i].mask ) != buttons[i].mask )
                {
                    buttons[i].count = 0;
                    buttons[i].status = DEBOUNCE_R;
                }
                break;
            case DEBOUNCE_R:
                //If the button is pushed again, go back to HELD
                if( ( pressed_buttons & buttons[i].mask ) == buttons[i].mask )
                {
                    buttons[i].count = 0;
                    buttons[i].status = HELD;
                }
                else //if the button is not pushed:
                {
                    buttons[i].count++;
                    //If the count is greater than the debounce value, go to NOT_PRESSED.
                    if( buttons[i].count > DEBOUNCE_NUM )
                    {
                        buttons[i].count = 0;
                        buttons[i].status = NOT_PRESSED;
                    }
                }
                break;
            case ERR:
                break;
        }
    }           
}
