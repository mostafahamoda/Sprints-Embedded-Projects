/*
 * SOS_cfg.h
 *
 * Created: 12/30/2019 9:57:01 PM
 *  Author: A.Elkady
 */ 


#ifndef SOS_CFG_H_
#define SOS_CFG_H_


/*
*	Header files inclusions
*/
#include "Timer.h"
#include "SOS.h"

/*
*	Used macros
*/
#define SOS_BUFFER_SIZE 10u
#define PRESCALE_VALUE 1024u

/*
*	extern of the used timer configuration
*/
extern Timer_cfg_s SOS_Config ;




#endif /* SOS_CFG_H_ */