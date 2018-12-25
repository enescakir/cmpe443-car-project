#ifndef TRIMPOT_H
#define TRIMPOT_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "ADC.h"

// ADC0[0] used for Trim Pot
// P0.23 (P15)
#define IOCON_TRIMPOT_ADDRESS 0x4002C05C
#define IOCON_TRIMPOT *((volatile uint32_t *) IOCON_TRIMPOT_ADDRESS)
#define IOCON_TRIMPOT_FUNC 1

#define TRIMPOT_ADC_CHANNEL 0
#define TRIMPOT_RANGE 100

void Trimpot_Init(void);

int Trimpot_Read_Data(void);

#endif
