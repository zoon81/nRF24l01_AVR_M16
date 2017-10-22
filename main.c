/*
 * main.c
 *
 *  Created on: Oct 15, 2017
 *      Author: t400
 */

#include "main.h"

struct payload payload;

int main(){

    // Prescaller 1024, CTC mode, interrupt on every ~25ms
    OCR0 = 200;
    TCCR0 |= BIT(WGM01);
    TCCR0 |= BIT(CS02) | BIT(CS00);
    TIMSK = BIT(OCIE0);

    sei();
    nRF2401_init(NRF_CSN_2, NRF_CE_2 );

    nRF_2401_reg_read(CONFIG, NRF_CSN_2);
    nRF_2401_reg_read(STATUS, NRF_CSN_2);
    nRF2401_reset_IRQ(NRF_CSN_2);
    nRF2401_set_receiver_mode(NRF_CSN_2, NRF_CE_2);

    adc_init();
    UARTInit();

    while(1){
        UARTSendString("  VR2_x : ");
        UARTSend_uint8(payload.direction);
        UARTSendString("  VR3 : ");
        UARTSend_uint8(payload.speed);
        UARTSendString("  VR4 : ");
        UARTSend_uint8(payload.frontlight);
        UARTSendString("\n\r");
        _delay_ms(50);
    }
    
    return 0;
}
ISR(TIMER0_COMPA_vect){

}

ISR(ADC_vect){
  

}
