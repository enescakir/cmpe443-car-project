#include "LED.h"

void LED_Init() {
	LED_Set(LED1_PORT, LED1_MASK, OUTPUT);
	LED_Set(LED2_PORT, LED2_MASK, OUTPUT);
	LED_Set(LED3_PORT, LED3_MASK, OUTPUT);
	LED_Set(LED4_PORT, LED4_MASK, OUTPUT);
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

void LED_Blink(GPIO_TypeDef *PORT, uint32_t MASK) {
	GPIO_PIN_Write(PORT, MASK, HIGH);
}

void LED_Handle(GPIO_TypeDef *PORT, uint32_t MASK, uint8_t value) {
	if (value == ON)
		LED_On(PORT, MASK);
	else if (value == OFF)
		LED_Off(PORT, MASK);
	else if (value == BLINK)
		LED_Blink(PORT, MASK);
}

void LED_Controller(int frontLeft, int frontRight, int backRight, int backLeft) {
	LED_Handle(LED1_PORT, LED1_MASK, frontLeft);
	LED_Handle(LED2_PORT, LED2_MASK, frontRight);
	LED_Handle(LED3_PORT, LED3_MASK, backRight);
	LED_Handle(LED4_PORT, LED4_MASK, backLeft);
}
