/*
 * Interrupt.c
 *
 * Created: 11/23/2019 12:07:33 AM
 *  Author: A.Elkady
 */ 

/*
*	header files inclusions
*/
#include "Interrupt.h"

/** 
 * \brief Enable_Global_Interrupt : A function that enable the global interrupt 
 *
 * \param void
 * \return void
 *
 **/ 
extern void Enable_GlobalInterrupt()
{
	S_REG |= (1 << GI);
}

/** 
 * \brief Disable_Global_Interrupt : A function that disable the global interrupt 
 *
 * \param void
 * \return void
 *
 **/
extern void Disable_GlobalInterrupt()
{
	S_REG &= ~(1 << GI);
}