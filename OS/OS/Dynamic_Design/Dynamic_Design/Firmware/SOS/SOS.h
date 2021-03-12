/*
 * SOS.h
 *
 * Created: 12/30/2019 9:56:49 PM
 *  Author: A.Elkady
 */ 


#ifndef SOS_H_
#define SOS_H_

/*
*	Header files inclusions
*/
#include "Timer.h"
#include "SOS_cfg.h"
#include "avr/interrupt.h"
#include "SOS_Ret_Val.h"
#include "Power_Management.h"

/*
*	Used macros
*/
#define READY 0u
#define WAITING 1u
#define RUNNING 1u

#define PERIODIC 0u
#define ONE_SHOT 1u

#define NO 0u
#define YES 1u

#define RESTART_SYSTEM_TICK_VALUE 1000000ul

/*
*	Typedef for a pointer to function
*/
typedef Error (*pfunc_SOS_Callback)(void) ;

/** 
 * \brief SOS_Init 
 *
 * \param u8Resoltuion (Input) : The desired resolution in microseconds
 * \return u8 : Indication of the execution if it fails or not
 *
 * Constrains when using Timer1 (Default) at (1024 PSC) : The minimum resolution allowed is 128 micro seconds
 *												The maximum resolution allowed is 8000000 micro seconds
 **/       
extern Error SOS_Init(u32 u32System_tick);

/** 
 * \brief Deinitialize the used timer
 *
 * \param void
 * \return u8 : Indication of the execution if it fails or not
 *
 **/     
extern Error SOS_Deinit(void);

/** 
 * \brief SOS_Create_Task : Adds a certain function with a certain interval as an event
 *
 * \param pfunc (Input) : A pointer to the function that is desired to be executed 
 * \param u32System_ticks_number (Input) : The delay time before executing the desired function
 * \param u8Periodicity (Input) : Tells if the user wants to execute this function periodically or one shot
 * \param u8Priority (Input) : Determine the priority of the desired task to be run (0 is the lowest priority)
 * \return  u8 : Indication of the execution if it fails or not 
 *
 **/     
extern Error SOS_Create_Task(pfunc_SOS_Callback pfunc , u32 u32System_ticks_number , u8 u8Periodicity , u8 u8Priority) ;

/** 
 * \brief SOS_Delete_Task : Stops a certain event from being executed
 *
 * \param pfunc (Input) : A pointer to the function that is desired to be stopped
 * \return u8 : Indication of the execution if it fails or not 
 *
 **/     
extern Error SOS_Delete_Task(pfunc_SOS_Callback pfunc) ;

/** 
 * \brief SOS_Run : The manager of the SOS
 *
 * \param void
 * \return u8 : Indication of the execution if it fails or not 
 *
 **/     
extern void SOS_Run(void) ;
#endif /* SOS_H_ */