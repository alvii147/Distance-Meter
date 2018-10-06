#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "adc.h"
#include "lcd.h"

void delay_10us(void);
float pulse_width_read(void);
void mode_change(void);
char a = 'c';
char b = 'm';

float dist;
float adjust = 1.0;

void main(void)
{
	DDRC |= (1<<0);
	DDRC &= ~(1<<1);
	DDRD |= (1<<7);
	DDRD &= ~(1<<5);
	DDRD &= ~(1<<3);
	DDRB |= (1<<6);
	
	PORTD |= (1<<7);
	PORTB |= (1<<6);
	
	while(1)
	{
		int state = 0;
		while(state != 1)
		{
			if(bit_is_clear(PIND, 5))
			{
				while(bit_is_clear(PIND, 5))
				{
					
				}
				state = 1;
			}
		}
		ADC_init();
		float temp = ADC_read()*(500.0/1023);
		float speed = 331 + (temp*0.6);
		
		LCDInit();
		char line[16];
		sprintf(line, "%0.1fC - %0.1fm/s", temp, speed);
		LCDGotoXY(1, 2);
		LCDString(line);
		
		mode_change();
		
		PORTC |= (1<<0);
		delay_10us();
		PORTC &= ~(1<<0);
		
		float time_us = pulse_width_read();
		dist = time_us*(speed/20000);
		
		char line2[16];
		sprintf(line2, "Length: %0.2f%c%c", dist*adjust, a, b);
		LCDGotoXY(1, 1);
		LCDString(line2);
	}
}

void delay_10us(void)
{
	TCCR0 |= (1<<CS00);
	TCCR0 &= ~(1<<CS01);
	TCCR0 &= ~(1<<CS02);
	
	TCNT0 = 0;
	
	while(TCNT0 < 80)
	{
		
	}
}

float pulse_width_read(void)
{
	while(bit_is_clear(PINC, 1))
	{
		
	}
	
	TCCR0 |= (1<<CS00);
	TCCR0 &= ~(1<<CS01);
	TCCR0 &= ~(1<<CS02);
	
	TCNT0 = 0;
	int count = 0;
	while(bit_is_set(PINC, 1))
	{
		if(TCNT0 == 255)
		{
			while(TCNT0 == 255)
			{
				
			}
			count++;
		}
	}
	
	unsigned int t1 = TCNT0 + (count*256);
	float t2 = t1/8.0;
	return t2;
}

void mode_change(void)
{
	sei();
	
	MCUCR &= ~(1<<ISC10);
	MCUCR &= ~(1<<ISC11);
	
	GICR |= (1<<INT1);	
}

ISR(INT1_vect)
{
	while(bit_is_clear(PIND, 3))
	{
		
	}
	
	if(adjust == 1.0)
	{
		adjust = 0.394;
		a = 'i';
		b = 'n';
	}
	else
	{
		adjust = 1.0;
		a = 'c';
		b = 'm';
	}
	
	char line3[16];
	sprintf(line3, "Length: %0.2f%c%c", dist*adjust, a, b);
	LCDGotoXY(1, 1);
	LCDString(line3);
}