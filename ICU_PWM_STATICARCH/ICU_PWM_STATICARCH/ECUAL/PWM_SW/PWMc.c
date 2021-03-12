/*
 * PWMc.c
 *
 * Created: 1/22/2020 11:09:01 AM
 *  Author: mostafahamoda1995
 */ 
#include "PWM.h"
#include "LCD_head.h"
static u8 u8Duty_Cycle = 0 ;
extern volatile u32 Ignite_Flag_Var_2  ;
u8 u8Pulse_pin ;
/*
* you must Enter your in time as a percentage of the second 
*/
extern ERROR_CHECK_t PWM_STEP(u8 u8_Pin,u8 u8_Duty) 
{
	/*
	* Initializing my Components
	*/
		Timer_Configuration_S_H Timer_Cfg ;
		Timer_Cfg.Timer_Channel = TIMER2;
		Timer_Cfg.Mode = TIMER_MODE ;
		Timer_Cfg.Timer_Mode = TIMER_MODE ;
		Timer_Cfg.Timer_Psc = PSC_8 ;
		Timer_Init(&Timer_Cfg) ;
	/*
	* Taking Input as a Percentage 
	*/
		u8Duty_Cycle = u8_Duty ;
		u8Pulse_pin = u8_Pin ;
		SET_BIT(DDRC,u8Pulse_pin) ;
	/*
	* Returning Error Checking
	*/
		return E_OK ;
}
extern ERROR_CHECK_t SEND_PULSE(void)
{
	Timer_Start(TIMER2,u8Duty_Cycle) ;
	SET_BIT(PORTC,u8Pulse_pin) ;
}

