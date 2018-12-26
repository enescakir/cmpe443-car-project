#include "ADC.h"

uint32_t ADC_Last               = 0;
uint8_t  ADC_New_Data_Available = 0;

void ADC_Init(volatile uint32_t *IOCON, uint32_t IOCON_FUNC) {

	uint32_t value = *IOCON;
	value &= ~7;
	value |= IOCON_FUNC;

	//Change the function value of pin to ADC.
//	ANALOG_PIN_IOCON |= 0x01;

	//Change the mode value of pin to mode which should be selected if Analog mode is used.
	value &= ~(1 << 3 | 1 << 4);

	//Change Analog/Digital mode of pin to Analog.
	value &= ~(1 << 7);

	*IOCON = value;
	
	//Turn on ADC.
	PCONP |= (1 << 12);

	//Set the CLKDIV and make the A/D converter operational without Burst mode.
	ADC->CR = (0 << 0)
			  | (ADC_CLKDIV << 8)
			  | (0 << 16)
			  | (1 << 21)
			  | (0 << 24);
}

void ADC_Start() {
	//Write a code for starting A/D conversion
	ADC->CR |= 1 << 24;
}

void ADC_Stop() {
	//Write a code for stopping A/D conversion
	ADC->CR &= ~(1 << 24);
}

uint32_t ADC_Read(uint32_t channel, uint32_t range) {
	uint32_t data;

	//Configure CR SEL bits for sampled and converting corresponding pin
	LPC_ADC->CR &= ~0xFF;
	LPC_ADC->CR |= 1 << channel;

	ADC_Start();

	//Wait until A/D conversion completed
	while ((ADC->STAT & (1 << channel)) == 0);

	//Convert the data RESULT to 0 - range and return the ADC data
	data = LPC_ADC->DR[channel];
	data = (((data >> 4) & 0xFFF) * range) / ADC_MAX_VALUE;

	ADC_Stop();

	return data;
}

