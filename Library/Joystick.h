#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "LPC407x_8x_177x_8x.h"

#include "GPIO.h"

#define JOYSTICK_PORT	PORT5

#define JOYSTICK_LEFT_MASK		((uint32_t) 1 << 0)
#define JOYSTICK_DOWN_MASK		((uint32_t) 1 << 1)
#define JOYSTICK_UP_MASK			((uint32_t) 1 << 2)
#define JOYSTICK_CENTER_MASK	((uint32_t) 1 << 3)
#define JOYSTICK_RIGHT_MASK		((uint32_t) 1 << 4)

void Joystick_Init(void);

uint8_t Joystick_Left_Pressed(void);
uint8_t Joystick_Down_Pressed(void);
uint8_t Joystick_Up_Pressed(void);
uint8_t Joystick_Center_Pressed(void);
uint8_t Joystick_Right_Pressed(void);

#endif
