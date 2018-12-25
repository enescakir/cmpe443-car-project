#include "Trimpot.h"


void Trimpot_Init() {
	ADC_Init(IOCON_TRIMPOD, IOCON_TRIMPOD_FUNC);
}

int Trimpot_Read_Data() {
	return ADC_Read(TRIMPOD_ADC_CHANNEL, TRIMPOD_RANGE);
}