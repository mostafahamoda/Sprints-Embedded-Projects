/*
 * EXTERNAL_INTERRUPT.c
 *
 * Created: 1/11/2020 5:22:51 PM
 *  Author: mostafahamoda1995
 */ 

#include "EXT_INT.h"

extern void EXT_INT_INIT(u8 u8Int_channel,u8 u8Int_Edge)
{
	/*
	* Setting the Global Interrupt Bit
	*/
	SET_BIT(SREG_EXT_INT_REG,I_EXT_INT) ;
	/*
	* State Machine for the Interrupt Used 
	*/
	if(u8Int_channel == INT_ZERO)
	{
		if(u8Int_Edge == RISING_EDGE)
		{
			SET_BIT(GICR_REG,INT0) ;
			MCUCR_REG |= ((1<<ISC00) | (1<<ISC01)) ;	
		}	
		else if(u8Int_Edge == FALLING_EDGE)
		{
			SET_BIT(GICR_REG,INT0) ;
			//MCUCR_REG |= ((0<<ISC00) | (1<<ISC01)) ;
			SET_BIT(MCUCR_REG,ISC01) ;
			CLEAR_BIT(MCUCR_REG,ISC00) ;
		}
		else if(u8Int_Edge == ANY_EDGE)
		{
			SET_BIT(GICR_REG,INT0) ;
			//MCUCR_REG |= ((1<<ISC00)|(0<<ISC01)) ;
			CLEAR_BIT(MCUCR_REG,ISC01) ;
			SET_BIT(MCUCR_REG,ISC00) ;
		}
	}	
	else if(u8Int_channel == INT_ONE)
	{
		if(u8Int_Edge == RISING_EDGE)
		{
			SET_BIT(GICR_REG,INT1) ;
			//MCUCR_REG |= ((1<<ISC10)|(1<<ISC11)) ;
			SET_BIT(MCUCR_REG,ISC10) ;
			SET_BIT(MCUCR_REG,ISC11) ;
		}
		else if(u8Int_Edge == FALLING_EDGE)
		{
			SET_BIT(GICR_REG,INT1) ;
			//MCUCR_REG |= ((0<<ISC10)|(1<<ISC11)) ;
			CLEAR_BIT(MCUCR_REG,ISC10) ;
			SET_BIT(MCUCR_REG,ISC11) ;
		}
		else if(u8Int_Edge == ANY_EDGE)
		{
			SET_BIT(GICR_REG,INT1) ;
			//MCUCR_REG |= ((1<<ISC10)|(0<<ISC11)) ;
			CLEAR_BIT(MCUCR_REG,ISC11) ;
			SET_BIT(MCUCR_REG,ISC10) ;
		}
		
	}
	else if(u8Int_channel == INT_TWO)
	{
		if(u8Int_Edge == RISING_EDGE)
		{
			SET_BIT(GICR_REG,INT2) ;
			SET_BIT(MCUCSR_REG,ISC2) ;
		}
		else if(u8Int_Edge == FALLING_EDGE)
		{
			SET_BIT(GICR_REG,INT2) ;
			CLEAR_BIT(MCUCSR_REG,ISC2) ;
		}
	}
	/*
	* Remember that the INTF0 , 1 , 2 Flags in the GIFR are Cleared Automatically after
	* the ISR is Executed but you ought to Clear it by Setting it 
	*/
}

