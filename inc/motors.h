#ifndef INC_MOTORS_H
#define INC_MOTORS_H

#include <avr/io.h>

#define MOTOR_FORW  PA1
#define MOTOR_BACK  PA0
#define MOTOR_SPEED PD7

#define STEERING_R PA3
#define STEERING_L PA4

void motor_setspeed(uint8_t speed, uint8_t direction);
void motors_init();

#endif