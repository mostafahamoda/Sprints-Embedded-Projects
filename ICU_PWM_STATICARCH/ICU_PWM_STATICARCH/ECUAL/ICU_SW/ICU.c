/*
 * ICU.c
 *
 * Created: 1/12/2020 8:34:24 AM
 *  Author: mostafahamoda1995
 */ 
#include "ICU.h"
/*
volatile u8 gu8_signal  ;
volatile u32 gu32Band_Width  ;
extern  u32 Ignite_Flag_Var ;*/
#include "LCD_head.h"
#include "avr/io.h"
/*
ISR(INT2_vect)
{
	if(gu8_signal == SIGNAL_START)
	{
		Timer_Start(TIMER0,1) ;
		EXT_INT_INIT(INT_TWO,FALLING_EDGE) ;
		PORTB = 0x00 ;
	}
	else if(gu8_signal == SIGNAL_END)
	{
		Timer_Stop(TIMER0) ;
		EXT_INT_INIT(INT_TWO,RISING_EDGE) ;
		gu32Band_Width =  Ignite_Flag_Var ;
	}
}
*/
volatile u8 gu8_signal  ;
volatile u32 gu32Band_Width  ;
extern  u32 Ignite_Flag_Var ;
char band[20] = {0} ;
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
		/ *if(gu32Band_Width != 0)
		{
		LCD_vPrintchar() ;
		gu32Band_Width = 0 ;
		}* /
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
		//extern u32 Ignite_Flag_Var ;
		gu32Band_Width = Ignite_Flag_Var ;
		/ *if(gu32Band_Width != 0)
		{
			itoa((int)gu32Band_Width,band,10) ;
			LCD_vPrintstring(band) ;
			LCD_vPrintchar('f') ;
			gu32Band_Width = 0 ;
		}* /
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
}*/
ERROR_CHECK_t ICU_Init(void)
{
	/*Initializing the Timer Structure*/
	Timer_Configuration_S_H Timer_Cfg ;
	Timer_Cfg.Timer_Channel = TIMER0;
	Timer_Cfg.Mode = TIMER_MODE ;
	Timer_Cfg.Timer_Mode = TIMER_MODE ;
	Timer_Cfg.Timer_Psc = PSC_8 ;
	
	
	Timer_Init(&Timer_Cfg) ;
	/*Initializing the External Interupt to Rising Edge*/
	
	
	EXT_INT_INIT(INT_TWO,RISING_EDGE) ; 
	gu8_signal = SIGNAL_START ;
	return E_OK;
}
u32 ICU_GetVal(void)
{
	u32 gu32Distance_Meter ;
	gu32Distance_Meter = gu32Band_Width / 2 ;
	return gu32Distance_Meter ;
}