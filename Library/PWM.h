#ifndef PWM_H
#define PWM_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"

// PWM_TypeDef struct.
typedef struct {
	volatile uint32_t IR;
	volatile uint32_t TCR;
	volatile uint32_t TC;
	volatile uint32_t PR;
	volatile uint32_t PC;
	volatile uint32_t MCR;
	volatile uint32_t MR0;
	volatile uint32_t MR1;
	volatile uint32_t MR2;
	volatile uint32_t MR3;
	volatile uint32_t CCR;
	volatile uint32_t CR0;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	uint32_t          RESERVED0;
	volatile uint32_t MR4;
	volatile uint32_t MR5;
	volatile uint32_t MR6;
	volatile uint32_t PCR;
	volatile uint32_t LER;
	uint32_t          RESERVED1[7];
	volatile uint32_t CTCR;
} PWM_TypeDef;

#define PWM0_BASE    0x40014000
#define PWM1_BASE    0x40018000

#define PWM0_PCONP    ((uint32_t) 1 << 5)
#define PWM1_PCONP    ((uint32_t) 1 << 6)

#define PWM1_PCONP    (1 << 6)

#define PWM0    ((PWM_TypeDef*) PWM0_BASE)
#define PWM1    ((PWM_TypeDef*) PWM1_BASE)

typedef enum {
	CHANNEL_1 = 1,
	CHANNEL_2 = 2,
	CHANNEL_3 = 3,
	CHANNEL_4 = 4,
	CHANNEL_5 = 5,
	CHANNEL_6 = 6
} PWM_Channel;

void PWM_Init(PWM_TypeDef *PWM, uint32_t *IOCON, uint32_t IOCON_FUNC, uint32_t PCONP_MASK, uint32_t channel);

void PWM_Cycle_Rate(PWM_TypeDef *PWM, uint32_t period_In_Cycles);

void PWM_Write(PWM_TypeDef *PWM, uint32_t channel, uint32_t T_ON);

#endif
