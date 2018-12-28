#include "Car.h"

#define MAX(X,Y) (((X) < (Y)) ? (Y) : (X))

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
	External_Init();
	Serial_Init();
	LED_Controller(OFF, OFF, OFF, OFF, 0);
	if(WIFI_ENABLED){
		ESP8266_Init();
		wait(2000);
		Serial_Write("connect start\r\n");
		ESP8266_sendCommand("AT+CWJAP=\"HWLAB\",\"12345678\"\r\n");
		Serial_Write("connect end\r\n");
		wait(2000);
	}
	Serial_Write("\033[2J");
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
	
	Motor_Controller(FORWARD, BACKWARD, speed);
	if (flag) setFlags(0, 1, 0, 0);
};

void turnLeft(int rate, int flag) {
	LED_Controller(ON, OFF, OFF, ON, 1);
	Motor_Controller(BACKWARD, FORWARD, speed);
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
	if(turnCount % 200 == 0){
		distance = Ultrasonic_Get_Distance();
		turnCount = 0;
	}

	// Read light sources
	LDR_Left_Value  = LDR_Left_Read_Data();
	LDR_Right_Value = LDR_Right_Read_Data();
	LDR_Difference  = abs(LDR_Left_Value - LDR_Right_Value);
	
	turnCount += 1;
};

char toggleMode(void) {
	if (mode == AUTO) setMode(MANUEL);
	else if (mode == MANUEL) setMode(AUTO);
	
	return mode;
};

void setMode(int nMode) {
	stopCar();
	active = 0;
	mode = nMode;
	if(mode == AUTO){
		Serial_Write("AUTO\r\n");
	} else if (mode == MANUEL) {
		Serial_Write("MANUEL\r\n");
	}
};

void startEscape() {
	IS_ESCAPING = 1;
	goBackward();
};

void endEscape() {
	IS_ESCAPING = 0;
	goForward();
};

void setFlags(int turnLeft, int turnRight, int forward, int backward) {
	TURN_LEFT_FLAG  = turnLeft;
	TURN_RIGHT_FLAG = turnRight;
	FORWARD_FLAG    = forward;
	BACKWARD_FLAG   = backward;
}

int isMoving() {
	return (TURN_LEFT_FLAG + TURN_RIGHT_FLAG + FORWARD_FLAG + BACKWARD_FLAG) > 0;
};

void checkWifiMode(){
	Serial_Write("tcp start\r\n");
	ESP8266_sendCommand("AT+CIPSTART=\"TCP\",\"192.168.0.103\",8080\r\n");
	Serial_Write("tcp end\r\n");
	wait(2000);
	//ESP8266_waitResponseEnd();
	Serial_Write("cip start\r\n");
	ESP8266_sendCommand("AT+CIPSEND=47\r\n");
	Serial_Write("cip end\r\n");
	wait(3000);
	/*
	int status_send = ESP8266_waitResponseEnd();
	while(status_send != 7) {
		status_send = ESP8266_waitResponseEnd();
	}
	Serial_Write("> is here \r\n");
	*/
	Serial_Write("get start\r\n");
	char* cmd = "GET /HWLAB_IoT/GetInformation?ID=1 HTTP/1.0\r\n\r\n";
	ESP8266_sendCommand(cmd);
	Serial_Write("get start\r\n");
	wait(2000);
	int status = ESP8266_waitResponseEnd();
	if(status == 10) {
		if(mode != MANUEL) {
			setMode(MANUEL);
		}
	} else if(status == 11) {
		if(mode != AUTO) {
			setMode(AUTO);
		}
	} else if(status == 12) {
		if(mode == AUTO) {
			active = 1;
		}
	}
	Serial_Write("get end\r\n");
	// ESP8266_sendCommand("AT+CIPCLOSE\r\n");
}
