/*
 * Festival.h
 *
 * Created: 12/15/2019 3:12:46 AM
 *  Author: A.Elkady
 */ 


#ifndef FESTIVAL_H_
#define FESTIVAL_H_

/*
*	Header files inclusions
*/	
#include "DIO.h"
#include "SOS.h"
#include "Power_Management.h"
#include "LEDS.h"

/*
*	Used macros
*/
#define SYSTEM_TICK_IN_MICRO 1000u

/** 
 * \brief Start_Festival : Starts the ceremony ...!!
 *
 * \param void
 * \return void
 *
 **/     
extern void Start_Festival(void);

#endif /* FESTIVAL_H_ */