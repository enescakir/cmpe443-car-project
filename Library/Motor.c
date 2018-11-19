#include "Motor.h"

void Motor_Init() {
	Motor_PWM_Init();
	Motor_Direction_Init();
}

void Motor_PWM_Init() {
	// Change the function of the pin in here:
	uint32_t value1 = IOCON_PWM0_6;
	value1 &= ~7;
	value1 |= 3;
	IOCON_PWM0_6 = value1;

	// Power the PWM0 from PCONP
	PCONP |= 1 << 5;

	// Enable PWM output for corresponding pin.
	PWM0->PCR |= 1 << 14;  //ENABLE PWM0_6 OUTPUT

	// Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	PWM0->TCR = 1 << 1;

	// Configure MR0 register for giving pulse every 20 ms.
	PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000.0) * 20 * 1000;

	// Reset TC, when MR0 matches TC.
	PWM0->MCR       = 1 << 1;

	// Enable PWM Match 0 Latch.
	PWM0->LER |= 1 << 0;

	// Enable Counter and PWM and Clear Reset on the PWM
	PWM0->TCR &= ~(1 << 1);
	PWM0->TCR |= 1 << 0;
	PWM0->TCR |= 1 << 3;

	PWM0_Write(0);
}

void Motor_Direction_Init() {
	// Set motor GPIOs as OUTPUT
	GPIO_DIR_Write(IN1_PORT, IN1_MASK, OUTPUT);
	GPIO_DIR_Write(IN2_PORT, IN2_MASK, OUTPUT);
	GPIO_DIR_Write(IN3_PORT, IN3_MASK, OUTPUT);
	GPIO_DIR_Write(IN4_PORT, IN4_MASK, OUTPUT);

	Motor_Controller(STOP, STOP, 0);
}

void Motor_Handle(int direction, GPIO_TypeDef *MOTOR1, uint32_t MASK1, GPIO_TypeDef *MOTOR2, uint32_t MASK2) {
	if (direction == FORWARD) {
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
	// Set direction of motors
	Motor_Handle(motor1, IN1_PORT, IN1_MASK, IN2_PORT, IN2_MASK);
	Motor_Handle(motor2, IN3_PORT, IN3_MASK, IN4_PORT, IN4_MASK);

	// Set speed of motots
	PWM0_Write(speed);
}

