/*
 * BCM_Module.c
 *
 * Created: 12/24/2019 7:05:47 AM
 * Author : mostafahamoda1995
 */ 


#include "uart.h"
#include "BCM.h"
#define F_CPU 8000000ul
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	//LCD_vInit();
	char Arr[10] = {1,2,3,4,5,6,7,8,9,9} ;
	//LCD_vPrintchar('H') ;
	strBCM_Cfg CONFIG ;
	CONFIG.Address = &Arr ;
	CONFIG.BaudRate = 9600 ;
	CONFIG.Data_length = 10 ;
	CONFIG.ID = 0x15 ;
	BCM_Init(&CONFIG) ;
	BCM_Send(0x01) ;
	DDRB = 0xff ;
    while (1) 
    {
		BCM_DISPATCHER();
		_delay_ms(10) ;		
    }
}

