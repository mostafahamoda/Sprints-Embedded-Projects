/*
 * TIMER_Ret_Val.h
 *
 * Created: 12/16/2019 8:00:15 PM
 *  Author: A.Elkady
 */ 


#ifndef TIMER_RET_VAL_H_
#define TIMER_RET_VAL_H_

/*
*	Errors definition
*/
#define TIMER_E_OK                                 (Error)0

#define TIMER_E_NULL_POINTER                       (Error)1

#define TIMER_E_WRONG_CHANNEL                      (Error)2

#define TIMER_E_WRONG_PSC                          (Error)3

#define TIMER_E_WRONG_INTERRUPT_MODE               (Error)4

#define TIMER_E_NUMBER_OF_ENTERED_TICKS_EXCEEDED   (Error)5

#define TIMER_E_NOT_INITIALIZED_YET                (Error)6

#define TIMER_INITIALIZED                          (Error)7

#endif /* TIMER_RET_VAL_H_ */