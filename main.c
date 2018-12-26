#include "LPC407x_8x_177x_8x.h"

#include "Library/Car.h"
#include "Library/Parameters.h"

#include "Library/Serial.h"
#include "Library/ESP8266.h"

void init() {
	Car_Init();
	Serial_Write("\033[2J");

	ESP8266_Init();
	// ESP8266_sendCommand("AT+CWJAP=\"HWLAB\",\"enes12345\"\r\n");
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
				turnLeft(LDR_Difference, 1);
			} else {
				turnRight(LDR_Difference, 1);
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
	if (LDR_Left_Value < LIGHT_THRESHOLD) {
		turnRight(20, 0);
	} else if (LDR_Right_Value < LIGHT_THRESHOLD) {
		turnLeft(20, 0);
	} else if (FORWARD_FLAG) {
		goForward();
	} else if (BACKWARD_FLAG) {
		goBackward();
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
	ESP8266_sendCommand("AT+RST\r\n");
	wait(1000);
	ESP8266_sendCommand("AT+CWJAP=\"HWLAB\",\"12345678\"\r\n");
	Serial_Write("Bagli\r\n");
	Serial_Write(ESP8266_readResponse());
	Serial_Write("\r\n");
	ESP8266_sendCommand("AT+CIFSR\r\n");
	Serial_Write("IP1\r\n");
	ESP8266_waitResponseEnd();
	char* response = ESP8266_readResponse();
	Serial_Write(response);
	Serial_Write("\r\n");
	Serial_Write(esp8266Response);
	Serial_Write("\r\n");
	Serial_Write("IP2\r\n");
	Serial_Write("\r\n");
	while (1) {
//		updateSensorValues();
//
//		update();
	}
}
