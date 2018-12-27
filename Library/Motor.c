#include "Motor.h"

void Motor_Init() {
	Motor_PWM_Init();
	Motor_Direction_Init();
}

void Motor_PWM_Init() {
	PWM_Init(PWM0, &IOCON_LEFT_MOTOR, IOCON_LEFT_MOTOR_PWM_FUNC, PWM0_PCONP, LEFT_MOTOR_PWM_CHANNEL);
	PWM_Init(PWM0, &IOCON_RIGHT_MOTOR, IOCON_RIGHT_MOTOR_PWM_FUNC, PWM0_PCONP, RIGHT_MOTOR_PWM_CHANNEL);
}

void Motor_Direction_Init() {
	// Set motor GPIOs as OUTPUT
	GPIO_DIR_Write(IN1_PORT, IN1_MASK, OUTPUT);
	GPIO_DIR_Write(IN2_PORT, IN2_MASK, OUTPUT);
	GPIO_DIR_Write(IN3_PORT, IN3_MASK, OUTPUT);
	GPIO_DIR_Write(IN4_PORT, IN4_MASK, OUTPUT);

	Motor_Controller(STOP, STOP, 0);
}

void Motor_Write(uint32_t speed, uint32_t channel) {
	PWM_Write(PWM0, channel, abs(speed));
}

void Motor_Handle(int percentage, GPIO_TypeDef *MOTOR1, uint32_t MASK1, GPIO_TypeDef *MOTOR2, uint32_t MASK2) {
	if (percentage > 0) {
		GPIO_PIN_Write(MOTOR1, MASK1, LOW);
		GPIO_PIN_Write(MOTOR2, MASK2, HIGH);
	} else if (percentage < 0) {
		GPIO_PIN_Write(MOTOR1, MASK1, HIGH);
		GPIO_PIN_Write(MOTOR2, MASK2, LOW);
	} else if (percentage == 0) {
		GPIO_PIN_Write(MOTOR1, MASK1, LOW);
		GPIO_PIN_Write(MOTOR2, MASK2, LOW);
	}
}

void Motor_Controller(int leftPercentage, int rightPercentage, int speed) {
	// Set direction of motors
	Motor_Handle(leftPercentage, IN1_PORT, IN1_MASK, IN2_PORT, IN2_MASK);
	Motor_Handle(rightPercentage, IN3_PORT, IN3_MASK, IN4_PORT, IN4_MASK);

	// Set speed of motors
	Motor_Write(leftPercentage * speed / 100, LEFT_MOTOR_PWM_CHANNEL);
	Motor_Write(rightPercentage * speed / 100, RIGHT_MOTOR_PWM_CHANNEL);
}

