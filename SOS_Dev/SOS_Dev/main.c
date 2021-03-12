/*
 * Timer_StaticArch.c
 *
 * Created: 11/23/2019 2:22:39 AM
 *  Author: mostafahamoda1995
 */ 
#define F_CPU 8000000ul
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "timer.h"
#include "LCD_head.h"
#include "SOS.h"
int main(void)
{
	sei() ;
	DDRB = 0xFF ;
	LCD_vInit() ;
	void (*ptr)(char)  = (&LCD_vPrintchar) ; 
	Sos_Init(0,1000) ;
	Sos_Create_Task(1,ptr,0,1,1) ;
	Sos_Create_Task(5,ptr,1,1,2) ;
	/*Function for Writing on the LCD*/
    while(1)
    {
        //TODO:: Please write your application code 
		Scheduler() ;
		//_delay_ms(500);
    }
}