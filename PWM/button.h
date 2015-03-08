
#ifndef SWITCH_H
#define SWITCH_H

#include "types.h"

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

//Left pushbutton:  button[0].
//Right pushbutton: button[1]
#define NUM_BUTTONS 2


extern void IO_INIT( void );
extern unsigned int READ_SWITCHES( void );
extern void CONTROL_LED( unsigned int value);
void init_buttons( void );
void update_buttons( void );

#endif
