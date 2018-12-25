#include "LDR.h"


void LDR_Init() {
	ADC_Init(IOCON_LEFT_LDR, IOCON_LEFT_LDR_FUNC);
	ADC_Init(IOCON_RIGHT_LDR, IOCON_RIGHT_LDR_FUNC);
}

int LDR_Left_Read_Data() {
	return ADC_Read(LEFT_LDR_ADC_CHANNEL, LDR_RANGE);
}

int LDR_Right_Read_Data() {
	return ADC_Read(RIGHT_LDR_ADC_CHANNEL, LDR_RANGE);
}