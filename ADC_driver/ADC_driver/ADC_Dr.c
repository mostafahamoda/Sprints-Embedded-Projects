/*
 * ADC_Dr.c
 *
 * Created: 12/29/2018 11:33:27 AM
 *  Author: mostafahamoda1995
 */ 
# include "ADC_h1.h"
# include <avr/io.h> 
# include <avr/interrupt.h>


void ADC_vInit(void)
{
	/*choose Vref*/
	SET_BIT(ADMUX,REFS0) ;
	/*Enable ADC*/
	SET_BIT(ADCSRA,ADEN) ;
	/*Select Clock / 64*/
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	/**/
}

unsigned short ADC_u16Read(void) 
{
	unsigned short temp  ;
	/*Start conversion*/
	SET_BIT(ADCSRA,ADSC) ;
	/*check ADIF*/                 // your ADC COnverter reg will not 
	while((READ_BIT(ADCSRA,ADIF) == 0)) 
	{
      /* DO NOTHING */
	}
	/*ptr = & val ;
	*(ptr) = ADCH ;
	*(ptr+1) = ADCL ;*/
	temp = ADCL ;
	temp |= (unsigned short) (ADCH<<8) ;
	return temp ;
}