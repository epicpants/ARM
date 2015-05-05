/******************************************************************************/
/* Button.h:                                                                  */
/* Jon Eftink & Tyler Ryan                                                    */
/******************************************************************************/


#ifndef SWITCH_H
#define SWITCH_H

#include "types.h"

#define LED_ON 2
#define LED_OFF 1

typedef enum
{
    NOT_PRESSED,
    DEBOUNCE,
    PRESSED,
    HELD,
    DEBOUNCE_R,
    ERR
} button_status;


typedef struct
{
    uint32 count;
    button_status status;
    uint32 mask;
} button;

enum
{
    RIGHT_SWITCH = 0,
    LEFT_SWITCH
};

#define NUM_BUTTONS 2

//Left pushbutton:  button[0].
//Right pushbutton: button[1]
extern button buttons[NUM_BUTTONS];


extern void IO_INIT( void );
extern unsigned int READ_SWITCHES( void );
extern void CONTROL_LED( unsigned int value);
void init_buttons( void );
void update_buttons( void );

#endif
