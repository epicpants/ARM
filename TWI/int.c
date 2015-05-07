
#include "int.h"

//Local constants:
#define POS_EDGE 0x60
#define PIT_COUNT 59903
#define MCK 47923200
#define US0_PID 1 << 6
//Might be missing pin 7 & 8 for USART0:
#define US0_PORTS ( ( 1 << 5 ) | ( 1 << 6 ) )
#define RESET_BIT ( 1 << 8 | 1 | 2 )
#define LDRB_BIT ( 1 << 6 )
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
__irq void TIMER2_ISR(void);

//Global vars:
uint32 interval = 0;
uint32 num_overflows;
uint32 num_counts;
uint8 tx_buf[BUF_SZ];
uint8 write_index = 0;
uint8 read_index = 0;
float time;
float distance;



__irq void PIT_ISR(void)
{
    uint8 tmp;
		uint8 index;
		uint8 integer;
		uint8 frac;
		uint32 divisor = 1000000000;
    char buf[50];
    
    //tmp = AT91C_BASE_PITC->PITC_PIVR;
    //interval++;
    
	  /*
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
	  */
	
	  if(interval == 0)
		{
				num_overflows = 0;
				START_TIMERS();
		}
		else if(interval == 1)
		{
				// Read Timer 2 status
				tmp = AT91C_BASE_TC2 -> TC_SR;
				
				// Check LDRB bit
				if( (tmp & LDRB_BIT) == LDRB_BIT )
				{
						num_counts = (num_overflows * COUNTER_MAX) + READ_TC2_REGISTER( RA );
				}
				else
				{
						STOP_TIMERS();
						num_counts = 0;
				}
				
		}
		else if(interval == 2)
		{
				if(num_counts != 0)
				{
						// Calculate distance
						distance = ((float)(num_counts * SOUND_VELOCITY))/MCK; // this equation looks different - probably why our measurements were off
				}
		}
		else if(interval == 3)
		{
				if(num_counts != 0)
				{
						// Print the distance as a formatted string
						integer = (uint8) distance; 																								// integer portion
						frac = (uint8)(((long long) num_counts * 10000) / MCK ) * SOUND_VELOCITY;		// fractional portion
						strcpy(buf, "\n\rDistance = ");
						index = 13;
						
					
						/*
						 * Convert integer portion to characters
						 */
						
						// Remove leading zeroes
						do
						{
								tmp = integer / divisor;
								divisor = divisor / 10;
						} while(tmp == 0);
						
						while(divisor > 1)
						{
								buf[index] = tmp | 0x30;
								index++;
								integer = integer - (tmp * divisor);
								divisor = divisor / 10;
								tmp = integer / divisor;
						}
						buf[index] = tmp | 0x30;
						
						index++;
						strcat(buf, ".");
						index++;
						
						/*
						 * Convert fraction portion to characters
						 */
						
						while(divisor > 1)
						{
								buf[index] = tmp | 0x30;
								index++;
								frac = frac - (tmp * divisor);
								divisor = divisor / 10;
								tmp = frac / divisor;
						}
						buf[index] = tmp | 0x30;
						
						index++;
						strcat(buf, "\n\r\0");
						index++;
				}
		}
		else if(interval == 4)
		{
				/*
				index = 0;
				while(buf[index] != 0)
				{
						tx_buf[read_index] = (uint8) buf[index];
						read_index++;
						read_index &= 0xFF;
						index++;
				}
				
				if(read_index != write_index)
				{
						tmp = tx_buf[write_index];
						write_index++;
						write_index &= 0xFF;
						uart_tx(&tmp, 1);
				}
				*/
				uart_tx(buf, strlen(buf));
		}
    
		interval++;
		
		if(interval >= 20)
		{
				interval = 0;
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

__irq void TIMER2_ISR(void)
{
		uint32 temp;
		temp = AT91C_BASE_TC2 -> TC_SR; // TC_CSR does not exist?
		num_overflows++;
		AT91C_BASE_AIC -> AIC_EOICR = 0;
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
	
		AT91C_BASE_AIC->AIC_SMR[7] = POS_EDGE; 							// I guess
    AT91C_BASE_AIC->AIC_SVR[7] = (uint32)TIMER2_ISR;		// Not sure about PID here
    AT91C_BASE_AIC->AIC_IECR = 1 << 7;
    
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
