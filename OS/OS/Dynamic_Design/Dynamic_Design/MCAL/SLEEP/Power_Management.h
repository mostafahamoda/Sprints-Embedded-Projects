/*
 * Power_Management.h
 *
 * Created: 12/15/2019 1:17:22 AM
 *  Author: A.Elkady
 */ 


#ifndef POWER_MANAGEMENT_H_
#define POWER_MANAGEMENT_H_

#include <avr/sleep.h>

/*
*	Definitions of the MCU_CR bits ( Related to the power management )
*/
#define SM0 4
#define SM1 5
#define SM2 6
#define SE 7

/*
*	Definition of the register MCU_CR who has the bits that control the power of the micro controller
*/
#define MCU_CR ( *((volatile unsigned char *) (0x55) ) )

/** 
 * \brief CPU_Sleep : A function that puts the micro controller into sleep mode ( Power save mode )
 *
 * \param void
 * \return void
 *
 **/     
extern void CPU_Sleep();

/** 
 * \brief CPU_WakeUp : A function that disables the sleep modes
 *
 * \param void
 * \return void
 *
 **/     
extern void CPU_WakeUp();

#endif /* POWER_MANAGEMENT_H_ */

