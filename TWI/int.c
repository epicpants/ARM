
#include "int.h"

//Local constants:
#define MODE_VAL_SYSC 0x60
#define PIT_COUNT 53653

//Local Functions:
__irq void PIT_ISR(void);

//Global vars:
int interval = -1;
uint32 num_overflows;



__irq void PIT_ISR(void)
{
    int tmp;
    
    tmp = AT91C_BASE_PITC->PITC_PIVR;
    interval++;
    
    switch( interval )
    {
        case 9:
            CONTROL_LED( LED_ON );
            break;
        case 19:
            CONTROL_LED( LED_OFF );
            interval = -1;
            break;   
    }
    
    
    
    
    
    AT91C_BASE_AIC->AIC_EOICR = 0;
    return;
}

//This function will initialize the Advanced Interrupt Controller.
void init_ISR( void )
{
    AT91C_BASE_AIC->AIC_SMR[1] = MODE_VAL_SYSC;
    AT91C_BASE_AIC->AIC_SVR[1] = (uint32)PIT_ISR;
    AT91C_BASE_AIC->AIC_IECR = 1 << 1;
    return;    
}

//This timer will initialize the PIT timer.
void init_PITC( void )
{
    AT91C_BASE_PITC->PITC_PIMR = ( 0x03000000 | PIT_COUNT );
    return;
}
