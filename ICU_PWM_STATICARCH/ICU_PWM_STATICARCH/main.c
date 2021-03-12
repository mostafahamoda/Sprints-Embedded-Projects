/*
 * ICU_PWM_STATICARCH.c
 *
 * Created: 1/11/2020 4:53:27 PM
 * Author : mostafahamoda1995
 */ 
#include "EXT_INT.h"
#include "avr/interrupt.h"
#include "util/delay.h"
#include "avr/io.h"
#include "timer.h"
#include "Common_Macros.h"
#include "ICU.h"
#include "LCD_head.h"
#include "PWM.h"
#include "EXT_INT.h"
#define F_CPU 8000000ul

void Send_Pulse(void)
{
	SET_BIT(PORTC,2) ;
	_delay_ms(50) ;
	CLEAR_BIT(PORTC,2) ;
}
volatile int hamo = 0 ;
/*
extern u32 Ignite_Flag_Var ;
extern u32 gu32Band_Width  ;*/
/*
volatile u8 gu8_signal  ;
volatile u32 gu32Band_Width  ;
extern  u32 Ignite_Flag_Var ;
char band[20] = {0} ;*/
	
ISR(INT2_vect)
{	
	if(hamo == 0)
	{
		DDRB = 0xF0 ;
		PORTB = 0xF0 ;
		hamo = 1 ;
	}
	else
	{
		PORTB = 0x00 ;
		hamo = 0 ;
	}
}
int main(void)
{
	/*ICU_Init() ;
	LCD_vInit() ;
	PWM_STEP(2,ULTRASONIC_W) ;
	DDRB = 0xFF ;
	PORTB = 0xF0 ;
	DDRD = 0xFF ;
	PORTD = 0xFF ;
	DDRC = 0xFF ;
	char  Data , Old_Data ;
	LCD_vPrintchar('D') ;
	//char dummy = '2' ;
	volatile u32 Number = 0;
	volatile u32 Number2 = 0 ;
	char band[20] = {0} ;
    while (1) 
    {
		Number = ICU_GetVal() ;
		if((Number != 0) && (Number != Number2))
		{
			itoa((int)Number,band,10) ;
			LCD_vPrintstring(band) ;
			Number2 = Number ;
			Number = 0 ;
		}
		Send_Pulse() ;
	}
}*/
/*



ISR(INT2_vect)
{
	if(gu8_signal == SIGNAL_START)
	{
		Timer_Start(TIMER0,ICU_REQ_TIME) ;
		EXT_INT_INIT(INT_TWO,FALLING_EDGE) ;
		gu8_signal = SIGNAL_END ;
		PORTB = 0x00 ;
	}
	else if(gu8_signal == SIGNAL_END)
	{
		PORTB = 0xF0 ;
		extern u32 Ignite_Flag_Var ;
		gu32Band_Width = Ignite_Flag_Var ;
		if(gu32Band_Width != 0)
		{
			itoa((int)gu32Band_Width,band,10) ;
			LCD_vPrintstring(band) ;
			LCD_vPrintchar('f') ;
			gu32Band_Width = 0 ;
		}
		Timer_Stop(TIMER0) ;
		EXT_INT_INIT(INT_TWO,RISING_EDGE) ;
		/ *int  gu8_DODO = 5 ;
		gu8_DODO = Ignite_Flag_Var ;
		char buffer[20]  = "HA";
		itoa(gu8_DODO,buffer,10) ;
		if(gu32Band_Width != 0)
		{
			LCD_vPrintstring(buffer) ; 
		}* /
		/ *gu8_DODO = 0 ;* /
		gu8_signal = SIGNAL_START ;
	}
}
*/
	LCD_vInit() ;
	EXT_INT_INIT(INT_TWO,RISING_EDGE) ;
	while(1);
}

