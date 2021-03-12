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
extern i_count_RX ;
int main(void)
{
    /* Replace with your application code */
	//LCD_vInit();
	char Arr[13] ={0}  ;
	//LCD_vPrintchar('H') ;
	strBCM_Cfg CONFIG ;
	CONFIG.Address = &Arr ;
	CONFIG.BaudRate = 9600 ;
	CONFIG.Data_length = 10 ;
	CONFIG.ID = 0x15 ;
	BCM_Init(&CONFIG) ;
	//BCM_Send(0x01) ;
	DDRA = 0xff ;
	BCM_Setup_RX(&Arr,13) ;
	int i ;
    while (1) 
    {
		if(i_count_RX<13)
		{
		BCM_DISPATCHER_RX();
		}		
		else 
		{
			for(i=0;i<13;i++)
			{
				PORTA = Arr[i]	;
			}
			_delay_ms(1000) ;	
		}
    }
}

