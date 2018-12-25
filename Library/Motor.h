#ifndef MOTOR_H
#define MOTOR_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "PWM.h"
#include "GPIO.h"

// PWM0[5] used for left motors
// P1.7 (P26)
#define IOCON_LEFT_MOTOR_ADDRESS 0x4002C09C
#define IOCON_LEFT_MOTOR *((volatile uint32_t *) IOCON_LEFT_MOTOR_ADDRESS)
#define IOCON_LEFT_MOTOR_PWM_FUNC 3
#define LEFT_MOTOR_PWM_CHANNEL 5

// PWM0[6] used for right motors
// P1.11 (P25)
#define IOCON_RIGHT_MOTOR_ADDRESS 0x4002C0AC
#define IOCON_RIGHT_MOTOR *((volatile uint32_t *) IOCON_RIGHT_MOTOR_ADDRESS)
#define IOCON_RIGHT_MOTOR_PWM_FUNC 3
#define RIGHT_MOTOR_PWM_CHANNEL 6

// IN1 PIN
#define IN1_PORT PORT1
#define IN1_MASK ((uint32_t) 1 << 23)

// IN2 PIN
#define IN2_PORT PORT1
#define IN2_MASK ((uint32_t) 1 << 24)

// IN3 PIN
#define IN3_PORT PORT0
#define IN3_MASK ((uint32_t) 1 << 5)

// IN4 PIN
#define IN4_PORT PORT0
#define IN4_MASK ((uint32_t) 1 << 4)

typedef enum {
	FORWARD  = 100,
	BACKWARD = -100,
	STOP     = 0
} Motor_Direction;


void Motor_Init(void);

void Motor_PWM_Init(void);

void Motor_Direction_Init(void);

void Motor_Write(uint32_t speed, uint32_t channel);

void Motor_Handle(int direction, GPIO_TypeDef *MOTOR1, uint32_t MASK1, GPIO_TypeDef *MOTOR2, uint32_t MASK2);

void Motor_Controller(int motor1, int motor2, int speed);

#endif
