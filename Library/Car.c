#include "Car.h"

int TURN_LEFT_FLAG  = 0;
int TURN_RIGHT_FLAG = 0;
int FORWARD_FLAG    = 0;
int BACKWARD_FLAG   = 0;
int IS_ESCAPING     = 0;

int speed     = 0;
int mode      = START_MODE;
int active    = 0;
int turnCount = 0;

// Sensor values
uint32_t distance        = 99999;
uint32_t LDR_Left_Value  = 0;
uint32_t LDR_Right_Value = 0;
uint32_t LDR_Difference  = 0;

void Car_Init() {
	Joystick_Init();
	Motor_Init();
	LED_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	Ultrasonic_Start_Trigger();
	Trimpot_Init();
	LDR_Init();
	LED_Controller(OFF, OFF, OFF, OFF, 0);
};

void goForward() {
	LED_Controller(ON, ON, OFF, OFF, 0);
	Motor_Controller(FORWARD, FORWARD, speed);
	setFlags(0, 0, 1, 0);
};

void goBackward() {
	LED_Controller(OFF, OFF, ON, ON, 0);
	Motor_Controller(BACKWARD, BACKWARD, speed);
	setFlags(0, 0, 0, 1);
};

void turnRight(int rate, int flag) {
	LED_Controller(OFF, ON, ON, OFF, 1);
	Motor_Controller(FORWARD + rate, FORWARD - rate, speed);
	if (flag) setFlags(0, 1, 0, 0);
};

void turnLeft(int rate, int flag) {
	LED_Controller(ON, OFF, OFF, ON, 1);
	Motor_Controller(FORWARD - rate, FORWARD + rate, speed);
	if (flag) setFlags(1, 0, 0, 0);
};

void stopCar() {
	LED_Controller(OFF, OFF, OFF, OFF, 1);
	Motor_Controller(STOP, STOP, 0);
	setFlags(0, 0, 0, 0);
};

void updateSensorValues(void) {
	// Read speed from trim pot
	speed = Trimpot_Read_Data();

	// Read distance from ultrasonic sensor
	distance = Ultrasonic_Get_Distance();

	// Read light sources
	LDR_Left_Value  = LDR_Left_Read_Data();
	LDR_Right_Value = LDR_Right_Read_Data();
	LDR_Difference  = abs(LDR_Left_Value - LDR_Right_Value);
};

char toggleMode(void) {
	if (mode == AUTO) mode = MANUEL;
	else if (mode == MANUEL) mode = AUTO;

	return mode;
};

void startEscape() {
	IS_ESCAPING = 1;
	goBackward();
};

void endEscape() {
	IS_ESCAPING = 0;
	goForward();
};

void checkObstacle(void) {
	if (distance < OBSTACLE_DISTANCE) {
		startEscape();
	} else if (distance > OBSTACLE_ESCAPE_DISTANCE && IS_ESCAPING) {
		endEscape();
	}
}

void setFlags(int turnLeft, int turnRight, int forward, int backward) {
	TURN_LEFT_FLAG  = turnLeft;
	TURN_RIGHT_FLAG = turnRight;
	FORWARD_FLAG    = forward;
	BACKWARD_FLAG   = backward;
}

int isMoving() {
	return (TURN_LEFT_FLAG + TURN_RIGHT_FLAG + FORWARD_FLAG + BACKWARD_FLAG) > 0;
};
