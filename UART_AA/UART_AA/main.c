/*
 * UART_AA.c
 *
 * Created: 12/27/2019 3:37:43 PM
 * Author : mostafahamoda1995
 */ 

#include <avr/io.h>
#define F_CPU 8000000ul 
int USART_BAUDRATE = 9600 ;
#define BAUD_PRECALE ((F_CPU/(USART_BAUDRATE * 16UL)) - 1)

int main(void)
{
    /* Replace with your application code */
	UCSRB = (1<<TXEN) ;
	UCSRC = (1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL) ;
	UBRRH = BAUD_PRECALE>>8 ;
	UBRRL = BAUD_PRECALE ;
	DDRB = 0xFF ;
	char Data  = 'A';
    while (1) 
    {
		PORTB |= (1<<4) ;
		while (!(UCSRA & (1<<UDRE)))
		{
		}
		UDR = 'A' ;
		PORTB |= (1<<5) ;
		/*
		while(!(UCSRA & (1<<RXC))){}
		PORTB = (1<<5);*/
    }
}

