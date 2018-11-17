#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "Timer.h"

// SPEEDOMETER
#define IOCON_SPEEDOMETER_ADDRESS 0x4002C05C
#define IOCON_SPEEDOMETER *((volatile uint32_t *) IOCON_SPEEDOMETER_ADDRESS)

extern uint32_t current;
extern uint32_t capture;
extern uint32_t previous;

void Speedometer_Init(void);

#endif
