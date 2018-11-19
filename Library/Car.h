#ifndef CAR_H
#define CAR_H

#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "PWM.h"
#include "Joystick.h"
#include "LED.h"
#include "Motor.h"
#include "Speedometer.h"
#include "Parameters.h"

extern int carSpeed;

void Car_Init(void);

void goForward(void);

void goBackward(void);

void turnRight(void);

void turnLeft(void);

void stopCar(void);

void setFlags(int turnLeft, int turnRight, int forward, int backward);

#endif
