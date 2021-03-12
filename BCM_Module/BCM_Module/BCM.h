/*
 * BCM.h
 *
 * Created: 12/24/2019 7:12:00 AM
 *  Author: mostafahamoda1995
 */ 
#ifndef BCM_H_
#define BCM_H_
#include "Error_RetVal.h"
#include "uart.h"
#include "STD_TYPES.h"
#define DATA_BITS 8
#define LOCKED 1 
#define UNLOCKED 0 
typedef signed int BCM_STATE ;
typedef struct {
	uint32_t BaudRate ;
	uint16_t Data_length ;
	uint32_t Address ;
	uint32_t ID ;
} strBCM_Cfg ;

#define IDLE  0
#define SENDING_BYTE 1
#define SENDING_COMPLETE 2 
#define FRAME_COMPLETE 3
#define FRAME_SIZE 3
BCM_ERROR BCM_Send(uint32_t ID) ;
BCM_STATE BCM_DISPATCHER(void) ;
BCM_ERROR BCM_Init(strBCM_Cfg* BCM_Config) ;
BCM_ERROR BCM_Setup_RX(uint32_t *Address_RX) ;
BCM_ERROR BCM_DISPATCHER_RX(void) ;
#endif /* BCM_H_ */