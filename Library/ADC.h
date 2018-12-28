#ifndef ADC_H
#define ADC_H

#include "LPC407x_8x_177x_8x.h"

#include "SystemStructures.h"

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t GDR;
	uint32_t          RESERVED0;
	volatile uint32_t INTEN;
	volatile uint32_t DR[8];
	volatile uint32_t STAT;
	volatile uint32_t TRM;
} ADC_TypeDef;

#define ADC_CLOCK_FREQUENCY 3000000

//Write the IOCON address of Analog Pin
#define ANALOG_PIN_IOCON_ADDRESS    0x4002C064
#define ANALOG_PIN_IOCON    *((volatile uint32_t*)(ANALOG_PIN_IOCON_ADDRESS))

//Write the CLKDIV of ADC for given ADC_CLOCK_FREQUENCY.
#define ADC_CLKDIV ((PERIPHERAL_CLOCK_FREQUENCY / ADC_CLOCK_FREQUENCY) -  1)

//Write the max value of ADC.
#define ADC_MAX_VALUE 0xFFF

#define ADC_BASE    0x40034000
#define ADC    ((ADC_TypeDef*) ADC_BASE)

void ADC_Init(volatile uint32_t *IOCON, uint32_t IOCON_FUNC);

void ADC_Start(void);

void ADC_Stop(void);

uint32_t ADC_Read(uint32_t channel, uint32_t range);

#endif
