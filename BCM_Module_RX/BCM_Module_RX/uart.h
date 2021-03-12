 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mario
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#define F_CPU 8000000ul
#include "common_macros.h"
#include "STD_TYPES.h"
#include "Error_RetVal.h"
#include "dio.h"
/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE_DOUBLE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)
#define BAUD_PRESCALE_SINGLE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
//#define BAUD_PRESCALE_DOUBLE 1	
//#define BAUD_PRESCALE_SINGLE 1
/**************FULLDUPLEX OR HALFDUPLEX **********************/
#define FULL_DUPLEX 0
#define TRANSIMETER 1
#define RECEIVER	2
/*************SPEED MODE**************************************/
#define NORMAL_SPEED 0
#define DOUBLE_SPEED 1
/*************SYNCHRONOUS OR ASYNCHRONOUS*********************/
#define SYNCHRONOUS 0 
#define ASYNCHRONOUS 1
/************FRAME NUMBER OF BITS*****************************/
#define FIVE_BITS 5
#define SIX_BITS 6
#define SEVEN_BITS 7
#define EIGHT_BITS 8
#define NINE_BITS 9
/*************PARITY OPTIONS*********************************/
#define PARITY_DISABLED 0
#define EVEN_PARITY 1 
#define ODD_PARITY 2
/**************STOP BITS NUMBERS*****************************/
#define ONE_STOP 0
#define TWO_STOP 1
/*********************INTERRUPT OR POLLING**********************/
#define INTERRUPT_MODE 0
#define POLLING_MODE 1
/*******************************************************************************
						Configuration Structure 
*******************************************************************************/

typedef struct {
	uint8_t u8_SpeedMode ; 
	uint16_t u16_BaudRate ;
	uint8_t u8_Sync ;
	uint8_t u8_DataBits ;
	uint8_t u8_Parity ;
	uint8_t u8_StopBits ;
	uint8_t u8_Interrupt ;
	uint8_t u8_Duplex ;
	} strUART_Config;
	
/*******************************************************************************
						UART Registers Access 
*******************************************************************************/
# define UCSRA (*(volatile uint8_t * const)0x002B)
# define UCSRB (*(volatile uint8_t * const)0x002A)
/***************URSEL Selects Between Writing on (0)UBRRH and (1)UCSRC ********/
# define UCSRC (*(volatile uint8_t * const)0x0040)
# define UBRRH (*(volatile uint8_t * const)0x0040)
# define UBRRL (*(volatile uint8_t * const)0x0029)
# define UDR   (*(volatile uint8_t * const)0x002C)

# define SREG  (*(volatile uint8_t * const)0x005F) 
/**********************************************************************************
						Defining the Configuration Bits
***********************************************************************************/
#define I_BIT 7
/*****************UCSRA REG***************/
#define MPCM 0
#define U2X 1
#define PE 2
#define DOR 3
#define FE 4
#define UDRE 5
#define TXC 6
#define RXC 7
/********************UCSRB*************/
#define TXB8 0
#define RXB8 1
#define UCSZ2 2
#define TXEN 3
#define RXEN 4
#define UDRIE 5
#define TXCIE 6
#define RXCIE 7
/******************UCSRC******************/
#define UCPOL 0
#define UCSZ0 1
#define UCSZ1 2
#define USBS 3
#define UPM0 4
#define UPM1 5
#define UMSEL 6
#define URSEL 7
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
UART_ERROR UART_init(const strUART_Config *UART_Cfg);

UART_ERROR UART_sendByte(const uint16_t data);

UART_ERROR UART_recieveByte(uint8_t *pu8_Received_Data);

//UART_ERROR UART_sendString(const uint8_t *Str);

//UART_ERROR UART_receiveString(uint8_t *Str); // Receive until #

#endif /* UART_H_ */
