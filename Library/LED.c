#include "LED.h"

void LED_Init() {
	// Set LED GPIOs as OUTPUT
	GPIO_DIR_Write(LED1_PORT, LED1_MASK, OUTPUT);
	GPIO_DIR_Write(LED2_PORT, LED2_MASK, OUTPUT);
	GPIO_DIR_Write(LED3_PORT, LED3_MASK, OUTPUT);
	GPIO_DIR_Write(LED4_PORT, LED4_MASK, OUTPUT);

	// Change the function of the pin in here:
	uint32_t value = IOCON_PWM1_2;
	value &= ~7;
	value |= 2;
	IOCON_PWM1_2 = value;

	// Power the PWM1 from PCONP
	PCONP |= 1 << 6;

	// Enable PWM output for corresponding pin.
	PWM1->PCR |= 1 << 10;  //ENABLE PWM1_2 OUTPUT

	// Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	PWM1->TCR = 1 << 1;

	// Configure MR0 register for giving pulse every 20 ms.
	PWM1->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;

	// Reset TC, when MR0 matches TC.
	PWM1->MCR = 1 << 1;

	// Enable PWM Match 0 Latch.
	PWM1->LER |= 1 << 0;

	// Enable Counter and PWM and Clear Reset on the PWM
	PWM1->TCR &= ~(1 << 1);
	PWM1->TCR |= 1 << 0;
	PWM1->TCR |= 1 << 3;

	PWM1_Write(0);
}

void LED_On(GPIO_TypeDef *PORT, uint32_t MASK) {
	GPIO_PIN_Write(PORT, MASK, HIGH);
}

void LED_Off(GPIO_TypeDef *PORT, uint32_t MASK) {
	GPIO_PIN_Write(PORT, MASK, LOW);
}

void LED_Controller(int frontLeft, int frontRight, int backRight, int backLeft, int isBlink) {
	// Set ON or OFF state of LEDs
	if (frontLeft) LED_On(LED2_PORT, LED2_MASK); else LED_Off(LED2_PORT, LED2_MASK);
	if (frontRight) LED_On(LED1_PORT, LED1_MASK); else LED_Off(LED1_PORT, LED1_MASK);
	if (backRight) LED_On(LED4_PORT, LED4_MASK); else LED_Off(LED4_PORT, LED4_MASK);
	if (backLeft) LED_On(LED3_PORT, LED3_MASK); else LED_Off(LED3_PORT, LED3_MASK);

	// If all LEDs are OFF, set duty cycle to 0
	if (frontLeft + frontRight + backRight + backLeft == 0) PWM1_Write(0);
	else PWM1_Write(60);

	// If they are blink, change cycle rate for PMW1
	if (isBlink) PWM1_Cycle_Rate(500);
	else PWM1_Cycle_Rate(20);

}
