/*
 * main.c
 *
 *  Created on: Oct 15, 2017
 *      Author: t400
 */

#include "main.h"

struct payload payload;
uint8_t hasnewpackage = 0;

int main()
{

    // Prescaller 1024, CTC mode, interrupt on every ~25ms
    OCR0 = 200;
    TCCR0 |= BIT(WGM01);
    TCCR0 |= BIT(CS02) | BIT(CS00);
    TIMSK = BIT(OCIE0);

    //External interrupt on low level of INT2
    //MCUCR   |=  BIT(ISC01);
    GICR |= BIT(INT2);

    nRF2401_init(NRF_CSN_2, NRF_CE_2);
    nRF_2401_reg_read(CONFIG, NRF_CSN_2);
    nRF_2401_reg_read(STATUS, NRF_CSN_2);
    nRF2401_reset_IRQ(NRF_CSN_2);
    nRF2401_set_receiver_mode(NRF_CSN_2, NRF_CE_2);

    UARTInit();
    UARTSendString("HELLO\n\r");
    
    sei();
    while (1)
    {
        if (hasnewpackage)
        {
            UARTSendString("  Status : ");
            UARTSend_uint8(payload.header_status);
            UARTSendString("  VR2_x : ");
            UARTSend_uint8(payload.direction);
            UARTSendString("  VR3 : ");
            UARTSend_uint8(payload.speed);
            UARTSendString("  VR4 : ");
            UARTSend_uint8(payload.frontlight);
            UARTSendString("\n\r");
            hasnewpackage = 0;
        }
        _delay_ms(50);
    }

    return 0;
}

ISR(TIMER0_COMPA_vect)
{
}

ISR(INT2_vect)
{
    nRF2401_receive_payload(NRF_CSN_2, NRF_CE_2, &payload);
    hasnewpackage = 1;
}