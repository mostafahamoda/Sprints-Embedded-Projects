/*
 * LCD_IMP.c
 *
 * Created: 3/1/2019 4:16:48 PM
 *  Author: mostafahamoda1995
 */ 
#include <avr/io.h>
#include "LCD_head.h"
#include "Common_Macros.h"
#define F_CPU 8000000ul 
#include <util/delay.h>
# include "SOS.h"

#ifdef LCD_8
void sendfallingedge(void)
{
	SET_BIT(PORTC,EN) ;
	_delay_ms(4) ;
	CLR_BIT(PORTC,EN) ;
	_delay_ms(4) ;
}
void LCD_vSendCmd(char cmd) 
{
	// Turn command bit (RS) off
	CLR_BIT(PORTC,RS) ;
	// PUT your command on your PORT
	PORTA = cmd ;
	// send falling edge 
	sendfallingedge();
}
void LCD_vClear()
{
	LCD_vSendCmd(0x01) ;
	
	sendfallingedge() ;
	
	_delay_ms(20) ;	
}
 void LCD_vInit(void) 
 {
	 DDRA = 0xFF ;
	 DDRC |= 0x0E ;
	 CLR_BIT(PORTC,RW) ;
	 // Sending commands to the LCD
	 // initialization in 8bit mode of 16X2 LCD
	 LCD_vSendCmd(0x38) ;
	 // Blink cursor
	 LCD_vSendCmd(0x0F) ;
	 // clear screen
	 LCD_vSendCmd(0x01) ;
	 _delay_ms(20) ;	 
 }
 
 void LCD_vMoveCursor( uint8 row , uint8 col) 
 {	
	int x ;
	if (row == 0)
	{
		x = 0x80 + col;
		LCD_vSendCmd(x) ;
	}
	else if (row == 1)
	{
		x = 0xc0 + col ;
		LCD_vSendCmd(x) ;
	} 
}
 void LCD_vPrintchar(char Data) 
 {
	 PORTA = Data ;
	 SET_BIT(PORTC,RS) ;
	 sendfallingedge() ; 
 }
 void LCD_vPrintstring(char * ptr) 
 {
	 int i ;
	 for(i=0;;i++)
	 {
		 if(ptr[i] != '\0' )
		 {
			 LCD_vPrintchar(ptr[i]) ;
		 }
		 else if(ptr[i] == '\0')
		 {
			 break ;
		 }		  	 
	 }
 }
 
 #elif defined LCD_4
 void sendfallingedge(void)
 {
	 SET_BIT(PORTA,EN) ;
	 _delay_ms(4) ;
	 CLR_BIT(PORTA,EN) ;
	 _delay_ms(4) ;
 }
  void LCD_vSendCmd(char cmd)
{
	CLR_BIT(PORTA,RS) ;
	PORTA &= 0x0f  ;
	PORTA |= cmd&0xf0 ;
	sendfallingedge() ;
	PORTA &= 0x0f ;
	PORTA |= (cmd<<4) ;
	sendfallingedge() ;
}

  void LCD_vInit(void)
{
	DDRA = 0xF0 ;
	DDRA |= 0x0E ;
	CLR_BIT(PORTA,RW) ;
	LCD_vSendCmd(0x33) ;
	LCD_vSendCmd(0x32) ;
	LCD_vSendCmd(0x28) ;
	// blink cursor
	LCD_vSendCmd(0x0F) ;
	// clear screen
	LCD_vSendCmd(0x01) ;
	_delay_ms(20) ;
}
  void LCD_vPrintchar(char data)
{
	SET_BIT(PORTA,RS) ;
	PORTA &= 0x0f  ;
	PORTA |= data&0xf0 ;
	sendfallingedge() ;
	PORTA &= 0x0f ;
	PORTA |= (data<<4) ;
	sendfallingedge() ;
}
  void LCD_vPrintstring(char * ptr)
 {
	 uint8 i ;
	 char fu ;
	 for(i=0;;i++)
	 {
		fu = *(ptr+i) ;
		 if(fu!='\0')
		 {
			 LCD_vPrintchar(fu) ;
		 }
		 else
		 {
			 break ;
		 }
		 
	 }
 }
  void LCD_vClear()
{
	LCD_vSendCmd(0x01) ;
	
	sendfallingedge() ;
	
	_delay_ms(20) ;
	
}
  void LCD_vMoveCursor( uint8 row , uint8 col)
 {
	 
	 
	 int x ;
	 if (row == 0)
	 {
		 x = 0x80 + col;
		 LCD_vSendCmd(x) ;
	 }
	 else if (row == 1)
	 {
		 x = 0xc0 + col ;
		 LCD_vSendCmd(x) ;
	 }
	 
	 
 }
#endif
 
  