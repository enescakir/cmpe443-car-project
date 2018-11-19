#include "Car.h"

int TURN_LEFT_FLAG  = 0;
int TURN_RIGHT_FLAG = 0;
int FORWARD_FLAG    = 0;
int BACKWARD_FLAG   = 0;

void Car_Init() {
	Joystick_Init();
	Motor_Init();
	LED_Init();
	Speedometer_Init();
};

void goForward() {
	LED_Controller(ON, ON, OFF, OFF, 0);
	Motor_Controller(FORWARD, FORWARD, ROBOT_SPEED);
	setFlags(0, 0, 1, 0);
};

void goBackward() {
	LED_Controller(OFF, OFF, ON, ON, 0);
	Motor_Controller(BACKWARD, BACKWARD, ROBOT_SPEED);
	setFlags(0, 0, 0, 1);
};

void turnRight() {
	LED_Controller(OFF, ON, ON, OFF, 1);
	Motor_Controller(FORWARD, BACKWARD, ROBOT_SPEED);
	setFlags(0, 1, 0, 0);
};

void turnLeft() {
	LED_Controller(ON, OFF, OFF, ON, 1);
	Motor_Controller(BACKWARD, FORWARD, ROBOT_SPEED);
	setFlags(1, 0, 0, 0);
};

void stopCar() {
	LED_Controller(OFF, OFF, OFF, OFF, 1);
	Motor_Controller(STOP, STOP, 0);
	setFlags(0, 0, 0, 0);
};

void setFlags(int turnLeft, int turnRight, int forward, int backward) {
	TURN_LEFT_FLAG  = turnLeft;
	TURN_RIGHT_FLAG = turnRight;
	FORWARD_FLAG    = forward;
	BACKWARD_FLAG   = backward;
}
