#include "Speedometer.h"

uint32_t current  = 0;
uint32_t capture  = 0;
uint32_t previous = 0;

void Speedometer_Init() {
	// Change the function of the pin in here
	uint32_t value = IOCON_SPEEDOMETER;
	value &= ~7;
	value |= 3;
	IOCON_SPEEDOMETER = value;

	PCONP |= 1 << 23; // Open Timer

	int32_t value1 = TIMER3->CTCR;
	value1 &= ~(1 << 0); // Timer mode
	value1 &= ~(1 << 1); // Timer mode
	TIMER3->CTCR = value1;

	int32_t value2 = TIMER3->TCR;
	value2 &= ~(1 << 0); // Disable
	value2 |= (1 << 1); // Reset
	TIMER3->TCR = value2;

	TIMER3->PR = (PERIPHERAL_CLOCK_FREQUENCY / 1000000.0) - 1;
	TIMER3->CCR |= (1 << 0 | 1 << 1); // Capture rising and falling edges

	int32_t value3 = TIMER3->TCR;
	value3 &= ~(1 << 1); // Remove reset
	value3 |= (1 << 0); // Enable Timer3
	TIMER3->TCR    = value3;
}

