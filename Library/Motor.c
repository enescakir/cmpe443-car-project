#include "Motor.h"

void Motor_Init() {
	Motor_PWM_Init();
	Motor_Direction_Init();
}

void Motor_PWM_Init() {
    //Change the function of the pin in here:
	
		// PORT1_2 P30 in BOARD
		// uint32_t value = IOCON_PWM0_1;
		// value &=~7;
		// value |=3;
		// IOCON_PWM0_1= value;

		//PORT1_3 P29 in BOARD
		uint32_t value1 = IOCON_PWM0_6;
		value1 &= ~7;
		value1 |= 3;
		IOCON_PWM0_6 = value1;
				
		// POWER THE PWM0 FROM PCONP 
		// base address for PCONP = 0x400FC0C4
		PCONP |= 1 << 5;
	
    //Enable PWM output for corresponding pin.
		// PWM0->PCR |= 1 << 9;  //ENABLE PWM0_1 OUTPUT
		// PWM0->PCR |= 1 << 10;  //ENABLE PWM0_2 OUTPUT
		PWM0->PCR |= 1 << 14;  //ENABLE PWM0_6 OUTPUT

    PWM0->TCR = 1 << 1; // Reset
		
    //Configure MR0 register for giving pulse every 20 ms.
    PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000.0) * 20 * 1000;

    PWM0->MCR = 1 << 1;

    PWM0->LER |= 1 << 0;
		
		int value2 = PWM0->TCR;
		value2 &= ~ (1 << 1) ;
    value2 |= 1 << 0 ;
		value2 |= 1 << 3;
		PWM0->TCR = value2;
		
    PWM0_Write(0);
}

void Motor_Direction_Init() {
	GPIO_DIR_Write(IN1_PORT, IN1_MASK, OUTPUT);
	GPIO_DIR_Write(IN2_PORT, IN2_MASK, OUTPUT);
	GPIO_DIR_Write(IN3_PORT, IN3_MASK, OUTPUT);
	GPIO_DIR_Write(IN4_PORT, IN4_MASK, OUTPUT);
	
	Motor_Controller(STOP, STOP,0);	
}

void Motor_Handle (int direction, GPIO_TypeDef *MOTOR1, uint32_t MASK1, GPIO_TypeDef *MOTOR2, uint32_t MASK2) {
	if(direction == FORWARD){
		GPIO_PIN_Write(MOTOR1, MASK1, HIGH);
		GPIO_PIN_Write(MOTOR2, MASK2, LOW);
	} else if (direction == BACKWARD) {
		GPIO_PIN_Write(MOTOR1, MASK1, LOW);
		GPIO_PIN_Write(MOTOR2, MASK2, HIGH);
	} else if (direction == STOP) {
		GPIO_PIN_Write(MOTOR1, MASK1, LOW);
		GPIO_PIN_Write(MOTOR2, MASK2, LOW);
	}

}

void Motor_Controller(int motor1, int motor2, int speed) {
	Motor_Handle(motor1, IN1_PORT, IN1_MASK, IN2_PORT, IN2_MASK);
	Motor_Handle(motor2, IN3_PORT, IN3_MASK, IN4_PORT, IN4_MASK);
	
	PWM0_Write(speed);
}

