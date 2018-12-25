#ifndef CAR_H
#define CAR_H

#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "PWM.h"
#include "Joystick.h"
#include "LED.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "Trimpot.h"
#include "LDR.h"
#include "Parameters.h"

int speed;
int mode;
int active;
int turnCount;

// Sensor values
uint32_t distance;
uint32_t LDR_Left_Value;
uint32_t LDR_Right_Value;
uint32_t LDR_Difference;

typedef enum {
	AUTO   = '#',
	MANUEL = '*',
}        Car_Mode;

void Car_Init(void);

void goForward(void);

void goBackward(void);

void turnRight(int rate);

void turnLeft(int rate);

void stopCar(void);

void updateSensorValues(void);

char toggleMode(void);

void startEscape(void);

void endEscape(void);

void checkObstacle(void);

void setFlags(int turnLeft, int turnRight, int forward, int backward);

#endif
