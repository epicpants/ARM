/******************************************************************************/
/* Button.h:                                                                  */
/* Jon Eftink & Tyler Ryan                                                    */
/******************************************************************************/

#ifndef TWI_H
#define TWI_H

#include "types.h"
#include ".\AT91SAM7SE-EK.h"

#define NO_ERRORS (0)
#define NACK_ERROR (1)
#define OVRE (1<<6)
#define START_BIT (1)
#define STOP_BIT (1<<1)
#define RXRDY (1<<1)
#define MREAD (1<<12)
#define NACK_BIT (1<<8)
#define TX_COMP (1)
#define	DS75 (0x48)
#define RES (1 << 5) // 10-bit resolution
#define TEMP_ADDR (0)
#define CONF_ADDR (0x01)

extern void INIT_TWI(void);
extern uint32 TWI_WRITE(uint32 device_addr, 
						uint32 internal_addr, 
						uint32 internal_size, 
						uint32 num_bytes, 
						uint32 * values);

uint32 TWI_READ(uint32 device_addr, 
				uint32 internal_addr, 
				uint32 internal_size, 
				uint32 num_bytes, 
				uint32 * values);


#endif
