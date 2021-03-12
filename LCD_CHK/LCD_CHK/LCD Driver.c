/*
 * LCD_Driver.c
 *
 * Created: 12/22/2018 9:58:51 AM
 *  Author: mostafahamoda1995
 */ 

#include <avr/io.h>
#define F_CPU 8000000ul
#include "LCD_head.h"
#include <util/delay.h>

int main(void)
{
	LCD_vInit() ;
	//LCD_vPrintchar('A') ;
	char * ptr = "hussam lovers <3" ;
	LCD_vPrintstring(ptr) ;
    while(1)
    {
        
    }
}