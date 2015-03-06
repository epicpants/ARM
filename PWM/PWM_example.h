#ifndef _PWM_example_H
#define _PWM_example_H

#include ".\AT91SAM7SE-EK.h"

// constant definitions

#define PWM0 (1<<0)
#define PWM1 (1<<1)
#define PWM2 (1<<2)
#define PWM3 (1<<3)
#define MCK_INPUT (0)
#define MCK_INPUT_2 (1)
#define MCK_INPUT_4 (2)
#define MCK_INPUT_8 (3)
#define MCK_INPUT_16 (4)
#define MCK_INPUT_32 (5)
#define MCK_INPUT_64 (6)
#define MCK_INPUT_128 (7)
#define MCK_INPUT_256 (8)
#define MCK_INPUT_512 (9)
#define MCK_INPUT_1024 (10)
#define CLKA (11)
#define CLKB (12)

// type declarations 

typedef unsigned int uint32;

// function declarations

extern void INIT_PWM(uint32 PWM_Num,uint32 Prescale, uint32 Polarity, uint32 Align);
extern uint32 SET_PWM_CLK(uint32 DIVIDER,uint32 CLK);
extern void ENABLE_PWM(uint32 PWM_NUM,uint32 PERIOD);
extern uint32 UPDATE_PWM(uint32 PWM_NUM,uint32 UPDATE_VAL);



#endif

