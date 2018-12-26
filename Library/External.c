#include "External.h"

void External_Init() {
	//Change the functionality of the push button as EINT0
	uint32_t value = EXT->EXTINT;
	value &= ~7;
	value |= (1 << 0);
	EXT->EXTINT    = value;

	//Change the External interrupt mode as Edge Sensitive
	EXT->EXTMODE |= (1 << 0);

	//Enable interrupt for EINT0_IRQn.
	NVIC_EnableIRQ(EINT0_IRQn);
}

void EINT0_IRQHandler() {
	// Clear interrupt for EINT0
	EXT->EXTINT &= ~(1 << 0);
	toggleMode();
}
