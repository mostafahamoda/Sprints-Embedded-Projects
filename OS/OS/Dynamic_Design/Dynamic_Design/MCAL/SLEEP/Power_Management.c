/*
 * Power_Management.c
 *
 * Created: 12/15/2019 1:17:34 AM
 *  Author: A.Elkady
 */ 

#include "Power_Management.h"

/** 
 * \brief CPU_Sleep : A function that puts the micro controller into sleep mode ( Power save mode )
 *
 * \param void
 * \return void
 *
 **/ 
extern void CPU_Sleep()
{
	/*
	*	Enable the sleep modes
	*/
	MCU_CR |= (1 << SE);
	
	/*
	*	Enable power save mode
	*/
	MCU_CR |= (1 << SM0);
	MCU_CR |= (1 << SM1);
	
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_mode();
}

/** 
 * \brief CPU_WakeUp : A function that disables the sleep modes
 *
 * \param void
 * \return void
 *
 **/
extern void CPU_WakeUp()
{
	/*
	*	Enable the sleep modes
	*/
	MCU_CR &= ~(1 << SE);
}

