/*
 * timer.h
 *
 * Created: 11/22/2019 5:55:58 PM
 *
 */ 
#ifndef TIMER_H_
#define TIMER_H_
#include "Platform_Types.h"
#include "avr/interrupt.h"
#include "Timers_Regs.h"
#include "Common_Macros.h"
#include "LCD_head.h"
#define F_CPU 8000000UL
#define TIMER0 0
#define TIMER1 1
#define TIMER2 2
#define NO_OF_CHANNELS 3
#define Timer0_OVF_Val 255 
#define Timer1_OVF 65535
#define Timer2_OVF 255 
/****************************************************************/
/****************************************************************/
       /*******______TIMER_OR_COUNTER_____********/

#define TIMER_MODE 0
#define COUNTER_MODE 1

/****************************************************************/
/****************************************************************/
         /*********______PRESCALLER_____*********/

#define NO_CLOCK               0
#define PSC_0                  1
#define PSC_8                  2
#define PSC_64                 3
#define PSC_256                4
#define PSC_1024               5
#define EXT_CLK_ON_FALLING     6
#define EXT_CLK_ON_RISSING     7
#define PSC_REG_0 1
#define PSC_REG_8 2
#define PSC_REG_64 3
#define PSC_REG_256 4
#define PSC_REG_1024 5
#define F_CPU_Timer 8

/****************************************************************/
/****************************************************************/
     /********______POLLING OR INTERRUPT MODE_____*********/
		 
#define POLLING      0
#define INTERRUPT    1

/****************************************************************/
/****************************************************************/
    /*********______STRUCT.PASSED.TO.INT.FUN.______*********/

typedef struct
{
  u8 Timer_Channel;
  u8 Timer_Psc;
  u8 Timer_Mode;
  u8 Mode;
  u32 Res ;	
}Timer_Configuration_S_H;
static u8 Prescaller_Timer[NO_OF_CHANNELS]={0,0,0};
/******************************************************************************************************/
extern u8 Timer_Init(Timer_Configuration_S_H* Confg_S);
extern u8 Timer_Start(u8 Timer_Channel,u32 Required_Time);
extern u8 Timer_Stop(u8 Timer_Channel);
extern uint8_t Timer_Reset(uint8_t Copy_uint8_TimerChannel);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Tick Time value to use it by user
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *Timer_Time (Pointer to return Value)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Get_TickTime(uint8_t Copy_uint8_TimerChannel, uint32_t *Copy_uint8Ptr_TimerTickTime);
/*_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Flag Status
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *FlagStatus (Pointer to Flag)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t Timer_Get_FlagStatus(uint8_t Copy_uint8_TimerChannel, uint8_t *Copy_uint8Ptr_FlagStatus);
#endif /* TIMER_H_ */