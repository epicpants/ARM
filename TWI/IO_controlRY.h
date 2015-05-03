#ifndef _IO_CONTROL_RY_H
#define _IO_CONTROL_RY_H

#define OUTPUT_ACTIVE 4
#define OUTPUT_INACTIVE 0

#define LED_ON 2
#define LED_OFF 1

#define LEFT_SW_PRESSED 2
#define RIGHT_SW_PRESSED 1

void IO_INIT(void);
unsigned int READ_SWITCHES(void);
void CONTROL_LED(unsigned int);
void DELAY_ASM(unsigned int);
void INPUT_INIT(void);
unsigned int READ_INPUT(void);

#endif

