#include "PWM.h"

void PWM_Init() {
	// TODO: We will make generic method for all PWM inits
}

void PWM0_Cycle_Rate(uint32_t period_In_Cycles) {
	// Changes the MR0 register value for a given parameter
	PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;

	// Enable PWM Match 0 Latch.
	PWM0->LER |= 1 << 0;
}

void PWM0_Write(uint32_t T_ON) {
	if (T_ON > 100) {
		T_ON = 100;
	}

	T_ON = PWM0->MR0 * (T_ON / 100.0);

	if (T_ON == PWM0->MR0) {
		T_ON++;
	}

	// Calculate the match register for channel 6
	PWM0->MR6 = T_ON;

	// Enable PWM Match Register Latch for channel 6
	PWM0->LER |= 1 << 6;
}

void PWM1_Cycle_Rate(uint32_t period_In_Cycles) {
	// Changes the MR0 register value for a given parameter
	PWM1->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;

	// Enable PWM Match 0 Latch.
	PWM1->LER |= 1 << 0;
}

void PWM1_Write(uint32_t T_ON) {
	if (T_ON > 100) {
		T_ON = 100;
	}

	T_ON = PWM1->MR0 * (T_ON / 100.0);

	if (T_ON == PWM1->MR0) {
		T_ON++;
	}

	// Calculate the match register for channel 2
	PWM1->MR2 = T_ON;

	// Enable PWM Match Register Latch for channel 2
	PWM1->LER |= 1 << 2;
}

