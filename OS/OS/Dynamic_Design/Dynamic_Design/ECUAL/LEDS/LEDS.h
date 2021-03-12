/*
 * LEDS.h
 *
 * Created: 12/15/2019 6:25:06 PM
 *  Author: A.Elkady
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#include "DIO.h"
#include "Delay.h"

/*
*	Used macros
*/
#define LED1_PIN B4
#define LED2_PIN B5
#define LED3_PIN B6
#define LED4_PIN B7


/** 
 * \brief Init_LEDS : Init the pins of the LEDS
 *
 * \param void
 * \return u8 : Indication of the execution if it fails or not 
 *
 **/     
extern Error Init_LEDS(void);

/** 
 * \brief LED1_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/     
extern Error LED1_Toggle(void);

/** 
 * \brief LED2_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/
extern Error LED2_Toggle(void);

/** 
 * \brief LED3_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/
extern Error LED3_Toggle(void);

/** 
 * \brief LED4_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/
extern Error LED4_Toggle(void);

#endif /* LEDS_H_ */

