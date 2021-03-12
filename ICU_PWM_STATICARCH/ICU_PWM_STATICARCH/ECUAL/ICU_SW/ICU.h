/*
 * ICU.h
 *
 * Created: 1/12/2020 8:34:37 AM
 *  Author: mostafahamoda1995
 */ 


#ifndef ICU_H_
#define ICU_H_
#include "timer.h"
#include "Common_Macros.h"
#include "EXT_INT.h"
#include "Platform_Types.h"
#include "Error_Return_ICU.h"
#include <avr/interrupt.h>
#define SIGNAL_START 0 
#define SIGNAL_END 1 
#define ICU_REQ_TIME 0.1176f
ERROR_CHECK_t ICU_Init(void) ;
u32 ICU_GetVal(void) ;
#endif /* ICU_H_ */