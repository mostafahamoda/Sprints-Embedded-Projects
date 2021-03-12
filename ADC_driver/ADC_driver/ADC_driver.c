/*
 * ADC_driver.c
 *
 * Created: 12/29/2018 11:31:51 AM
 *  Author: mostafahamoda1995
 */ 

# include "ADC_h1.h"
# include <avr/io.h>
# include <avr/interrupt.h>


int main(void)
{
	ADC_vInit() ;
	unsigned short val ;
	DDRD = 0xFF ;
    while(1)
    {
       val = ADC_u16Read() ;
	   PORTD = val ;
    }
}