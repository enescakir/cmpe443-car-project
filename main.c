#include "LPC407x_8x_177x_8x.h"

#include "Library/GPIO.h"
#include "Library/PWM.h"
#include "Library/Joystick.h"
#include "Library/Parameters.h"
#include "Library/LED.h"
#include "Library/Motor.h"

void init() {
	Joystick_Init();
	LED_Init();
	LED_Controller(ON, OFF, ON, OFF);
	Motor_PWM_Init();
	Motor_Direction_Init();
	Motor_Controller(0,1,1,0);
	PWM_Write(20);
}

//When code start, LED should be turned off.
//When you press the UP button of the Joystick, LED will be turned on (use 50% Duty Cycle)
//When you press the CENTER button of the Joystick, LED will be turned on (use 100% Duty Cycle)
//When you press the DOWN button of the Joystick, LED will be turned off.
//When you press the LEFT button of the Joystick, LED will blink (10 times in a second).
//When you press the RIGHT button of the Joystick, LED will blink (2 times in a second).
void update() {
	if (Joystick_Center_Pressed()){
		PWM_Write(0);
		LED_Controller(OFF,OFF,OFF,OFF);
		Motor_Controller(0,0,0,0);
	}
	else if (Joystick_Up_Pressed()){
			PWM_Write(ROBOT_SPEED);
			LED_Controller(ON,ON,OFF,OFF);
			Motor_Controller(1,0,1,0);
	}
	else if (Joystick_Down_Pressed()){
			PWM_Write(ROBOT_SPEED);
			LED_Controller(OFF,OFF,ON,ON);
			Motor_Controller(0,1,0,1);
	}
	else if (Joystick_Left_Pressed()){
			PWM_Write(ROBOT_SPEED);
			LED_Controller(BLINK,OFF,OFF,BLINK);
			Motor_Controller(0,1,1,0);
	}
	else if (Joystick_Right_Pressed()){
			PWM_Write(ROBOT_SPEED);
			LED_Controller(OFF,BLINK,BLINK,OFF);
			Motor_Controller(1,0,0,1);
	}





}

int main() {
	init();

	while (1) {
		update();
	}
}
