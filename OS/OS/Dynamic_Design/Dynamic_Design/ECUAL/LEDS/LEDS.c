/*
 * LEDS.c
 *
 * Created: 12/15/2019 6:25:13 PM
 *  Author: A.Elkady
 */ 

#include "LEDS.h"

/** 
 * \brief Init_LEDS : Init the pins of the LEDS
 *
 * \param void
 * \return u8 : Indication of the execution if it fails or not 
 *
 **/     
extern Error Init_LEDS(void)
{
	DIO_Pin_Init(LED1_PIN,OUTPUT);
	DIO_Pin_Init(LED2_PIN,OUTPUT);
	DIO_Pin_Init(LED3_PIN,OUTPUT);
	DIO_Pin_Init(LED4_PIN,OUTPUT);
	
	return 0;
}

/** 
 * \brief LED1_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/     
extern Error LED1_Toggle(void)
{
	DIO_Pin_Toggle(LED1_PIN);
	_delay_ms(20);
	return 0 ;
}

/** 
 * \brief LED2_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/     
extern Error LED2_Toggle(void)
{
	DIO_Pin_Toggle(LED2_PIN);
	_delay_ms(20);
	return 0 ;
}

/** 
 * \brief LED3_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/     
extern Error LED3_Toggle(void)
{
	DIO_Pin_Toggle(LED3_PIN);
	_delay_ms(20);
	return 0 ;
}

/** 
 * \brief LED4_Toggle
 *
 * \param void
 * \return u8 : Indication to the execution
 *
 **/     
extern Error LED4_Toggle(void)
{
	DIO_Pin_Toggle(LED4_PIN);
	_delay_ms(20);
	return 0 ;
}