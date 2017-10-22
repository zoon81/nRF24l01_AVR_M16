#include "adc.h"

void adc_init(){
    ADMUX |= BIT(REFS0) | BIT(ADLAR);
    ADCSRA |= BIT(ADEN) | BIT(ADPS2) | BIT(ADPS1) | BIT(ADPS0);
}
uint8_t adc_read(uint8_t channel){
    ADMUX = (ADMUX & 0xE0) | channel;
    ADCSRA |= BIT(ADSC);
    while(!(ADCSRA & BIT(ADIF)));
    ADCSRA |= BIT(ADIF);
    return ADCH;
}
void adc_startconversion(uint8_t channel){
    ADMUX = (ADMUX & 0xE0) | channel;
    ADCSRA |= BIT(ADSC);
}