#include "Hidden.h"

void PWM_Timer_Reset() {
	//Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	LPC_PWM0->TCR = 1 << 1;
}

void PWM_MR0_Reset() {
	//Reset TC, when MR0 matches TC.
	LPC_PWM0->MCR = 1 << 1;
}

void PWM_MR0_Enable() {
	//Enable PWM Match 0 Latch.
	LPC_PWM0->LER |= 1 << 0;
}

void PWM_MRL_Enable() {
	//Enable PWM Match Register Latch.
	LPC_PWM0->LER |= 1 << 1;
}

void PWM_Timer_Enable() {
	//Enable Counter and PWM and Clear Reset on the PWM
	LPC_PWM0->TCR = (1 << 0 | 1 << 3);
}
