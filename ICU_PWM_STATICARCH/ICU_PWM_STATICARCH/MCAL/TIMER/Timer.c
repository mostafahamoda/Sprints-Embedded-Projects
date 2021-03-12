/*
 * Timer.c
 *
 * Created: 11/23/2019 3:04:51 AM
 *  Author: mostafahamoda1995
 */ 

#include "timer.h"
#include "LCD_head.h"
volatile u32 Ticks ;
volatile u32 i ;
u32 Initial_ticks =  0 ;
volatile u32 Ignite_Flag_Var  ;
volatile u32 Ignite_Flag_Var_1  ;
volatile u32 Ignite_Flag_Var_2  ;


ISR(TIMER0_OVF_vect)
{
	if(Ticks != 0)
	{
		if(Ticks < (Timer0_OVF_Val))
		{
			/*Initializing the Timer Register*/
			TCNT0_Reg = Timer0_OVF_Val-Ticks;
			Ticks = 0;
		}
		else if(Ticks >= (Timer0_OVF_Val))
		{
			/*Initializing the Timer Register*/
			TCNT0_Reg = 0x00;
			Ticks = Ticks - Timer0_OVF_Val ;
		}
	}
	else if(Ticks == 0)
	{
		Ticks = Initial_ticks ;
		TCNT0_Reg = 0x00 ; 
		Ignite_Flag_Var ++ ;
	}
}
ISR(TIMER2_OVF_vect)
{
	if(Ticks != 0)
	{
		if(Ticks < (Timer2_OVF))
		{
			/*Initializing the Timer Register*/
			TCNT2_Reg = Timer2_OVF-Ticks;
			Ticks = Ticks - Ticks ;
			//LCD_vPrintchar('Hff') ;
			//PORTB = 0x00 ;
		}
		else if(Ticks >= (Timer2_OVF))
		{
			/*Initializing the Timer Register*/
			TCNT2_Reg = 0x00 ;
			Ticks = Ticks - Timer2_OVF ;
		}
	}
	else if(Ticks == 0)
	{
		Ticks = Initial_ticks ;
		TCNT2_Reg = 0x00 ;
		Ignite_Flag_Var_2 ++ ;
		CLEAR_BIT(PORTC,2) ;
		//LCD_vPrintchar(Ignite_Flag_Var_2+'0') ;
		Timer_Stop_2() ;
	}
}
/*
* Note: Timer one ISR needs modifications before using 
*/
ISR(TIMER1_OVF_vect)
{
	if(Ticks != 0)
	{
		if(Ticks < (Timer1_OVF))
		{
			/*Initializing the Timer Register*/
			TCNT1_Reg = Timer1_OVF-Ticks;
			Ticks = 0 ;
		}
		else if(Ticks >= (Timer1_OVF))
		{
			/*Initializing the Timer Register*/
			TCNT1_Reg = 0x00 ;
			Ticks = Ticks - Timer1_OVF ;
		}
	}
	else if(Ticks == 0)
	{
		Ticks = Initial_ticks ;
		TCNT1_Reg = 0x00 ;
		Ignite_Flag_Var_1 ++ ;
	}
}

void Timer_Stop_0(void)
{
	// Cutting the Source Clock
	CLEAR_BIT(TCCR0_Reg,CS02_Reg) ;
	CLEAR_BIT(TCCR0_Reg,CS01_Reg) ;
	CLEAR_BIT(TCCR0_Reg,CS00_Reg) ;
	/*Clearing Ignite_Variable*/
	Ignite_Flag_Var = 0 ;
}
void Timer_Stop_1(void)
{
	// Cutting the Source Clock
	CLEAR_BIT(TCCR1B_Reg,CS12_Reg) ;
	CLEAR_BIT(TCCR1B_Reg,CS11_Reg) ;
	CLEAR_BIT(TCCR1B_Reg,CS10_Reg) ;
	/*Clearing Ignite_Variable*/
	Ignite_Flag_Var_1 = 0 ;
}
void Timer_Stop_2(void)
{
	// Cutting the Source Clock
	CLEAR_BIT(TCCR2_Reg,CS22_Reg) ;
	CLEAR_BIT(TCCR2_Reg,CS21_Reg) ;
	CLEAR_BIT(TCCR2_Reg,CS20_Reg) ;
	/*Clearing Ignite_Variable*/
	Ignite_Flag_Var_2 = 0 ;
}
/*************************************************************************************************************************************/
									/*Timer Initialization Function*/
/*************************************************************************************************************************************/
u8 Timer_Init(Timer_Configuration_S_H* Confg_S)
{
	/*********************************************************************************************************************************/
									/*Importing the Values Stored in the Configuration Structure*/
	/*********************************************************************************************************************************/
	u8 mode = Confg_S->Mode , timer_psc = Confg_S->Timer_Psc , timer_channel = Confg_S->Timer_Channel , timer_mode = Confg_S->Timer_Mode;
	/*Setting the Pre-Scalar Values*/
	Prescaller_Timer[timer_channel] = timer_psc ;
	if(timer_channel == TIMER0)
	{
		// Wave Form Generation
		CLEAR_BIT(TCCR0_Reg,WGM00_Reg) ;
		CLEAR_BIT(TCCR0_Reg,WGM01_Reg) ;
		// Enabling the Interrupt
		SET_BIT(TIMSK_Reg,TOIE0_reg) ;
	}
	else if(timer_channel == TIMER1)
	{
		/*Clearing WGM10:11 on TCCRA First*/
		CLEAR_BIT(TCCR1A_Reg,WGM10_Reg) ;
		CLEAR_BIT(TCCR1A_Reg,WGM11_Reg) ;
		/*Clearing WGM12:13 on TCCRB*/
		CLEAR_BIT(TCCR1B_Reg,WGM12_Reg) ;
		CLEAR_BIT(TCCR1B_Reg,WGM13_Reg) ;
		/*Enabling the Overflow Interrupt*/
		SET_BIT(TIMSK_Reg,TOIE1_Reg) ;
	}
	else if(timer_channel == TIMER2)
	{
		// Wave Form Generation
		CLEAR_BIT(TCCR2_Reg,WGM20_Reg) ;
		CLEAR_BIT(TCCR2_Reg,WGM21_Reg) ;
		/// Enabling the Interrupt
		SET_BIT(TIMSK_Reg,TOIE2_reg) ;
	}
	return E_OK ;
}
/**************************************************************************************************************************************/
												/*Creating Timer Start Function */
/**************************************************************************************************************************************/
u8 Timer_Start(u8 Timer_Channel,double Required_Time)
{
	/*Declaring the Minimum Tick*/
	double  tick_min = 0 ; 
	char a1[10] = {0} ; 
	/************************************************************************/
	/* Configuring timer prescalar                                                                      
	/************************************************************************/
	if(Timer_Channel == 0)
	{
		/*Setting the Pre-Scalar Values*/
		switch (Prescaller_Timer[Timer_Channel])
		{
		case PSC_0 :
		TCCR0 |= PSC_REG_0 ;
		tick_min = (1/F_CPU_Timer) ;
		break ;
		case PSC_8 :
		TCCR0 |= PSC_REG_8 ;
		tick_min = (8/F_CPU_Timer) ;
		break ;
		case PSC_64 :
		TCCR0 |= PSC_REG_64 ;
		tick_min = (64/F_CPU_Timer) ;
		break ;
		case PSC_256 :
		TCCR0 |= PSC_REG_256 ;
		tick_min = (256/F_CPU_Timer) ;
		break ;
		case PSC_1024 :
		TCCR0 |= PSC_REG_1024 ;
		tick_min = (1024/F_CPU_Timer) ;
		break ;
		}
		/*
		* Calculating the Number of Ticks in micro-seconds to avoid Floating Point Calculations
		*/
		/*Calculating Total Number of Ticks*/
		Ticks = (Required_Time*MILLISECOND_CVG)/tick_min;
		Initial_ticks = Ticks;
		/*Ticks = Required_Time * 1000)*/
		/*Ticks = Required_Time ;*/
		/*counting the Number of Loops*/
		//u32 Loop = Ticks / Timer0_OVF ;
		u32 Loop = 0 ;
		for(i=0;i<(Loop+1);i++)
		{
		if(Ticks < Timer0_OVF_Val)
		{
			/*Initializing the Timer Register*/
			TCNT0_Reg = Timer0_OVF_Val-Ticks;
			Ticks = 0;
			/*polling on the Overflow Register  */
			//while(READ_BIT(TIFR_Reg,TOV0_Reg)==0) ;
			/*Clearing the Overflow Bit*/
			//SET_BIT(TIFR_Reg,TOV0_Reg) ; 
			break ;
		}
		else if(Ticks >= Timer0_OVF_Val)
		{
			/*Initializing the Timer Register*/
			TCNT0_Reg = 0x00 ;
			/*polling on the Overflow Register  */
			//while(READ_BIT(TIFR_Reg,TOV0_Reg) == 0) ;
			/*Clearing the Overflow Bit*/
			//SET_BIT(TIFR_Reg,TOV0_Reg) ;		
			Ticks = Ticks - Timer0_OVF_Val ;
		}			
		}
	}
	/*Timer 1 Configuration */
	else if(Timer_Channel == 1)
	{
		/*Setting the pre-Scalar */
		switch (Prescaller_Timer[Timer_Channel])
		{
		case PSC_0 :
		TCCR1B_Reg |= PSC_REG_0 ;
		tick_min = (1/F_CPU_Timer) ;
		break ;
		case PSC_8 :
		TCCR1B_Reg |= PSC_REG_8 ;
		tick_min = (8/F_CPU_Timer) ;
		break ;
		case PSC_64 :
		TCCR1B_Reg |= PSC_REG_64 ;
		tick_min = (64/F_CPU_Timer) ;
		break ;
		case PSC_256 :
		TCCR1B_Reg |= PSC_REG_256 ;
		tick_min = (256/F_CPU_Timer) ;
		break ;
		case PSC_1024 :
		TCCR1B_Reg |= PSC_REG_1024 ;
		tick_min = (1024/F_CPU_Timer) ;
		break ;
		}
		/*Calculating Total Number of Ticks*/
		Ticks=(Required_Time*1000)/tick_min ;
		u32 Loop = Ticks / Timer1_OVF ;
		/*Looping on the Timer register*/
		for(i=0;i<(Loop+1);i++)
			{
				/*Case 1*/
				if(Ticks<Timer1_OVF)
				{
					/*Timer Counter Register Initialization */
					TCNT1_Reg = Timer1_OVF-Ticks ;
					/*Checking on the Overflow Flag*/
					while(READ_BIT(TIFR_Reg,TOV1) == 0) ;
					/*Clearing the Over flow Register*/
					SET_BIT(TIFR_Reg,TOV0_Reg) ;			
					break ;
				}
				else if(Ticks >= Timer1_OVF)
				{
					/*Initializing the Counter*/
					TCNT1_Reg = 0x00 ;
					/*Polling on the Overflow Flag*/
					while(READ_BIT(TIFR_Reg,TOV1) == 0) ;
					/*Checking on the Overflow Flag*/
					SET_BIT(TIFR_Reg,TOV0_Reg) ;			
					Ticks = Ticks - Timer1_OVF ;
				}
				else
				{
					break ;
				}
			}
			Timer_Stop_1() ;		
	}
	else if(Timer_Channel == 2)
	{
		switch (Prescaller_Timer[Timer_Channel])
		{
			case PSC_0 :
			TCCR2_Reg |= PSC_REG_0 ;
			tick_min = (1/F_CPU_Timer) ;
			break ;
			case PSC_8 :
			TCCR2_Reg |= PSC_REG_8 ;
			tick_min = (8/F_CPU_Timer) ;
			break ;
			case PSC_64 :
			TCCR2_Reg |= PSC_64 ;
			tick_min = (64/F_CPU_Timer) ;
			break ;
			case PSC_256 :
			TCCR2_Reg |= PSC_REG_256 ;
			tick_min = (256/F_CPU_Timer) ;
			break ;
			case PSC_1024 :
			TCCR2_Reg |= PSC_REG_1024 ;
			tick_min = (1024/F_CPU_Timer) ;
			break ;
			default:
			tick_min = (1024/F_CPU_Timer) ;
			break;
		}
		/*Calculating Total Number of Ticks		Ticks = (Required_Time*1000) / 	tick_min ;
		u32 Loop = Ticks / Timer2_OVF ;
			for(i=0;i<Loop+1;i++)
			{
				if(Ticks < Timer2_OVF)
				{
					Timer2 Counter					TCNT2_Reg = Timer2_OVF-Ticks ;
					Polling the Overflow Flag					while(READ_BIT(TIFR_Reg,TOV2_Reg) == 0) ;
					Clearing 					SET_BIT(TIFR_Reg,TOV0_Reg) ;
					break ;			
				}
				else if(Ticks >= Timer2_OVF)
				{
					TCNT2_Reg = 0x00 ;
					while(READ_BIT(TIFR_Reg,TOV2_Reg)==0) ;			
					SET_BIT(TIFR_Reg,TOV0_Reg) ;
					Ticks = Ticks - Timer2_OVF ;
				}
				else
				{
					break ;
				}
		}
		Timer_Stop_2() ;*/
		
		Ticks = (Required_Time*MILLISECOND_CVG)/tick_min ;
		Initial_ticks = Ticks ;
		/*Ticks = Required_Time * 1000)*/
		/*Ticks = Required_Time ;*/
		/*counting the Number of Loops*/
		//u32 Loop = Ticks / Timer0_OVF ;
		u32 Loop = 1 ;
		for(i=0;i<(Loop+1);i++)
		{
			if(Ticks < Timer2_OVF)
			{
				/*Initializing the Timer Register*/
				TCNT2_Reg = Timer2_OVF-Ticks;
				Ticks = Ticks - Ticks ;
				/*polling on the Overflow Register  */
				//while(READ_BIT(TIFR_Reg,TOV0_Reg)==0) ;
				/*Clearing the Overflow Bit*/
				//SET_BIT(TIFR_Reg,TOV0_Reg) ;
				break ;
			}
			else if(Ticks >= Timer2_OVF)
			{
				/*Initializing the Timer Register*/
				TCNT2_Reg = 0x00 ;
				/*polling on the Overflow Register  */
				//while(READ_BIT(TIFR_Reg,TOV0_Reg) == 0) ;
				/*Clearing the Overflow Bit*/
				//SET_BIT(TIFR_Reg,TOV0_Reg) ;
				Ticks = Ticks - Timer2_OVF ;
			}
	}
	return E_OK ;
}
	}
/**************************************************************************************************************************************/
/*Creating Timer Stop Function */
/**************************************************************************************************************************************/

u8 Timer_Stop(u8 Timer_Channel)
{
	switch(Timer_Channel)
	{
	case 0 :
	Timer_Stop_0() ;
	case 1 : 
	Timer_Stop_1() ;
	case 2 :
	Timer_Stop_2() ;
	}
	return E_OK ;	
}