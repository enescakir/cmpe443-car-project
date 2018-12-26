#include "LPC407x_8x_177x_8x.h"

#include "Library/Car.h"
#include "Library/Parameters.h"

void init() {
	Car_Init();
}


void update_auto() {
	// Handle joystick presses
	if (Joystick_Center_Pressed()) active = 0;
	else if (Joystick_Up_Pressed()) active = 1;

	if (active) {
		// Car is too close, stop car
		if (distance < OBSTACLE_DISTANCE / 2) {
			stopCar();
			return;
		}

		// Car is little close, half speed
		if (distance < OBSTACLE_DISTANCE) {
			speed = speed / 2;
		}

		if (LDR_Difference > DIFFERENCE_THRESHOLD) {
			if (LDR_Left_Value > LDR_Right_Value) {
				turnLeft(LDR_Difference);
			} else {
				turnRight(LDR_Difference);
			}
		} else {
			goForward();
		}
	}
}

void update_manual() {
	// Check distance
	checkObstacle();

	// Avoid from light source
	/*
	if (LDR_Left_Value < LIGHT_THRESHOLD) {
		turnRight(20);
	} else if (LDR_Right_Value < LIGHT_THRESHOLD) {
		turnLeft(20);
	} else if (FORWARD_FLAG) {
		goForward();
	} else if (BACKWARD_FLAG) {
		goBackward();
	}*/

	// Handle joystick presses
	if (Joystick_Center_Pressed()) stopCar();
	else if (Joystick_Up_Pressed()) goForward();
	else if (Joystick_Down_Pressed()) goBackward();
	else if (Joystick_Left_Pressed()) turnLeft(20);
	else if (Joystick_Right_Pressed()) turnRight(20);
}

void update() {
	if (mode == AUTO) update_auto();
	else if (mode == MANUEL) update_manual();
}

int main() {
	init();

	while (1) {
		updateSensorValues();

		update();
	}
}
