/*
 * ADC_C.c
 *
 * Created: 3/5/2019 4:32:34 PM
 *  Author: mostafahamoda1995
 */ 
#include <avr/io.h>
#define F_CPU 8000000ul 
#include "ADC_Head.h"
#include "Key_pad_1.h"
#include "util/delay.h"

void ADC_vInit_manual(char x) 
{
	// choosing the Input clock source for the prescalar 
	// and power source
	SET_BIT(ADMUX,REFS0) ;
	CLR_BIT(ADMUX,REFS1) ;
	// choosing the Left-Adjusted ADC Storing technique
	if(x == 8)
	{
	SET_BIT(ADMUX,ADLAR) ;
	}	
	// Choosing which Analog input channed you are wiiling to use (adc0)
	/*SET_BIT(ADMUX,MUX0) ;
	SET_BIT(ADMUX,MUX1) ;
	SET_BIT(ADMUX,MUX2) ;
	CLR_BIT(ADMUX,MUX3) ;
	CLR_BIT(ADMUX,MUX4) ;*/
	// Enabling the ADCEN bit in ADCSRA reg 
	SET_BIT(ADCSRA,ADEN) ;
	// Setting the prescalar value 64
	SET_BIT(ADCSRA,ADPS2) ;
	SET_BIT(ADCSRA,ADPS1) ;
	CLR_BIT(ADCSRA,ADPS0) ;
	/**/
	
}

uint16 ADC_vRead_manual(void) 
{
	uint16 temp ;
	// Start Conversion using the ADC by setting the ADSC
	SET_BIT(ADCSRA,ADSC) ;
	// checking the conversion flag 
	while((READ_BIT(ADCSRA,ADIF)) == 0)
	{
		// Do Nothing 	
	}
	
	temp = ADCL ;
	temp |= (unsigned short) (ADCH<<8) ;
	return temp ;
	
			
}

char ADC_vRead_manual_8bits(void)
{
	char temp ;
	// Start Conversion using the ADC by setting the ADSC
	SET_BIT(ADCSRA,ADSC) ;
	// checking the conversion flag
	while((READ_BIT(ADCSRA,ADIF)) == 0)
	{
		// Do Nothing
	}
	temp = ADCH ;
	
}