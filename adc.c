#include "adc.h"

void ADC_init(void)
{
	ADMUX |= (1<<REFS0); //AVCC with external capacitor at AREF pin
	ADMUX &= ~(1<<REFS1); //AVCC with external capacitor at AREF pin

	ADCSRA &= ~(1<<ADPS0); //division factor of 64, ADC frequency = 8MHz/64 = 125kHz
	ADCSRA |= (1<<ADPS1); //division factor of 64, ADC frequency = 8MHz/64 = 125kHz
	ADCSRA |= (1<<ADPS2); //division factor of 64, ADC frequency = 8MHz/64 = 125kHz

	ADCSRA |= (1<<ADEN); //enable ADC
}


uint16_t ADC_read(void)
{
	ADMUX &= ~(1<<MUX0); //ADC0 channel selection
	ADMUX &= ~(1<<MUX1); //ADC0 channel selection
	ADMUX &= ~(1<<MUX2); //ADC0 channel selection
	ADMUX &= ~(1<<MUX3); //ADC0 channel selection
	ADMUX &= ~(1<<MUX4); //ADC0 channel selection

	ADCSRA |= (1<<ADSC); //start conversion

	ADMUX &= ~(1<<ADLAR); //ADLAR to right adjust the result
	while(ADCSRA & (1<<ADSC)) //loops until ADSC is completed
	{
		
	}
	return ADCW;
}