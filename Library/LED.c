#include "LED.h"

void LED_Init() {
	// Set LED GPIOs as OUTPUT
	GPIO_DIR_Write(LED1_PORT, LED1_MASK, OUTPUT);
	GPIO_DIR_Write(LED2_PORT, LED2_MASK, OUTPUT);
	GPIO_DIR_Write(LED3_PORT, LED3_MASK, OUTPUT);
	GPIO_DIR_Write(LED4_PORT, LED4_MASK, OUTPUT);

	PWM_Init(PWM1, &IOCON_LED_PWM, IOCON_LED_PWM_FUNC, PWM1_PCONP, LED_PWM_CHANNEL);
}

void LED_On(GPIO_TypeDef *PORT, uint32_t MASK) {
	GPIO_PIN_Write(PORT, MASK, HIGH);
}

void LED_Off(GPIO_TypeDef *PORT, uint32_t MASK) {
	GPIO_PIN_Write(PORT, MASK, LOW);
}

void LED_Write(uint32_t T_ON) {
	PWM_Write(PWM1, CHANNEL_2, T_ON);
}

void LED_Controller(int frontLeft, int frontRight, int backRight, int backLeft, int isBlink) {
	// Set ON or OFF state of LEDs
	if (frontLeft) LED_On(LED1_PORT, LED1_MASK); else LED_Off(LED1_PORT, LED1_MASK);
	if (frontRight) LED_On(LED2_PORT, LED2_MASK); else LED_Off(LED2_PORT, LED2_MASK);
	if (backRight) LED_On(LED3_PORT, LED3_MASK); else LED_Off(LED3_PORT, LED3_MASK);
	if (backLeft) LED_On(LED4_PORT, LED4_MASK); else LED_Off(LED4_PORT, LED4_MASK);

	// If all LEDs are OFF, set duty cycle to 0
	if (frontLeft + frontRight + backRight + backLeft == 0) LED_Write(0);
	else LED_Write(60);

	// If they are blink, change cycle rate for PMW1
	if (isBlink) PWM_Cycle_Rate(PWM1, 500);
	else PWM_Cycle_Rate(PWM1, 20);
}
