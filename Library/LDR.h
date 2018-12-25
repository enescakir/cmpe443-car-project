#ifndef TRIMPOT_H
#define TRIMPOT_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "ADC.h"

// IOCON address for ADC0[3]
// P0.26 (P18)
#define IOCON_LEFT_LDR_ADDRESS 0x4002C068
#define IOCON_LEFT_LDR *((volatile uint32_t *) IOCON_LEFT_LDR_ADDRESS)
#define IOCON_LEFT_LDR_FUNC 1
#define LEFT_LDR_ADC_CHANNEL 3

// IOCON address for ADC0[2]
// P0.25 (P17)
#define RIGHT_LDR_ADDRESS 0x4002C064
#define RIGHT_LDR *((volatile uint32_t *) RIGHT_LDR_ADDRESS)
#define RIGHT_LDR_FUNC 1
#define RIGHT_LDR_ADC_CHANNEL 2


#define LDR_RANGE 1000

void LDR_Init(void);

int LDR_Left_Read_Data(void);

int LDR_Right_Read_Data(void);

#endif
