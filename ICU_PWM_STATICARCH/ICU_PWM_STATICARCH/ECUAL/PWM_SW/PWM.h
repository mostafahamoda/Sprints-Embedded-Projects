/*
 * PWM.h
 *
 * Created: 1/22/2020 11:09:20 AM
 *  Author: mostafahamoda1995
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "timer.h"
#include "avr/io.h"
#include "Platform_Types.h"
#include "Common_Macros.h"
#include "Error_Return_PWM.h"
#define HIGH 1 
#define LOW 0 
#define ULTRASONIC_W 0.05f
extern ERROR_CHECK_t PWM_STEP(u8 u8_Pin,u8 u8_Duty);
extern ERROR_CHECK_t SEND_PULSE(void);

#endif /* PWM_H_ */