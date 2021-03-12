/*
 * dio.h
 *
 *  Created on: Nov 23, 2019
 *      Author: Mario
 */

#ifndef DIO_H_
#define DIO_H_


#include "common_macros.h"
#include "dio_config.h"
#include "STD_TYPES.h"




extern uint8_t DIO_WRITE_PIN (uint8_t u8Pin_Number,uint8_t u8Value );
extern uint8_t DIO_INIT_Pin (uint8_t u8Pin_Number,uint8_t u8State);
extern uint8_t DIO_PIN_READ (uint8_t u8Pin_Number,uint8_t* pu8Reading );

extern uint8_t DIO_WRITE_PORT (uint8_t u8Port_Number,uint8_t u8Value);
extern uint8_t DIO_INIT_PORT (uint8_t u8Port_Number,uint8_t u8State);
extern uint8_t DIO_PORT_READ (uint8_t u8Port_Number,uint8_t* u8Reading);

extern uint8_t DIO_PIN_ACTIVATE_PULL_UP(uint8_t u8Pin_Number );
extern uint8_t DIO_PORT_ACTIVATE_PULL_UP(uint8_t u8Port_Number );


#endif /* DIO_H_ */
