#include "PWM.h"

void PWM_Init(PWM_TypeDef *PWM, uint32_t *IOCON, uint32_t IOCON_FUNC, uint32_t PCONP_MASK, uint32_t channel) {
	// Change the function of the pin in here:
	uint32_t value1 = IOCON;
	value1 &= ~7;
	value1 |= IOCON_FUNC;
	IOCON           = value1;

	// Power the PWM0 from PCONP
	PCONP |= PCONP_MASK;

	// Enable PWM output for corresponding pin.
	PWM->PCR |= 1 << (channel + 8); // 14 for channel 6

	// Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	PWM->TCR = 1 << 1;

	// Configure MR0 register for giving pulse every 20 ms.
	PWM->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000.0) * 20 * 1000;

	// Reset TC, when MR0 matches TC.
	PWM->MCR = 1 << 1;

	// Enable PWM Match 0 Latch.
	PWM->LER |= 1 << 0;

	// Enable Counter and PWM and Clear Reset on the PWM
	PWM->TCR &= ~(1 << 1);
	PWM->TCR |= 1 << 0;
	PWM->TCR |= 1 << 3;
}


void PWM_Cycle_Rate(PWM_TypeDef *PWM, uint32_t period_In_Cycles) {
	// Changes the MR0 register value for a given parameter
	PWM->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;

	// Enable PWM Match 0 Latch.
	PWM->LER |= 1 << 0;
}

void PWM_Write(PWM_TypeDef *PWM, uint32_t channel, uint32_t T_ON) {
	if (T_ON > 100) {
		T_ON = 100;
	}

	T_ON = PWM->MR0 * (T_ON / 100.0);

	if (T_ON == PWM->MR0) {
		T_ON++;
	}

	// Calculate the match register for channel
	if (channel == CHANNEL_1) PWM->MR1 = T_ON;
	else if (channel == CHANNEL_2) PWM->MR2 = T_ON;
	else if (channel == CHANNEL_3) PWM->MR3 = T_ON;
	else if (channel == CHANNEL_4) PWM->MR4 = T_ON;
	else if (channel == CHANNEL_5) PWM->MR5 = T_ON;
	else if (channel == CHANNEL_6) PWM->MR6 = T_ON;

	// Enable PWM Match Register Latch for channel
	PWM->LER |= 1 << channel;
}
