#ifndef TRIMPOT_H
#define TRIMPOT_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "ADC.h"

// PWM0[6] used for motors
// IOCON address for PWM0[6]
// P1.11 (P25) in BOARD
// TODO: IOCON_TRIMPOT_ADDRESS define
#define IOCON_TRIMPOT_ADDRESS 0x4002C0AC
#define IOCON_TRIMPOT *((volatile uint32_t *) IOCON_TRIMPOT_ADDRESS)
#define IOCON_TRIMPOT_FUNC 0x4002C0AC

#define TRIMPOT_ADC_CHANNEL 0
#define TRIMPOT_RANGE 100

void Trimpot_Init(void);

int Trimpot_Read_Data(void);

#endif
