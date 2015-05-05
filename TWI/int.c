
#include "int.h"

//Local constants:
#define POS_EDGE 0x60
#define PIT_COUNT 59903
#define US0_PID 1 << 6
//Might be missing pin 7 & 8 for USART0:
#define US0_PORTS ( ( 1 << 5 ) | ( 1 << 6 ) )
#define RESET_BIT ( 1 << 8 | 1 | 2 )
#define MODE_NORMAL ( 0 )
#define CHAR_LEN ( 3 << 6 )
#define NO_PARITY ( 4 << 9 )
#define CLK_DIV ( 312 ) //16x oversampling, baud rate = 9600
#define FRAC_PART ( 0 << 16 ) //No fractional part necessary for 16x oversampling at BR = 9600
#define TX_RDY_BIT ( 1 << 1 )
#define EN_RCVR ( 1 << 4 )
#define DIS_TX ( 1 << 7 )
#define EN_TX ( 1 << 6 )
#define BUF_SZ 256
#define ERR0R_CHAR 0x21  //'!' character



//Local Functions:
__irq void PIT_ISR(void);
__irq void USART0_TX_ISR(void);

//Global vars:
int interval = -1;
uint32 num_overflows;
uint8 tx_buf[BUF_SZ];
uint8 write_index = 0;
uint8 read_index = 0;



__irq void PIT_ISR(void)
{
    int tmp;
    uint8 buf[50];
    
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
            strcpy( buf, "Hello world\n" );
            uart_tx( buf, strlen( buf ) + 1 );
            break;   
    }
    
    
    
    
    
    AT91C_BASE_AIC->AIC_EOICR = 0;
    return;
}


__irq void USART0_TX_ISR(void)
{
    int tmp;
    uint8 character;
    
    tmp = AT91C_BASE_US0->US_IMR;
    if( ( AT91C_BASE_US0->US_CSR & 1) == 1 )
    {   //If received character:
        if( ( AT91C_BASE_US0->US_CSR & 0xE0 ) == 0xE0 )
        {   //If there was an error
            AT91C_BASE_US0->US_CR = 1 << 8;
            character = ERR0R_CHAR;
        }
        else
           character = AT91C_BASE_US0->US_RHR;
        
        tx_buf[write_index] = character;
        write_index++;
        write_index %= BUF_SZ;
    }
    else
    {
        if( write_index == read_index )
        {  //If there is nothing to read, disable transmitter:
            AT91C_BASE_US0->US_CR = DIS_TX;
        }
        else
        {   //Add a character to the THR:
            character = tx_buf[read_index];
            read_index++;
            read_index %= BUF_SZ;
            
            if( character > 127 )
            {   
                character = ERR0R_CHAR;
            }
            AT91C_BASE_US0->US_THR = character;
            
        }
    }
       
    AT91C_BASE_AIC->AIC_EOICR = 0;
    return;
}

//This function will initialize the Advanced Interrupt Controller.
void init_ISR( void )
{
    AT91C_BASE_AIC->AIC_SMR[1] = POS_EDGE;
    AT91C_BASE_AIC->AIC_SVR[1] = (uint32)PIT_ISR;
    AT91C_BASE_AIC->AIC_IECR = 1 << 1;
    AT91C_BASE_AIC->AIC_SMR[6] = POS_EDGE;
    AT91C_BASE_AIC->AIC_SVR[6] = (uint32)USART0_TX_ISR;
    AT91C_BASE_AIC->AIC_IECR = 1 << 6;
    
    return;    
}

//This timer will initialize the PIT timer.
void init_PITC( void )
{
    AT91C_BASE_PITC->PITC_PIMR = ( 0x03000000 | PIT_COUNT );
    return;
}

//This function will initialize USART 0. 
void init_USART0(void)
{
    
    //Enable peripheral clock for USART 0:
    AT91C_BASE_SYS->PMC_SCER = US0_PID; 
    
    //Disable Parallel I/0 for RXD0 and TXD0:
    AT91C_BASE_SYS->PIOA_PDR = US0_PORTS;
    
    //Select peripheral A device:
    AT91C_BASE_PIOA->PIO_ASR = US0_PORTS;
    
    //Reset USART0 status:
    AT91C_BASE_US0->US_CR = RESET_BIT;
    
    //Set up Mode:
    AT91C_BASE_US0->US_MR = MODE_NORMAL | CHAR_LEN | NO_PARITY;
    
    //Set baud rate:
    AT91C_BASE_US0->US_BRGR = FRAC_PART | CLK_DIV;
    
    //Enable interrupt for TxRDY & RxRDY:
    AT91C_BASE_US0->US_IER = TX_RDY_BIT | 1;
    
    //Enable receiver:
    AT91C_BASE_US0->US_CR = EN_RCVR;
    
    //Enable transmitter:
    AT91C_BASE_US0->US_CR = EN_TX;
    
    return;
}


void uart_tx( uint8 * data, uint8 num_bytes )
{
    int i;
    if( num_bytes > 0 )
    {
        for( i = 0; i < num_bytes; i++ )
        {
            tx_buf[write_index] = data[i];
            write_index++;
            write_index %= BUF_SZ;
        }
        
        AT91C_BASE_US0->US_CR = EN_TX;
        //AT91C_BASE_US0->US_THR = tx_buf[read_index];
        //read_index++;
        //read_index %= BUF_SZ;
    }
}
