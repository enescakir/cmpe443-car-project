#include "PWM.h"

void PWM_Init() {
    //Change the function of the pin in here:

    //Turn on PWM

    //Enable PWM output for corresponding pin.

    PWM0->TCR = 1 << 1;

    //Configure MR0 register for giving pulse every 20 ms.
    PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;

    PWM0->MCR = 1 << 1;

    PWM0->LER |= 1 << 0;

    PWM0->TCR = (1 << 0 | 1 << 3);

    PWM_Write(0);
}

void PWM_Cycle_Rate(uint32_t period_In_Cycles) {
    //Write a formula that changes the MR0 register value for a given parameter.
    PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;

    PWM0->LER |= 1 << 0;
}

void PWM_Write(uint32_t T_ON) {
    if (T_ON > 100) {
        T_ON = 100;
    }

    //Write a formula to calculate the match register for P30 (P1_2) pin.
    //Store the value in T_ON variable (T_ON = ???)

    if (T_ON == PWM0->MR0) {
        T_ON++;
    }
    PWM0->MR1 = T_ON;

    PWM0->LER |= 1 << 1;
}
