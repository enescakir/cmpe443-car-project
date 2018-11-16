#ifndef LED_H
#define LED_H

#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"

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
	OFF   = 0,
	ON    = 1,
	BLINK = 2
} LED_Mode;

void LED_Init(void);

void LED_Set(GPIO_TypeDef *PORT, uint32_t MASK, uint8_t value);

void LED_On(GPIO_TypeDef *PORT, uint32_t MASK);

void LED_Off(GPIO_TypeDef *PORT, uint32_t MASK);

void LED_Blink(GPIO_TypeDef *PORT, uint32_t MASK);

void LED_Handle(GPIO_TypeDef *PORT, uint32_t MASK, uint8_t value);

void LED_Controller(int frontLeft, int frontRight, int backRight, int backLeft);

#endif
