#include "Motor.h"

void Motor_PWM_Init() {
    //Change the function of the pin in here:
	
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
	
    //Enable PWM output for corresponding pin.
		PWM0->PCR |= 1 << 9;  //ENABLE PWM0_1 OUTPUT
		//PWM0->PCR |= 1 << 10;  //ENABLE PWM0_2 OUTPUT
	
    PWM0->TCR = 1 << 1; // Reset
		
    //Configure MR0 register for giving pulse every 20 ms.
    PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;

    PWM0->MCR = 1 << 1;

    PWM0->LER |= 1 << 0;
		
		PWM0->TCR &= ~ (1 << 1) ;
    PWM0->TCR |= 1 << 0 ;
		PWM0->TCR |= 1 << 3;

    PWM_Write(0);
}

void Motor_Direction_Init() {
	GPIO_DIR_Write(IN1_PORT, IN1_MASK, OUTPUT);
	GPIO_DIR_Write(IN2_PORT, IN2_MASK, OUTPUT);
	GPIO_DIR_Write(IN3_PORT, IN3_MASK, OUTPUT);
	GPIO_DIR_Write(IN4_PORT, IN4_MASK, OUTPUT);
	
	Motor_Controller(0,0,0,0);
	
}

void Motor_Controller(int in1, int in2, int in3, int in4) {
	if(in1) GPIO_PIN_Write(IN1_PORT, IN1_MASK, HIGH); else GPIO_PIN_Write(IN1_PORT, IN1_MASK, LOW);
	if(in2) GPIO_PIN_Write(IN2_PORT, IN2_MASK, HIGH); else GPIO_PIN_Write(IN2_PORT, IN2_MASK, LOW);
	if(in3) GPIO_PIN_Write(IN3_PORT, IN3_MASK, HIGH); else GPIO_PIN_Write(IN3_PORT, IN3_MASK, LOW);
	if(in4) GPIO_PIN_Write(IN4_PORT, IN4_MASK, HIGH); else GPIO_PIN_Write(IN4_PORT, IN4_MASK, LOW);
}

