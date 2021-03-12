/*
 * ADC_TEMP.c
 *
 * Created: 1/9/2020 9:23:05 PM
 * Author : mostafahamoda1995
 */ 


#include "ADC_Head.h"
#include "avr/io.h"
#include "LCD_head.h"

int main(void)
{
    ADC_vInit_manual(8) ;
	LCD_vInit() ;
	char Read ;
    while (1) 
    {
		Read = ADC_vRead_manual_8bits() ;
		LCD_vPrintchar(Read) ;
    }
}

