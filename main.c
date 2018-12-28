#include "LPC407x_8x_177x_8x.h"

#include "Library/Car.h"
#include "Library/Parameters.h"

#include "Library/Serial.h"

void init() {
	Car_Init();
}


void update_auto() {
	// Handle joystick presses
	if (Joystick_Center_Pressed()) {
		active = 0;
		stopCar();
	} else if (Joystick_Up_Pressed()) {
		active = 1;
	}

	if (active) {
		// Check distance
		if (!IS_ESCAPING && distance < OBSTACLE_DISTANCE) {
			startEscape();
		} else if (IS_ESCAPING && distance > OBSTACLE_ESCAPE_DISTANCE && distance < ULTRASONIC_MAX_DISTANCE) {
			endEscape();
		}

		if(!IS_ESCAPING){
			if (LDR_Difference > DIFFERENCE_THRESHOLD) {
				if (LDR_Left_Value > LDR_Right_Value) {
					turnLeft(LDR_Difference, 1);
				} else {
					turnRight(LDR_Difference, 1);
				}
			} else {
				goForward();
			}
		}
	}
}

void update_manual() {

	if(isMoving()){
		// Check distance
		if (!IS_ESCAPING && FORWARD_FLAG && distance < OBSTACLE_DISTANCE) {
			startEscape();
		} else if (IS_ESCAPING && distance > OBSTACLE_ESCAPE_DISTANCE && distance < ULTRASONIC_MAX_DISTANCE) {
			endEscape();
		}

		// Avoid from light source
		if (FORWARD_FLAG && LDR_Left_Value < LIGHT_THRESHOLD) {
			turnRight(20, 0);
		} else if (FORWARD_FLAG && LDR_Right_Value < LIGHT_THRESHOLD) {
			turnLeft(20, 0);
		} else if (FORWARD_FLAG) {
			goForward() ;
		} else if (BACKWARD_FLAG) {
			goBackward();
		}
	}
	// Handle joystick presses
	if (Joystick_Center_Pressed()) stopCar();
	else if (Joystick_Up_Pressed()) goForward();
	else if (Joystick_Down_Pressed()) goBackward();
	else if (Joystick_Left_Pressed()) turnLeft(20, 1);
	else if (Joystick_Right_Pressed()) turnRight(20, 1);
}

void update() {
	if (mode == AUTO) update_auto();
	else if (mode == MANUEL) update_manual();
}

int main() {
	init();
		
	while (1) {
		if(WIFI_ENABLED){
			checkWifiMode();
		}
		updateSensorValues();
		
		update();
	}
}
