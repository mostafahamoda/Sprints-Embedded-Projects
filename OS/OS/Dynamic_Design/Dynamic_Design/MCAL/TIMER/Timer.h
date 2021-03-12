/*
 * Timer.h
 *
 * Created: 11/22/2019 9:00:52 PM
 *  Author: A.Elkady
 */ 


#ifndef TIMER_H_
#define TIMER_H_

/*
*	Header files inclusions
*/
#include "Interrupt.h"
#include "Data_Types.h"
#include "TIMER_Ret_Val.h"

/*
*	Defining the frequency of the CPU
*/
#define F_CPU 8000000ul
/*
*	Timer registers
*/
#define TIMASK   ( *((volatile unsigned char *) (0x59) ) )
#define TIFREG   ( *((volatile unsigned char *) (0x58) ) )

/*
*	Timer 0 registers
*/
#define TCNT_0   ( *((volatile unsigned char *) (0x52) ) )
#define TCCR_0   ( *((volatile unsigned char *) (0x53) ) )
#define TOCR_0   ( *((volatile unsigned char *) (0x5C) ) )

/*
*	Timer 1 registers
*/
#define TCCR_1A  ( *((volatile unsigned char *) (0x4F) ) )
#define TCCR_1B  ( *((volatile unsigned char *) (0x4E) ) )
#define TCNT_1H  ( *((volatile unsigned char *) (0x4D) ) )
#define TCNT_1L  ( *((volatile unsigned char *) (0x4C) ) )
#define TOCR_1AH ( *((volatile unsigned char *) (0x4B) ) )
#define TOCR_1AL ( *((volatile unsigned char *) (0x4A) ) )
#define TOCR_1BH ( *((volatile unsigned char *) (0x49) ) )
#define TOCR_1BL ( *((volatile unsigned char *) (0x48) ) )
#define TICR_1H  ( *((volatile unsigned char *) (0x47) ) )
#define TICR_1L  ( *((volatile unsigned char *) (0x46) ) )

#define TCNT_1   ( *((volatile u16 *) (0x4C) ) )
#define TOCR_1A   ( *((volatile u16 *) (0x4A) ) )
#define TOCR_1B   ( *((volatile u16 *) (0x48) ) )

/*
*	Timer 2 registers
*/
#define TCCR_2   ( *((volatile unsigned char *) (0x45) ) )
#define TCNT_2   ( *((volatile unsigned char *) (0x44) ) )
#define TOCR_2   ( *((volatile unsigned char *) (0x43) ) )
#define ASSR_2   ( *((volatile unsigned char *) (0x42) ) ) 

/*
*	TIMASK bits
*/
#define T0_OVIE  0u  
#define T0_OCIE  1u
#define T1_OVIE  2u 
#define T1_OCIEB 3u
#define T1_OCIEA 4u
#define T1_ICIE  5u
#define T2_OVIE  6u 
#define T2_OCIE  7u

/*
*	TIFREG bits
*/
#define T0_OVF   0u  
#define T0_OCF   1u
#define T1_OVF   2u  
#define T1_OCFB  3u
#define T1_OCFA  4u
#define T1_ICF   5u
#define T2_OVF   6u  
#define T2_OCF   7u

/*
*	Macros used  
*/
#define TIMER0 0u
#define TIMER1 1u
#define TIMER2 2u

#define TIMER_MODE 0u
#define COUNTER_MODE 1u

#define INTERRUPT 0u
#define POLLING 1u

#define MAX_TCNT0_NUMBER 255u
#define MAX_TCNT1_NUMBER 65535u
#define MAX_TCNT2_NUMBER 255u

#define NUMBER_OF_TIMER_CHANNELS 3u


/*
*	The upcoming 9 macros is used in the calculations of number of ticks needed for a specific time
*/
#define FREQ_OVER_MILLI (F_CPU / 1000u)
#define FREQ_OVER_MICRO (F_CPU / 1000000u)

#define PRESCALE_0    1ul
#define PRESCALE_8    8ul
#define PRESCALE_32   32ul
#define PRESCALE_64   64ul
#define PRESCALE_128  128ul
#define PRESCALE_256  256ul
#define PRESCALE_1024 1024ul

/*
*	Timer 0 prescales represented as numbers from 0 to 7
*/
#define T0_PSC_NO_CLK  0u
#define T0_PSC_0 1u
#define T0_PSC_8 2u
#define T0_PSC_64 3u
#define T0_PSC_256 4u
#define T0_PSC_1024 5u
#define T0_PSC_EXT_ON_FALLING 6u
#define T0_PSC_EXT_ON_RISING 7u

/*
*	Timer 1 prescales represented as numbers from 0 to 7
*/
#define T1_PSC_NO_CLK  0u
#define T1_PSC_0 1u
#define T1_PSC_8 2u
#define T1_PSC_64 3u
#define T1_PSC_256 4u
#define T1_PSC_1024 5u
#define T1_PSC_EXT_ON_FALLING 6u
#define T1_PSC_EXT_ON_RISING 7u

/*
*	Timer 2 prescales represented as numbers from 0 to 7
*/
#define T2_PSC_NO_CLK  0u
#define T2_PSC_0 1u
#define T2_PSC_8 2u
#define T2_PSC_32 3u
#define T2_PSC_64 4u
#define T2_PSC_128 5u
#define T2_PSC_256 6u
#define T2_PSC_1024 7u

/*
*	Timer counter control register bits of timer 0
*/
typedef enum
{
	T0_CS00 = 0,
	T0_CS01    ,
	T0_CS02    ,
	T0_WGM01   ,
	T0_COM00   ,
	T0_COM01   ,
	T0_WGM00   ,
	T0_FOC
}T0_TCCR;

/*
*	Timer counter control register A bits of timer 1
*/
typedef enum
{
	T1_WGM10 = 0 ,
	T1_WGM11     ,
	T1_FOCB      ,
	T1_FOCA      ,
	T1_COM1B0    ,
	T1_COM1B1    ,
	T1_COM1A0    ,
	T1_COM1A1
}TCCREG_1A;

/*
*	Timer counter control register B bits of timer 1
*/
typedef enum
{
	T1_CS10 = 0 ,
	T1_CS11     ,
	T1_CS12     ,
	T1_WGM12    ,
	T1_WGM13    ,
	SPARE       ,
	T1_ICES     ,
	T1_ICNC
}TCCREG_1B;

/*
*	Asynchronous Status Register bits of timer 2
*/
typedef enum
{
	TCRUB   = 0,
	TOCRUB     ,
	TCNTUB     ,
	AS2
}ASSR;

/*
*	Timer counter control register bits of timer 2
*/
typedef enum
{
	T2_CS20 = 0,
	T2_CS21    ,
	T2_CS22    ,
	T2_WGM21   ,
	T2_COM20   ,
	T2_COM21   ,
	T2_WGM20   ,
	T2_FOC
}T2_TCCR;

/*
*	Definition of the timer configuration structure
*/
typedef struct{
	u8 u8Channel ;      /*  Timer 0 or 1 or 2  */
	u8 u8PSC ;          /* The desired prescale*/
	u8 u8Timer_mode ;   /*Timer or counter mode*/
	u8 u8Interrupt_mode;          /*Interrupt or Polling */
	} Timer_cfg_s;

/** 
 * \brief Timer_Init : A function that takes a pointer to the configuration structure to initialize the desired timer with the desired configuration
 *
 * \param *pstTimer_cfg (Input) : A pointer to the configuration structure (Struct contains : Timer Channel, Prescaler, Timer mode , Mode )
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Init(Timer_cfg_s *pstTimer_cfg);

/** 
 * \brief Timer_Start : A function that makes a particular timer (u8Channel) give a particular time (u32Ticks) 
 *
 * \param u8Channel (Input) : The desired timer to be started 
 * \param u32Time (Input)   : The desired ticks to be counted 
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Start(u8 u8Channel , u16 u16Ticks);

/** 
 * \brief Timer_Stop : A function that stops the clock of a particular timer (Channel)
 *
 * \param u8Channel : The desired timer to be stopped
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Stop(u8 u8Channel);

/** 
 * \brief Timer_reset : A function that reset a chosen timer
 *
 * \param u8Channel (Input) : Timer channel to be reset 
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Reset(u8 u8Channel) ;

/** 
 * \brief Timer_Get_Tick_Time : A function that calculates the time per tick for a particular timer , the time is returned in nano second
 *								
 * \param *Timer_time (Output) : The value of the timer per tick will be returned into that pointer
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Get_Tick_Time(u8 u8Channel, u32 *pu32Timer_time_ns);


#endif /* TIMER_H_ */