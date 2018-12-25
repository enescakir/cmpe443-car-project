#ifndef TRIMPOT_H
#define TRIMPOT_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "ADC.h"

// PWM0[6] used for motors
// IOCON address for PWM0[6]
// P1.11 (P25) in BOARD
// TODO: IOCON_TRIMPOT_ADDRESS define
#define IOCON_LEFT_LDR_ADDRESS 0x4002C0AC
#define IOCON_LEFT_LDR *((volatile uint32_t *) IOCON_LEFT_LDR_ADDRESS)
#define IOCON_LEFT_LDR_FUNC 0x4002C0AC
#define LEFT_LDR_ADC_CHANNEL 1

#define RIGHT_LDR_ADDRESS 0x4002C0AC
#define RIGHT_LDR *((volatile uint32_t *) RIGHT_LDR_ADDRESS)
#define RIGHT_LDR_FUNC 0x4002C0AC
#define RIGHT_LDR_ADC_CHANNEL 2


#define LDR_RANGE 1000

void LDR_Init(void);

int LDR_Left_Read_Data(void);

int LDR_Right_Read_Data(void);

#endif
