#include "PWM.h"

void PWM_Init() {
	//Change the function of the pin in here:
	
	//Turn on PWM 
	
	//Enable PWM output for corresponding pin.
	
	PWM_Timer_Reset();
	
	//Configure MR0 register for giving pulse every 20 ms.
	
	PWM_MR0_Reset();
	
	PWM_MR0_Enable();
	
	PWM_Timer_Enable();
	
	PWM_Write(0);
}

void PWM_Cycle_Rate(uint32_t period_In_Cycles) {
	//Write a formula that changes the MR0 register value for a given parameter.
	
	PWM_MR0_Enable();
}

void PWM_Write(uint32_t T_ON) {	
	if(T_ON > 100) {
		T_ON = 100;
	}
	
	//Write a formula to calculate the match register for P30 (P1_2) pin.
	//Store the value in T_ON variable (T_ON = ???)
	
	if (T_ON == PWM0->MR0) {
		T_ON++;
	}
	PWM0->MR1 = T_ON;
	
	PWM_MRL_Enable();
}
