/*
 * Timer.c
 *
 * Created: 11/22/2019 9:00:44 PM
 *  Author: A.Elkady
 */ 

#include "Timer.h"

/*
*	Static variable that tells if the module is initialized or not 
*/
static u8 gu8Is_timer_init = TIMER_E_NOT_INITIALIZED_YET ;

/*
*	Static array holds variables storing timers' prescale config. 
*/
static u8 gau8Timer_PSC[NUMBER_OF_TIMER_CHANNELS] = {0} ; /*Holds the current prescale of timer 0 , 1 , 2*/

/*
*	Static array holds variables storing timers' modes config 
*/
static u8 gau8Timer_Mode[NUMBER_OF_TIMER_CHANNELS] = {0} ;  /*Polling or interrupt*/

/*
*	Static array holds variables storing the time tick values in nano seconds 
*/
static u32 gau32Tick_time[NUMBER_OF_TIMER_CHANNELS] = {0} ;
	
/** 
 * \brief Timer_Ignite : A static function that is used to restart the clock of a particular timer after stopping it with Timer_Stop function
 *
 * \param u8Channel (Input) : The desired timer to be restarted
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/ 
static Error Timer_Ignite(u8 u8Channel);

static Error Timer_Ignite(u8 u8Channel)
{
	/*
	*	Declaration and definition of the variable that will hold the execution indication
	*/
	Error u8Execution_indication = TIMER_E_OK ;
	
	if (TIMER_INITIALIZED == gu8Is_timer_init )
	{
		if(TIMER0 == u8Channel)
		{
			if (T0_PSC_NO_CLK == gau8Timer_PSC[0] )
			{
				TCCR_0 &= ~(1 << T0_CS00);
				TCCR_0 &= ~(1 << T0_CS01);
				TCCR_0 &= ~(1 << T0_CS02);
			}
			else if(T0_PSC_0 == gau8Timer_PSC[0])
			{
				TCCR_0 |=  (1 << T0_CS00);
				TCCR_0 &= ~(1 << T0_CS01);
				TCCR_0 &= ~(1 << T0_CS02);
			}
			else if(T0_PSC_8 == gau8Timer_PSC[0])
			{
				TCCR_0 &= ~(1 << T0_CS00);
				TCCR_0 |=  (1 << T0_CS01);
				TCCR_0 &= ~(1 << T0_CS02);
			}
			else if(T0_PSC_64 == gau8Timer_PSC[0])
			{
				TCCR_0 |=  (1 << T0_CS00);
				TCCR_0 |=  (1 << T0_CS01);
				TCCR_0 &= ~(1 << T0_CS02);
			}
			else if(T0_PSC_256 == gau8Timer_PSC[0])
			{
				TCCR_0 &= ~(1 << T0_CS00);
				TCCR_0 &= ~(1 << T0_CS01);
				TCCR_0 |=  (1 << T0_CS02);
			}
			else if(T0_PSC_1024 == gau8Timer_PSC[0])
			{
				TCCR_0 |=  (1 << T0_CS00);
				TCCR_0 &= ~(1 << T0_CS01);
				TCCR_0 |=  (1 << T0_CS02);
			}
			else if(T0_PSC_EXT_ON_FALLING == gau8Timer_PSC[0] )
			{
				TCCR_0 &= ~(1 << T0_CS00);
				TCCR_0 |=  (1 << T0_CS01);
				TCCR_0 |=  (1 << T0_CS02);
			}
			else if(T0_PSC_EXT_ON_RISING == gau8Timer_PSC[0] )
			{
				TCCR_0 |=  (1 << T0_CS00);
				TCCR_0 |=  (1 << T0_CS01);
				TCCR_0 |=  (1 << T0_CS02);
			}
			else
			{
				/* Handling of entering wrong Pre scale */
				u8Execution_indication = TIMER_E_WRONG_PSC ;
			}
		}
		else if (TIMER1 == u8Channel)
		{
			if (T1_PSC_NO_CLK == gau8Timer_PSC[1] )
			{
				TCCR_1B &= ~(1 << T1_CS10);
				TCCR_1B &= ~(1 << T1_CS11);
				TCCR_1B &= ~(1 << T1_CS12);
			}
			else if(T1_PSC_0 == gau8Timer_PSC[1] )
			{
				TCCR_1B |=  (1 << T1_CS10);
				TCCR_1B &= ~(1 << T1_CS11);
				TCCR_1B &= ~(1 << T1_CS12);
			}
			else if(T1_PSC_8 == gau8Timer_PSC[1] )
			{
				TCCR_1B &= ~(1 << T1_CS10);
				TCCR_1B |=  (1 << T1_CS11);
				TCCR_1B &= ~(1 << T1_CS12);
			}
			else if(T1_PSC_64 == gau8Timer_PSC[1])
			{
				TCCR_1B |=  (1 << T1_CS10);
				TCCR_1B |=  (1 << T1_CS11);
				TCCR_1B &= ~(1 << T1_CS12);
			}
			else if(T1_PSC_256 == gau8Timer_PSC[1])
			{
				TCCR_1B &= ~(1 << T1_CS10);
				TCCR_1B &= ~(1 << T1_CS11);
				TCCR_1B |=  (1 << T1_CS12);
			}
			else if(T1_PSC_1024 == gau8Timer_PSC[1])
			{
				TCCR_1B |=  (1 << T1_CS10);
				TCCR_1B &= ~(1 << T1_CS11);
				TCCR_1B |=  (1 << T1_CS12);
			}
			else if(T1_PSC_EXT_ON_FALLING == gau8Timer_PSC[1])
			{
				TCCR_1B &= ~(1 << T1_CS10);
				TCCR_1B |=  (1 << T1_CS11);
				TCCR_1B |=  (1 << T1_CS12);
			}
			else if(T1_PSC_EXT_ON_RISING == gau8Timer_PSC[1] )
			{
				TCCR_1B |=  (1 << T1_CS10);
				TCCR_1B |=  (1 << T1_CS11);
				TCCR_1B |=	(1 << T1_CS12);
			}
			else
			{
				/*Handling of entering wrong Pre scale*/
				u8Execution_indication = TIMER_E_WRONG_PSC ;
			}
		}
		else if (TIMER2 == u8Channel)
		{
			if (T2_PSC_NO_CLK == gau8Timer_PSC[2])
			{
				TCCR_2 &= ~(1 << T2_CS20);
				TCCR_2 &= ~(1 << T2_CS21);
				TCCR_2 &= ~(1 << T2_CS22);
			}
			else if(T2_PSC_0 == gau8Timer_PSC[2] )
			{
				TCCR_2 |=  (1 << T2_CS20);
				TCCR_2 &= ~(1 << T2_CS21);
				TCCR_2 &= ~(1 << T2_CS22);
			}
			else if(T2_PSC_8 == gau8Timer_PSC[2])
			{
				TCCR_2 &= ~(1 << T2_CS20);
				TCCR_2 |=  (1 << T2_CS21);
				TCCR_2 &= ~(1 << T2_CS22);
			}
			else if(T2_PSC_32 == gau8Timer_PSC[2])
			{
				TCCR_2 |=  (1 << T2_CS20);
				TCCR_2 |=  (1 << T2_CS21);
				TCCR_2 &= ~(1 << T2_CS22);
			}
			else if(T2_PSC_64 == gau8Timer_PSC[2])
			{
				TCCR_2 &= ~(1 << T2_CS20);
				TCCR_2 &= ~(1 << T2_CS21);
				TCCR_2 |=  (1 << T2_CS22);
			}
			else if(T2_PSC_128 == gau8Timer_PSC[2])
			{
				TCCR_2 |=  (1 << T2_CS20);
				TCCR_2 &= ~(1 << T2_CS21);
				TCCR_2 |=  (1 << T2_CS22);
			}
			else if(T2_PSC_256 == gau8Timer_PSC[2])
			{
				TCCR_2 &= ~(1 << T2_CS20);
				TCCR_2 |=  (1 << T2_CS21);
				TCCR_2 |=  (1 << T2_CS22);
			}
			else if(T2_PSC_1024 == gau8Timer_PSC[2])
			{
				TCCR_2 |=  (1 << T2_CS20);
				TCCR_2 |=  (1 << T2_CS21);
				TCCR_2 |=  (1 << T2_CS22);
			}
			else
			{
				/*Handling of entering wrong Pre scale*/
				u8Execution_indication = TIMER_E_WRONG_PSC ;
			}
			
		}
		else
		{
			/*Handling of entering wrong channel*/
			u8Execution_indication = TIMER_E_WRONG_CHANNEL ;
		}
	} 
	else
	{
		/*
		*	Handling of using the module before initializing it
		*/
		u8Execution_indication = TIMER_E_NOT_INITIALIZED_YET ;
	}
	
	return u8Execution_indication ;
}

/** 
 * \brief Timer_Init : A function that takes a pointer to the configuration structure to initialize the desired timer with the desired configuration
 *
 * \param *pstTimer_cfg (Input) : A pointer to the configuration structure (Struct contains : Timer Channel, Prescaler, Timer mode , Mode )
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Init(Timer_cfg_s *pstTimer_cfg)
{
	/*
	*	Declaration and definition of the variable that will hold the execution indication
	*/
	Error u8Execution_indication = TIMER_E_OK ;
	
	if (0 != pstTimer_cfg ) /* Checking that the passed pointer is not a NULL one */
	{
		if (TIMER0 == pstTimer_cfg -> u8Channel ) 
		{
			/*
			*	Passing the Timer Prescale to its static variable 
			*/
			
			gau8Timer_PSC[TIMER0] = (pstTimer_cfg -> u8PSC) ;
			
			/*
			*	Checking the desired Mode if it's polling or interrupt
			*/
			if (INTERRUPT == pstTimer_cfg -> u8Interrupt_mode )
			{
				Enable_GlobalInterrupt() ;  /*Enable global interrupt*/
				/*
				*	Passing the Timer mode to its static variable 
				*/
				gau8Timer_Mode[TIMER0] = INTERRUPT ;
				TIMASK |= (1 << T0_OVIE) ; /*Enable the interrupt request for timer 0 overflow*/
			} 
			else if(POLLING == pstTimer_cfg -> u8Interrupt_mode )
			{
				TIMASK &= ~(1 << T0_OVIE) ; /*Disable the interrupt request for timer 0 overflow*/
				/*
				*	Passing the Timer mode to its static variable 
				*/
				gau8Timer_Mode[TIMER0] = POLLING ;
			}
			else
			{
				/* Handling of entering wrong Mode */
				u8Execution_indication = TIMER_E_WRONG_INTERRUPT_MODE ;
			}
			
			/*
			*	Enable the CTC mode of timer 0
			*/
			TCCR_0 |= (1 << T0_WGM01) ;
			
			/*
			*	Calculating the time per tick and passing it to a static variable
			*/
			if (T0_PSC_0 == gau8Timer_PSC[TIMER0])
			{
				gau32Tick_time[TIMER0] = (PRESCALE_0 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T0_PSC_8 == gau8Timer_PSC[TIMER0])
			{
				gau32Tick_time[TIMER0] = (PRESCALE_8 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T0_PSC_64 == gau8Timer_PSC[TIMER0])
			{
				gau32Tick_time[TIMER0] = (PRESCALE_64 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T0_PSC_256 == gau8Timer_PSC[TIMER0])
			{
				gau32Tick_time[TIMER0] = (PRESCALE_256 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T0_PSC_1024 == gau8Timer_PSC[TIMER0])
			{
				gau32Tick_time[TIMER0] = (PRESCALE_1024 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else
			{
				/* Handling of wrong Prescale */
				u8Execution_indication = TIMER_E_WRONG_PSC ;
			}
		} 
		else if (TIMER1 == pstTimer_cfg -> u8Channel)
		{
			/*
			*	Passing the Timer Prescale to its static variable 
			*/
			
			gau8Timer_PSC[TIMER1] = (pstTimer_cfg -> u8PSC) ;
			
			/*
			*	Checking the desired Mode if it's polling or interrupt
			*/
			if (INTERRUPT == pstTimer_cfg -> u8Interrupt_mode)
			{
				TOCR_1A = MAX_TCNT1_NUMBER ;
				
				Enable_GlobalInterrupt() ;  /*Enable global interrupt*/

				/*
				*	Passing the Timer mode to its static variable 
				*/
				gau8Timer_Mode[TIMER1] = INTERRUPT ;
				TIMASK |= (1 << T1_OCIEA) ; /*Enable the interrupt request for timer 1 overflow*/
			}
			else if(POLLING == pstTimer_cfg -> u8Interrupt_mode)
			{
				TIMASK &= ~(1 << T1_OCIEA) ; /*Disable the interrupt request for timer 1 overflow*/
				
				/*
				*	Passing the Timer mode to its static variable 
				*/
				gau8Timer_Mode[TIMER1] = POLLING ;
			}
			else
			{
				/*Handling of entering wrong Mode*/
				u8Execution_indication = TIMER_E_WRONG_INTERRUPT_MODE ;
			}
			
			/*
			*	Activating CTC mode
			*/
			TCCR_1B |= (1 << T1_WGM12);
			
			/*
			*	Calculating the time per tick and passing it to a static variable
			*/
			
			if (T1_PSC_0 == gau8Timer_PSC[TIMER1])
			{
				gau32Tick_time[TIMER1] = (PRESCALE_0 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T1_PSC_8 == gau8Timer_PSC[TIMER1])
			{
				gau32Tick_time[TIMER1] = (PRESCALE_8 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T1_PSC_64 == gau8Timer_PSC[TIMER1])
			{
				gau32Tick_time[TIMER1] = (PRESCALE_64 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T1_PSC_256 == gau8Timer_PSC[TIMER1])
			{
				gau32Tick_time[TIMER1] = (PRESCALE_256 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T1_PSC_1024 == gau8Timer_PSC[TIMER1])
			{
				gau32Tick_time[TIMER1] = (PRESCALE_1024 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else
			{
				/*Handling of wrong Prescale*/
				u8Execution_indication = TIMER_E_WRONG_PSC ;
			}
		}
		else if(TIMER2 == pstTimer_cfg -> u8Channel)
		{
			/*
			*	Passing the Timer Prescale to its static variable 
			*/
			
			gau8Timer_PSC[TIMER2] = (pstTimer_cfg -> u8PSC) ;
			
			/*
			*	Checking the desired Mode if it's polling or interrupt
			*/
			if (INTERRUPT == pstTimer_cfg -> u8Interrupt_mode)
			{
				Enable_GlobalInterrupt() ;  /*Enable global interrupt*/
				
				/*
				*	Passing the Timer mode to its static variable 
				*/
				gau8Timer_Mode[TIMER2] = INTERRUPT ;
				TIMASK |= (1 << T2_OVIE) ; /*Enable the interrupt request for timer 2 overflow*/
			}
			else if(POLLING == pstTimer_cfg -> u8Interrupt_mode)
			{
				TIMASK &= ~(1 << T2_OVIE) ;/*Disable the interrupt request for timer 2 overflow*/
				
				/*
				*	Passing the Timer mode to its static variable 
				*/
				gau8Timer_Mode[TIMER2] = POLLING ;
			}
			else
			{
				/*Handling of entering wrong Mode*/
				u8Execution_indication = TIMER_E_WRONG_INTERRUPT_MODE ;
			}
			
			/*
			*	Calculating the time per tick and passing it to a static variable
			*/
			
			if (T2_PSC_0 == gau8Timer_PSC[TIMER2])
			{
				gau32Tick_time[TIMER2] = (PRESCALE_0 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T2_PSC_8 == gau8Timer_PSC[TIMER2])
			{
				gau32Tick_time[TIMER2] = (PRESCALE_8 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T2_PSC_32 == gau8Timer_PSC[TIMER2])
			{
				gau32Tick_time[TIMER2] = (PRESCALE_32 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T2_PSC_64 == gau8Timer_PSC[TIMER2])
			{
				gau32Tick_time[TIMER2] = (PRESCALE_64 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T2_PSC_128 == gau8Timer_PSC[TIMER2])
			{
				gau32Tick_time[TIMER2] = (PRESCALE_128 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T2_PSC_256 == gau8Timer_PSC[TIMER2])
			{
				gau32Tick_time[TIMER2] = (PRESCALE_256 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else if(T2_PSC_1024 == gau8Timer_PSC[TIMER2])
			{
				gau32Tick_time[TIMER2] = (PRESCALE_1024 * 1000u) / FREQ_OVER_MICRO ; /* Multiplication by 1000 is to make the time in nano seconds instead of micro*/
			}
			else
			{
				/*Handling of wrong Prescale*/
				u8Execution_indication = TIMER_E_WRONG_PSC ;
			}
		}
		else
		{
			/* Handling of entering wrong channel */
			u8Execution_indication = TIMER_E_WRONG_CHANNEL ;
		}
			
	} 
	else
	{
		/*Handling of passing null pointer*/
		u8Execution_indication = TIMER_E_NULL_POINTER ;
	}
	
	if (TIMER_E_OK == u8Execution_indication)
	{
		gu8Is_timer_init = TIMER_INITIALIZED ;
	} 
	else
	{
		/*
		*	Do nothing
		*/
	}
	
	return u8Execution_indication ;
}

/** 
 * \brief Timer_Start : A function that makes a particular timer (u8Channel) give a particular time (u32Ticks) 
 *
 * \param u8Channel (Input) : The desired timer to be started
 * \param u32Ticks (Input) : The desired ticks to be counted
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Start(u8 u8Channel , u16 u16Ticks)
{
	/*
	*	Declaration and definition of the variable that will hold the execution indication
	*/
	Error u8Execution_indication = TIMER_E_OK ;
	
	if (TIMER_INITIALIZED == gu8Is_timer_init)
	{
		if (TIMER0 == u8Channel)
		{
			if (u16Ticks <= MAX_TCNT0_NUMBER)
			{
				/*
				*	Restarting the desired timer with the predefined prescale 
				*/
				Timer_Ignite(TIMER0);
		
				/*
				*	Load the desired number of ticks to TCNT register
				*/
				TCNT_0 = MAX_TCNT0_NUMBER - (u8) u16Ticks ;
		
			} 
			else
			{
				/*Handling of entering tick number more than the maximum allowed*/
				u8Execution_indication = TIMER_E_NUMBER_OF_ENTERED_TICKS_EXCEEDED ;
			}
		
		} 
		else if(TIMER1 == u8Channel)
		{
			if (u16Ticks <= MAX_TCNT1_NUMBER)
			{
				TCNT_1 = 0 ;
			
				/*
				*	Restarting the desired timer with the predefined prescale 
				*/
				Timer_Ignite(TIMER1);
			
			
				/*
				*	Load the desired number of ticks to TCNT register
				*/
				TOCR_1A = u16Ticks ;
			
			} 
			else
			{
				/*Handling of entering tick number more than the maximum allowed*/
				u8Execution_indication = TIMER_E_NUMBER_OF_ENTERED_TICKS_EXCEEDED ;
			}
		}
		else if(TIMER2 == u8Channel)
		{
			if (u16Ticks <= MAX_TCNT2_NUMBER)
			{
				/*
				*	Restarting the desired timer with the predefined prescale 
				*/
				Timer_Ignite(TIMER2);
		
				/*
				*	Load the desired number of ticks to TCNT register
				*/
				TCNT_2 = MAX_TCNT2_NUMBER - (u8) u16Ticks ;
		
			} 
			else
			{
				/*Handling of entering tick number more than the maximum allowed*/
				u8Execution_indication = TIMER_E_NUMBER_OF_ENTERED_TICKS_EXCEEDED ;
			}
		}
		else
		{
			/*Handling of entering the wrong channel*/
			u8Execution_indication = TIMER_E_WRONG_CHANNEL ;
		}
	} 
	else
	{
		/*
		*	Handling of using the module before initializing it
		*/
		u8Execution_indication = TIMER_E_NOT_INITIALIZED_YET ;
	}
	
	/* Return the execution indication if it's ok or not */
	return u8Execution_indication ;
	
}


/** 
 * \brief Timer_Stop : A function that stops the clock of a particular timer (Channel)
 *
 * \param u8Channel : The desired timer to be stopped
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/ 
extern Error Timer_Stop(u8 u8Channel)
{
	Error u8Execution_indication = TIMER_E_OK ;
	
	if (TIMER_INITIALIZED == gu8Is_timer_init)
	{
		if (TIMER0 == u8Channel)
		{
			TCCR_0 &= ~(1 << T0_CS00);
			TCCR_0 &= ~(1 << T0_CS01);
			TCCR_0 &= ~(1 << T0_CS02);
			TCNT_0= 0 ;
		}
		else if(TIMER1 == u8Channel)
		{
			TCCR_1B &= ~(1 << T1_CS10);
			TCCR_1B &= ~(1 << T1_CS11);
			TCCR_1B &= ~(1 << T1_CS12);
			TCNT_1L = 0 ;
			TCNT_1H = 0 ;
		}
		else if(TIMER2 == u8Channel)
		{
			TCCR_2 &= ~(1 << T2_CS20);
			TCCR_2 &= ~(1 << T2_CS21);
			TCCR_2 &= ~(1 << T2_CS22);
			TCNT_2= 0 ;
		}
		else
		{
			/*Handling of entering a wrong channel*/
			u8Execution_indication = TIMER_E_WRONG_CHANNEL ;
		}
	} 
	else
	{
		/*
		*	Handling of using the module before initializing it
		*/
		u8Execution_indication = TIMER_E_NOT_INITIALIZED_YET ;
	}
	
	
	return u8Execution_indication ;
}

/** 
 * \brief Timer_reset : A function that reset a chosen timer
 *
 * \param u8Channel (Input) : Timer channel to be reset 
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Reset(u8 u8Channel) 
{
	Error u8Execution_indication = TIMER_E_OK ;
	
	if (TIMER_INITIALIZED == gu8Is_timer_init)
	{
		if (TIMER0 == u8Channel)
		{
			TCNT_0= 0 ;
		}
		else if(TIMER1 == u8Channel)
		{
			TCNT_1 = 0 ;
		}
		else if(TIMER2 == u8Channel)
		{
			TCNT_2= 0 ;
		}
		else
		{
			/*Handling of entering a wrong channel*/
			u8Execution_indication = TIMER_E_WRONG_CHANNEL ;
		}
	} 
	else
	{
		/*
		*	Handling of using the module before initializing it
		*/
		u8Execution_indication = TIMER_E_NOT_INITIALIZED_YET ;
	}
	
	
	return u8Execution_indication ;
}

/** 
 * \brief Timer_Get_Tick_Time : A function that calculates the time per tick for a particular timer , the time is returned in nano second
 *								
 * \param Timer_channel (Input) : Timer channel used
 * \param *Timer_time (Output) : The value of the timer per tick will be returned into that pointer
 * \return u8 : An 8-bit variable that will hold the indication of the execution
 *
 **/     
extern Error Timer_Get_Tick_Time(u8 u8Channel, u32 *pu32Timer_time_ns)
{
	Error u8Execution_indication = TIMER_E_OK ;
	
	if (TIMER_INITIALIZED == gu8Is_timer_init)
	{
		/* Checking that the passed pointer is not a null one */
		if (pu32Timer_time_ns != 0 )
		{
			if (TIMER0 == u8Channel)
			{
				*pu32Timer_time_ns = gau32Tick_time[TIMER0] ;
			}
			else if(TIMER1 == u8Channel)
			{
				*pu32Timer_time_ns = gau32Tick_time[TIMER1] ;
			}
			else if(TIMER2 == u8Channel)
			{
				*pu32Timer_time_ns = gau32Tick_time[TIMER2] ;
			}
			else
			{
				/*Handling of entering a wrong channel*/
				u8Execution_indication = TIMER_E_WRONG_CHANNEL ;
			}
		}
		else
		{
			/* Handling of entering null pointer */
			u8Execution_indication = TIMER_E_NULL_POINTER ;
		}
	} 
	else
	{
		/*
		*	Handling of using the module before initializing it
		*/
		u8Execution_indication = TIMER_E_NOT_INITIALIZED_YET ;
	}
	
	return u8Execution_indication ;
}




