/*
 * SOS_cfg.c
 *
 * Created: 12/30/2019 9:56:41 PM
 *  Author: A.Elkady
 */ 

#include "SOS_cfg.h"

/*
*	Changing any of these configuration will automatically changes the configuration of SOS ( Do not forget to change the PRESCALE_VALUE in SOS_cfg.h
*   but in case of changing the timer channel you have to change the ISR vector in SOS.c ( Timer 1 is the default timer )
*/

Timer_cfg_s SOS_Config =
{
	TIMER1 , T1_PSC_1024 , TIMER_MODE , INTERRUPT
};

