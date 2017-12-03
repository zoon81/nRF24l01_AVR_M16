/*
 * main.c
 *
 *  Created on: Oct 15, 2017
 *      Author: t400
 */

#include "main.h"

volatile uint8_t hasnewpackage = 0;
struct payload payload;

int main()
{
    // Prescaller 1024, CTC mode, interrupt on every ~25ms
    /*
    OCR0 = 200;
    TCCR0 |= BIT(WGM01);
    TCCR0 |= BIT(CS02) | BIT(CS00);
    TIMSK = BIT(OCIE0);
    */

    //External interrupt on low level of INT2
    //MCUCR   |=  BIT(ISC01);
    GICR |= BIT(INT2);
    UARTInit();

    nRF2401_init(NRF_CSN_2, NRF_CE_2);
    UARTSendString("  NRF_Config : ");
    UARTSend_uint8(nRF_2401_reg_read(CONFIG, NRF_CSN_2));
    UARTSendString("  NRF_Status : ");
    UARTSend_uint8(nRF_2401_reg_read(STATUS, NRF_CSN_2));
    nRF2401_reset_IRQ(NRF_CSN_2);
    nRF2401_set_receiver_mode(NRF_CE_2);
    sei();
    UARTSendString("HELLO\n\r");
    while (1)
    {
        if (hasnewpackage)
        {
            UARTSendString("  NRF_Status : ");
            UARTSend_uint8(nRF_2401_reg_read(STATUS, NRF_CSN_2));
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
    }

    return 0;
}

ISR(INT2_vect)
{
    nRF2401_receive_payload_it(NRF_CSN_2, NRF_CE_2, &payload);
    nRF2401_set_receiver_mode(NRF_CE_2);
    hasnewpackage = 1;
}