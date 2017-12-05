#include "motors.h"

void motors_init(){
    DDRA |= BIT(MOTOR_FORW) | BIT(MOTOR_BACK) | BIT(STEERING_L) | BIT(STEERING_R);
    DDRD |= BIT(MOTOR_SPEED);

    //Setup timer2 for PWM
    //PWM, Phase Correct
    //Clear OC2 on compare match when up-counting. Set OC2 on compare match when downcounting.
    ///128 From prescaler
    OCR2 = 0;
    TCCR2 = BIT(WGM20) | BIT(COM21) | BIT(CS22) | BIT(CS20); 

}

void motor_setspeed(uint8_t speed, uint8_t direction){
    OCR2 = speed;
    if(direction){
        // Forward
        PORTA &= ~BIT(MOTOR_BACK);
        PORTA |= BIT(MOTOR_FORW);
    }else{
        // Backward
        PORTA &= ~BIT(MOTOR_FORW);
        PORTA |= BIT(MOTOR_BACK);
    }
}