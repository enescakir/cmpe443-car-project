#include "Motor.h"

void Motor_Init() {
	Motor_PWM_Init();
	Motor_Direction_Init();
}

void Motor_PWM_Init() {
	PWM_Init(PWM0, IOCON_PWM0_6, 3, (1 << 5), CHANNEL_6)
}

void Motor_Direction_Init() {
	// Set motor GPIOs as OUTPUT
	GPIO_DIR_Write(IN1_PORT, IN1_MASK, OUTPUT);
	GPIO_DIR_Write(IN2_PORT, IN2_MASK, OUTPUT);
	GPIO_DIR_Write(IN3_PORT, IN3_MASK, OUTPUT);
	GPIO_DIR_Write(IN4_PORT, IN4_MASK, OUTPUT);

	Motor_Controller(STOP, STOP, 0);
}

void Motor_Write(uint32_t speed) {
	PWM_Write(PWM0, CHANNEL_6, speed)
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
	Motor_Write(speed);
}

