/*
 * lcd.h
 *
 * Created: 06-Mar-2018 06:03:33 PM
 * Author : FAHIM REAZA
 */ 

#define F_CPU 8000000UL 

#include <avr/io.h>		// include I/O definitions (port names, pin names, etc)
#include <util/delay.h>
 
#define LCD_CONTROL_PORT			PORTA
#define LCD_CONTROL_DIRECTION		DDRA
#define LCD_DATA_PORT				PORTB
#define LCD_DATA_DIRECTION			DDRB
#define LCD_RS 						1	//LCD PIN 4 
#define LCD_RW						3	//LCD PIN 5 connect to GND. 
#define LCD_E 						2	//LCD PIN 6
#define LCD_D4						2	//LCD PIN 11
#define LCD_D5						3	//LCD PIN 12
#define LCD_D6						4	//LCD PIN 13
#define LCD_D7						5	//LCD PIN 14


#define LCD_MAX_CHAR_IN_LINE 		20


#define LCD_cmd							0 //RS=0 for command mode. 
#define LCD_data						1 //RS=1 for command mode. 

#define LCD_ENABLE 						1 //LCD Enable(E) set 0-to-1 for executing the current instruction 
#define LCD_DISABLE 					0 //LCD Enable(E) set 0-to-1 for executing the current instruction


//Entry modes, use at initialization
#define LCD_CURSOR_SHIFT_LEFT_MODE		0x04// 0000 0100
#define LCD_DISPLAY_SHIFT_LEFT_MODE		0x05// 0000 0101
#define LCD_CURSOR_SHIFT_RIGHT_MODE		0x06// 0000 0110
#define LCD_DISPLAY_SHIFT_RIGHT_MODE	0x07// 0000 0111 


//DDRAM Addresses
#define DDRAM_PTR  0x80   // Address Display Data RAM pointer
#define LINE1_ADDR 0x00   // Start of line 1 in the DD-Ram 
#define LINE2_ADDR 0x40   // Start of line 2 in the DD-Ram
#define LINE3_ADDR 0x14   // Start of line 3 in the DD-Ram
#define LINE4_ADDR 0x54   // Start of line 4 in the DD-Ram


//Display modes, use at initialization
#define LCDOff()				LCDSendCmd(0x08)
#define LCDOn()					LCDSendCmd(0x0C)
#define LCDCursorOff()			LCDSendCmd(0x0C)
#define LCDCursorNoBlink()		LCDSendCmd(0x0E)
#define LCDCursorBlink()		LCDSendCmd(0x0F)
#define LCDClear()				LCDSendCmd(0x01); _delay_ms(10)
#define LCDCursorHome()			LCDSendCmd(0x02)
#define LCDCursorLeft()			LCDSendCmd(0x10)
#define LCDCursorRight()		LCDSendCmd(0x14)
#define LCDDisplayShiftLeft()	LCDSendCmd(0x1C)
#define LCDDisplayShiftRight()	LCDSendCmd(0x18)



void LCDSendCmd4BIT(unsigned char ucCmd);

void LCDSendCmd(unsigned char ucCmd);
void LCDSendData (unsigned char ucData);

void LCDGotoXY(unsigned char x,unsigned char y);

void LCDInit(void);

void LCDString(char *msg);

void LCDShowCursor(void);

void LCDHideCursor(void);

void LCDRefresh(void);

void LCDPutchar(char c);


