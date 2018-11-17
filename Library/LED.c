#include "LED.h"

void LED_Init() {
	LED_Set(LED1_PORT, LED1_MASK, OUTPUT);
	LED_Set(LED2_PORT, LED2_MASK, OUTPUT);
	LED_Set(LED3_PORT, LED3_MASK, OUTPUT);
	LED_Set(LED4_PORT, LED4_MASK, OUTPUT);
	  //Change the function of the pin in here:
	
		//PORT1_20 P7 in BOARD
		uint32_t value = IOCON_PWM1_2;
		value &=~7;
		value |=2;
		IOCON_PWM1_2= value;

		// POWER THE PWM0 FROM PCONP 
		// base address for PCONP = 0x400FC0C4
		PCONP |= 1<<6;
	
    //Enable PWM output for corresponding pin.
		PWM1->PCR |= 1 << 9;  //ENABLE PWM0_1 OUTPUT
		PWM1->PCR |= 1 << 10;  //ENABLE PWM0_2 OUTPUT
	
    PWM1->TCR = 1 << 1; // Reset
		
    //Configure MR0 register for giving pulse every 20 ms.
    PWM1->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;

    PWM1->MCR = 1 << 1;

    PWM1->LER |= 1 << 0;
		
		PWM1->TCR &= ~ (1 << 1) ;
    PWM1->TCR |= 1 << 0 ;
		PWM1->TCR |= 1 << 3;

    PWM1_Write(0);
}

void LED_Set(GPIO_TypeDef *PORT, uint32_t MASK, uint8_t value) {
	GPIO_DIR_Write(PORT, MASK, value);
}

void LED_On(GPIO_TypeDef *PORT, uint32_t MASK) {
	GPIO_PIN_Write(PORT, MASK, HIGH);
}

void LED_Off(GPIO_TypeDef *PORT, uint32_t MASK) {
	GPIO_PIN_Write(PORT, MASK, LOW);
}


void LED_Handle(GPIO_TypeDef *PORT, uint32_t MASK, uint8_t value) { 
	if (value == ON)
		LED_On(PORT, MASK);
	else if (value == OFF)
		LED_Off(PORT, MASK);
}

void LED_Controller(int frontLeft, int frontRight, int backRight, int backLeft, int isBlink) {
	LED_Handle(LED2_PORT, LED2_MASK, frontLeft);
	LED_Handle(LED1_PORT, LED1_MASK, frontRight);
	LED_Handle(LED4_PORT, LED4_MASK, backRight);
	LED_Handle(LED3_PORT, LED3_MASK, backLeft);
	
	if(frontLeft + frontRight + backRight + backLeft == 0) 	PWM1_Write(0);
	else 	PWM1_Write(60);

	if(isBlink) PWM1_Cycle_Rate(500);
	else 	PWM1_Cycle_Rate(20);

}
