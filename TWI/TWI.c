/******************************************************************************/
/* TWI.c:                                                                		  */
/* Jon Eftink & Tyler Ryan                                                    */
/******************************************************************************/

#include "TWI.h"
#include <AT91SAM7SE512.H>

/*
 * Perform a read from a slave
 */
uint32 TWI_READ(uint32 device_addr, uint32 internal_addr, uint32 internal_size, uint32 num_bytes, uint32 * values)
{
	uint32 temp, index, return_value;
	
	temp = (device_addr << 16) | (internal_size << 8) | (MREAD);
	AT91C_BASE_TWI -> TWI_MMR = temp;
	AT91C_BASE_TWI -> TWI_IADR = internal_addr;
	
	// To start a TWI read transmission, write a 1 to START bit
	// The STOP bit needs to be written BEFORE the last byte is received

	temp = START_BIT; 								
	if(num_bytes == 1)
	{
		temp |= STOP_BIT; 					
	}

	AT91C_BASE_TWI -> TWI_CR = temp;
	index = 0;
	while(num_bytes != 0)
	{
		do
		{
			temp = AT91C_BASE_TWI -> TWI_SR;
		} while( ( (temp & RXRDY) == 0 ) && ( (temp & NACK_BIT) == 0 ) && ( (temp & OVRE) == 0) );

		if( (temp & NACK_BIT) != 0 || ( (temp & OVRE) != 0 ) )
		{
			return_value = NACK_ERROR;
			break;
		}

		temp = AT91C_BASE_TWI -> TWI_RHR;
		values[index] = temp;
		index++;
		num_bytes--;

		if(num_bytes == 1)
		{
			AT91C_BASE_TWI -> TWI_CR = STOP_BIT;
		}

		return_value = NO_ERRORS;
	}

	do
	{
		temp = AT91C_BASE_TWI -> TWI_SR;
	} while( (temp & TX_COMP) == 0 );

	return return_value;
}
