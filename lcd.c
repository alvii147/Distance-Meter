/*
 * lcd.c
 *
 * Created: 06-Mar-2018 06:03:33 PM
 * Author : FAHIM REAZA
 */ 
 
 
#include "lcd.h"

void LCDInit()
{

	LCD_CONTROL_DIRECTION |= (1<<LCD_RS); //Set DDRC_Of_RS as OUTPUT Pin. 
	LCD_CONTROL_DIRECTION |= (1<<LCD_RW); //Set DDRC_Of_RW as OUTPUT Pin. 
	LCD_CONTROL_DIRECTION |= (1<<LCD_E); //Set DDRC_Of_E as OUTPUT Pin. 

	LCD_DATA_DIRECTION |= (1<<LCD_D4); //Set DDRC_Of_D4 as OUTPUT Pin. 
	LCD_DATA_DIRECTION |= (1<<LCD_D5); //Set DDRC_Of_D5 as OUTPUT Pin. 
	LCD_DATA_DIRECTION |= (1<<LCD_D6); //Set DDRC_Of_D6 as OUTPUT Pin. 
	LCD_DATA_DIRECTION |= (1<<LCD_D7); //Set DDRC_Of_D7 as OUTPUT Pin. 


	LCD_CONTROL_PORT &= ~(1<<LCD_RS); //PORT_Of_RS goes to LOW for Command Mode 
	LCD_CONTROL_PORT &= ~(1<<LCD_E); //Clear of PORT_Of_E (Initialize stage is zero)  
	_delay_ms(150);

	LCDSendCmd4BIT(0x03); // 8-bit data length (Repeat 3-times for clear lcd memory) 
	_delay_ms(150);
	LCDSendCmd4BIT(0x03); // 8-bit data length (Repeat 3-times for clear lcd memory) 
	_delay_ms(150);
	LCDSendCmd4BIT(0x03); // 8-bit data length (Repeat 3-times for clear lcd memory) 
	_delay_ms(150);

	LCDSendCmd4BIT(0x02); 	//Set to 4 bit operation 
	LCDSendCmd(0x28);		//function set, 4 line, 8-bit, character size=5x7 
	LCDClear();				//clear display (0x01) 
	LCDOff();				//turn off the LCD (0x08) 
	LCDOn();				//turn on the LCD (0x0C) 
	LCDSendCmd(0x06); 		//Sets mode to increment the address by one and to shift the cursor to the right at the time of write to the DD/CGRAM. 
	LCDSendCmd(DDRAM_PTR); 	//set DDRAM Address (0x80) 
}


void LCDGotoXY(unsigned char x,unsigned char y)
{
	if(y == 1)
	{
		LCDSendCmd(DDRAM_PTR + LINE1_ADDR + x-1);
	}
	else if(y == 2)
	{
		LCDSendCmd(DDRAM_PTR + LINE2_ADDR + x-1);
	}
	else if(y == 3)
	{
		LCDSendCmd(DDRAM_PTR + LINE3_ADDR + x-1);
	}
	else if(y == 4)
	{
		LCDSendCmd(DDRAM_PTR + LINE4_ADDR + x-1);
	}
}

void LCDSendCmd(unsigned char ucCmd)
{
	LCD_CONTROL_PORT &= ~(1<<LCD_RS); //LCD in COMMAND mode 

	LCDSendCmd4BIT(ucCmd>>4);
	LCDSendCmd4BIT(ucCmd);
}


void LCDSendData (unsigned char ucData)
{
	LCD_CONTROL_PORT |= (1<<LCD_RS); //LCD in DATA mode 

	LCDSendCmd4BIT(ucData>>4);
	LCDSendCmd4BIT(ucData);
}


void LCDSendCmd4BIT(unsigned char ucCmd)
{
	
	if(ucCmd&0x01) LCD_DATA_PORT |= (1<<LCD_D4);
	else LCD_DATA_PORT &= ~(1<<LCD_D4);

	if(ucCmd&0x02) LCD_DATA_PORT |= (1<<LCD_D5);
	else LCD_DATA_PORT &= ~(1<<LCD_D5);

	if(ucCmd&0x04) LCD_DATA_PORT |= (1<<LCD_D6);
	else LCD_DATA_PORT &= ~(1<<LCD_D6);

	if(ucCmd&0x08) LCD_DATA_PORT |= (1<<LCD_D7);
	else LCD_DATA_PORT &= ~(1<<LCD_D7);

	LCD_CONTROL_PORT |= (1<<LCD_E);
	LCD_CONTROL_PORT &= ~(1<<LCD_E);

	_delay_ms(2);
}



void LCDPutchar(char c)
{
	LCDSendData(c);
}


void LCDString(char *msg)
{
	uint8_t len = 0;

	while(*msg)
	{
		LCDPutchar(*msg);
		msg++; 
		len++;
	}

	while(LCD_MAX_CHAR_IN_LINE - len)
	{
		LCDPutchar(0x20); // Space
		len++;
	}

}


void LCDShowCursor()
{
	LCDSendCmd(0x0E); // Display on, Cursor On and Blink On;
}


void LCDHideCursor()
{
	LCDSendCmd(0x0C); // Display on, Cursor Off and Blink Off;
}


void LCDRefresh()
{
	LCD_CONTROL_PORT &= ~(1<<LCD_RS); //LCD in COMMAND mode 
	LCD_CONTROL_PORT &= ~(1<<LCD_E); //LCD disable 

	_delay_ms(2);

	LCDSendCmd4BIT(0x03);
	_delay_ms(2);

	LCDSendCmd4BIT(0x03);
	_delay_ms(2);

	LCDSendCmd4BIT(0x03);
	_delay_ms(2);

	LCDSendCmd4BIT(0x02);
	_delay_ms(2);

	LCDSendCmd(0x28);		//function set, 4 line, 8-bit, character size=5x7
	LCDSendCmd(0x02 );
	LCDOn();				//turn on the LCD
	LCDSendCmd(0x06);
	LCDSendCmd(DDRAM_PTR); 	//set DDRAM Address
}
