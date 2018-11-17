#include "PWM.h"


void PWM_Init() {
/*    //Change the function of the pin in here:
	
		//PORT1_2 P30 in BOARD
		uint32_t value = IOCON_PWM0_1;
		value &=~7;
		value |=3;
		IOCON_PWM0_1= value;

		//PORT1_3 P29 in BOARD
		uint32_t value1 = IOCON_PWM0_2;
		value1 &=~7;
		value1 |=3;
		IOCON_PWM0_2= value1;
				
		// POWER THE PWM0 FROM PCONP 
		// base address for PCONP = 0x400FC0C4
		PCONP |= 1<<5;
		PCONP |= 1<<6;
	
    //Enable PWM output for corresponding pin.
		PWM0 -> PCR |= 1 << 9;  //ENABLE PWM0_1 OUTPUT
		PWM0 -> PCR |= 1 << 10;  //ENABLE PWM0_2 OUTPUT
	
    PWM0->TCR = 1 << 1;
		
    //Configure MR0 register for giving pulse every 20 ms.
    PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;

    PWM0->MCR = 1 << 1;

    PWM0->LER |= 1 << 0;

    PWM0->TCR = (1 << 0 | 1 << 3);

    PWM_Write(0);*/
}

void PWM0_Cycle_Rate(uint32_t period_In_Cycles) {
    //Write a formula that changes the MR0 register value for a given parameter.
    PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;

    PWM0->LER |= 1 << 0;
}

void PWM0_Write(uint32_t T_ON) {
    if (T_ON > 100) {
        T_ON = 100;
    }

		T_ON = PWM0->MR0 *(T_ON / 100.0);
				
    if (T_ON == PWM0->MR0) {
        T_ON++;
    }
    // PWM0->MR1 = T_ON;
		// PWM0->MR2 = T_ON;
		PWM0->MR6 = T_ON;

    // PWM0->LER |= 1 << 1;
		// PWM0->LER |= 1 << 2;
		PWM0->LER |= 1 << 6;

}
void PWM1_Cycle_Rate(uint32_t period_In_Cycles) {
    //Write a formula that changes the MR0 register value for a given parameter.
    PWM1->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;

    PWM1->LER |= 1 << 0;
}

void PWM1_Write(uint32_t T_ON) {
    if (T_ON > 100) {
        T_ON = 100;
    }

		T_ON = PWM1->MR0 *(T_ON / 100.0);
				
    if (T_ON == PWM1->MR0) {
        T_ON++;
    }
    PWM1->MR1 = T_ON;
		PWM1->MR2 = T_ON;

    PWM1->LER |= 1 << 1;
		PWM1->LER |= 1 << 2;

}

