/*
 * uart.c
 *
 *  Created on: Oct 15, 2017
 *      Author: t400
 */
#include "uart.h"

void UARTInit()  
{
	UBRRL = UBRR_VAL; 
	UBRRH = (UBRR_VAL >> 8); 
	// UCSRA |= (1<<U2X0);

	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (3 << UCSZ0);	//set character size to 8bit
}
uint8_t  UARTReceive()
{
	while (!(UCSRA & (1 << RXC))){} // Varakozas amig nincs uj bejovo adat
	return UDR;
}

void UARTSendByte(uint8_t data) // Ez a fuggveny a kuldendo adatot beirja az UDR regiszter kimeno pufferjebe
{
	while (!(UCSRA & (1 << UDRE))){} // Varakozas amig az Ado kesz nem lesz az adatkuldesre
	UDR = data;
}

