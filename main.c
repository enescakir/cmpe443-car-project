#include "LPC407x_8x_177x_8x.h"

#include "Library/Car.h"
#include "Library/Parameters.h"

void init() {
	Car_Init();
}

void update() {
	if (mode == AUTO) update_auto();
	else if (mode == MANUEL) update_manual();
}

void update_auto() {
	// Handle joystick presses
	if (Joystick_Center_Pressed()) active = 0;
	else if (Joystick_Up_Pressed()) active = 1;

	if (active) {

	}
}

void update_manual() {
	checkObstacle()

	// Handle joystick presses
	if (Joystick_Center_Pressed()) stopCar();
	else if (Joystick_Up_Pressed()) goForward();
	else if (Joystick_Down_Pressed()) goBackward();
	else if (Joystick_Left_Pressed()) turnLeft(20);
	else if (Joystick_Right_Pressed()) turnRight(20);
}

int main() {
	init();

	while (1) {
		updateSpeed()
		update();
	}
}
