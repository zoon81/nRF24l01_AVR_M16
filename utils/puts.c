#include "puts.h"

void UARTSendString(char * str)
{
	while (*str)
	{
		UARTSendByte(*str);
		str++;
	}
}
void UARTSend_uint8(uint8_t number)
{
	uint8_t data;
	if(number > 99){
		data = number / 100;
		number -= data * 100;
		UARTSendByte(data + 48);
		data = number / 10;
		number -= data * 10;
		UARTSendByte(data + 48);
		UARTSendByte(number + 48);
	}else if(number > 9){
		data = number / 10;
		number -= data * 10;
		UARTSendByte(data + 48);
		UARTSendByte(number + 48);
	} else if(number >= 0){
		UARTSendByte(number + 48);
	}
}