#include "Speedometer.h"

uint32_t current = 0;
uint32_t capture = 0;
uint32_t previous = 0;

void Speedometer_Init() {
	// SPEEDOMETER is at PORT0_23 = P30 in BOARD
	uint32_t value = IOCON_SPEEDOMETER;
	value &= ~7;
	value |= 3;
	IOCON_SPEEDOMETER = value;

	PCONP |= 1 << 23;//OPEN TIMER
	
	int32_t value1 = TIMER3->CTCR;
	value1 &= ~(1<<0); //timer mode
	value1 &= ~(1<<1); //timer mode
	TIMER3->CTCR = value1;
	
	int32_t value2 = TIMER3->TCR;
	value2 &= ~(1<<0); //DISABLE
	value2 |= (1<<1); //RESET
	TIMER3->TCR = value2;

	TIMER3->PR = (PERIPHERAL_CLOCK_FREQUENCY / 1000000.0) - 1;
	TIMER3->CCR |= (1<<0 | 1<<1); //CAPTURE RISING AND FALLING EDGE
	
	int32_t value3 = TIMER3->TCR;
	value3 &= ~(1<<1); //REMOVE RESET
	value3 |= (1<<0); //ENABLE TIMER3
	TIMER3->TCR = value3;

}

