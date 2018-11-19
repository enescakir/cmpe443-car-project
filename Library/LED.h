#ifndef LED_H
#define LED_H

#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "PWM.h"

// PWM1[2] used for LEDS
// IOCON address for PWM1[2]
// P1.20 (P7) in BOARD
#define IOCON_PWM1_2_ADDRESS 0x4002C0D0
#define IOCON_PWM1_2 *((volatile uint32_t *) IOCON_PWM1_2_ADDRESS)

// Front-left LED
#define LED1_PORT PORT0
#define LED1_MASK ((uint32_t) 1 << 25)

// Front-right LED
#define LED2_PORT PORT0
#define LED2_MASK ((uint32_t) 1 << 26)

// Back-right LED
#define LED3_PORT PORT1
#define LED3_MASK ((uint32_t) 1 << 30)

// Back-left LED
#define LED4_PORT PORT1
#define LED4_MASK ((uint32_t) 1 << 31)

typedef enum {
	OFF = 0,
	ON  = 1
} LED_Mode;

void LED_Init(void);

void LED_On(GPIO_TypeDef *PORT, uint32_t MASK);

void LED_Off(GPIO_TypeDef *PORT, uint32_t MASK);

void LED_Controller(int frontLeft, int frontRight, int backRight, int backLeft, int isBlink);

#endif
