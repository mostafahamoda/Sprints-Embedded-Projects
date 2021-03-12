/*
 * EXT_INT.c
 *
 * Created: 4/6/2020 1:49:23 AM
 * Author : mostafahamoda1995
 */ 
#include "EXT_INT.h"
#include "avr/io.h"
#include "avr/interrupt.h"
volatile int hamo = 0 ;
ISR(INT2_vect)
{
	if(hamo == 0)
	{
	DDRB = 0xFF;
	PORTB = 0xF0 ;
	hamo = 1 ;
	}
	else
	{
		PORTB = 0x00 ;
		hamo = 0 ;
	}
}

int main(void)
{
    /* Replace with your application code */
	/*
	sei();
	SET_BIT(GICR_REG,INT0) ;
	MCUCR_REG |= ((1<<ISC00) | (1<<ISC01)) ;
	*/
	EXT_INT_INIT(INT_TWO,RISING_EDGE);
    while (1) 
    {
    }
}

