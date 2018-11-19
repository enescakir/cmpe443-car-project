#include "LPC407x_8x_177x_8x.h"

#include "Library/Car.h"
#include "Library/Parameters.h"

int countHole = 0;

void init() {
	Car_Init();
}

void update() {
	// Handle joystick presses
	if (Joystick_Center_Pressed()) stopCar();
	else if (Joystick_Up_Pressed()) goForward();
	else if (Joystick_Down_Pressed()) goBackward();
	else if (Joystick_Left_Pressed()) turnLeft();
	else if (Joystick_Right_Pressed()) turnRight();

	// Count wheel rotation
	current = TIMER3->CR0;
	if (current - previous != 0 && (TURN_LEFT_FLAG || TURN_RIGHT_FLAG)) {
		capture  = current - previous;
		previous = current;

		if (capture != 0 && countHole < ROTATION_NUMBER_FOR_90_DEGREE * 2 - 1) {
			countHole++;
			capture = 0;
		} else {
			countHole = 0;
			stopCar();
		}
	}

}

int main() {
	init();

	while (1) {
		update();
	}
}
