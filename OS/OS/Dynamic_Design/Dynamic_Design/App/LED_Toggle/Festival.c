/*
 * Festival.c
 *
 * Created: 12/15/2019 3:12:28 AM
 *  Author: A.Elkady
 */ 

#include "Festival.h"

/** 
 * \brief Start_Festival : Initialize The pins of the LEDS to be output
 *
 * \param void
 * \return void
 *
 **/     
extern void Start_Festival(void)
{
	/*
	*	Initializing the LEDS 
	*/
	Init_LEDS();
	/*
	*	Initialize the SOS with a certain resolution
	*/
	SOS_Init(SYSTEM_TICK_IN_MICRO);
	
	SOS_Create_Task(LED4_Toggle , 2000u , ONE_SHOT , 0);
	SOS_Create_Task(LED1_Toggle , 1000u , PERIODIC , 1);
	SOS_Create_Task(LED2_Toggle , 500u , PERIODIC , 2);
	SOS_Create_Task(LED3_Toggle , 250u , PERIODIC , 3);
	
	SOS_Run();
}

