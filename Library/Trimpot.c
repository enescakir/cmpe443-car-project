#include "Trimpot.h"


void Trimpot_Init() {
	ADC_Init(&IOCON_TRIMPOT, IOCON_TRIMPOT_FUNC);
}

int Trimpot_Read_Data() {
	return ADC_Read(TRIMPOT_ADC_CHANNEL, TRIMPOT_RANGE);
}
