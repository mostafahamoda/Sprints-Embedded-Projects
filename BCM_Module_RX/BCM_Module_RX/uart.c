 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mario
 *
 *******************************************************************************/

#include "uart.h"
#include "BCM.h"
#include <avr/io.h>
volatile uint8_t gu8_DataTransmit ;
volatile uint8_t gu8_DataReceive ;
extern BCM_State ;
extern i_count ;
extern Data_Length_BCM ;
extern i_count_RX ;
extern REC_Length ;
/******************Setting the ISR**********************************************/
void __vector_14(void)__attribute((signal,used));

void __vector_13(void)__attribute((signal,used));

void __vector_14 (void)
{
	UDR = gu8_DataTransmit ;
	DDRA = 0xFF ;
	DDRB = 0xFF ;
	PORTA = BCM_State ;
	if(i_count<Data_Length_BCM)
	{  
		BCM_State = SENDING_COMPLETE ;
		i_count++ ;
		PORTB = i_count ;
	}
	else if(i_count>=Data_Length_BCM)
	{
		BCM_State = FRAME_COMPLETE ;
	}
	CLEAR_BIT(UCSRB,UDRIE);
}
void __vector_13 (void)
{
	gu8_DataReceive = UDR ;
	if(i_count_RX<REC_Length)
	i_count_RX ++;
	else
	{
		
		
	}
	
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
UART_ERROR UART_init(const strUART_Config *UART_Cfg)
{
	uint8_t ERROR  = ERROR_OK;
	/**********************Enabling Full Duplex Transmission**********************/
	SET_BIT(UCSRB,RXEN) ;
	SET_BIT(UCSRB,TXEN) ;
	/******************Checking Speed Mode & BAUDRATE ************************************/
	CLEAR_BIT(UBRRH,URSEL) ; /***********************to Write in UBRRH REGISTERS***********/
	switch(UART_Cfg->u8_SpeedMode)
	{
		case NORMAL_SPEED :
			CLEAR_BIT(UCSRA,U2X);
			/**************************BAUDRATE****************************************/
			/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
			UBRRH = BAUD_PRESCALE_SINGLE>>8;
			UBRRL = BAUD_PRESCALE_SINGLE;
			break;
		case DOUBLE_SPEED :
			SET_BIT(UCSRA,U2X) ;
			/**************************BAUDRATE****************************************/
			/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
			UBRRH = BAUD_PRESCALE_DOUBLE>>8;
			UBRRL = BAUD_PRESCALE_DOUBLE;
			break;
		default :
			ERROR = ERROR_NOK ;
			break ;	
	}
	/**********************Synchronous or Asynchronous Operation **************/
	SET_BIT(UCSRC,URSEL) ; /******************Setting to Access UCRSC Register********/
	switch(UART_Cfg->u8_Sync)
	{
		case SYNCHRONOUS:
			SET_BIT(UCSRC,UMSEL);
			break;
		case ASYNCHRONOUS:
			CLEAR_BIT(UCSRC,UMSEL);
			break ;
		default:
			ERROR = ERROR_NOK ;
	}
	/***********************FRAME DATA BITS*************************************/
	switch(UART_Cfg->u8_DataBits)
	{
		case FIVE_BITS:
			CLEAR_BIT(UCSRC,UCSZ0) ;
			CLEAR_BIT(UCSRC,UCSZ1) ;
			CLEAR_BIT(UCSRB,UCSZ2) ;
			break; 
		case SIX_BITS:
			SET_BIT(UCSRC,UCSZ0) ;
			CLEAR_BIT(UCSRC,UCSZ1) ;
			CLEAR_BIT(UCSRB,UCSZ2) ;
			break;
		case SEVEN_BITS:
			CLEAR_BIT(UCSRC,UCSZ0) ;
			SET_BIT(UCSRC,UCSZ1) ;
			CLEAR_BIT(UCSRB,UCSZ2) ;
			break;
		case EIGHT_BITS:
			SET_BIT(UCSRC,UCSZ0) ;
			SET_BIT(UCSRC,UCSZ1) ;
			CLEAR_BIT(UCSRB,UCSZ2) ;
			break;
		case NINE_BITS:
			SET_BIT(UCSRC,UCSZ0) ;
			SET_BIT(UCSRC,UCSZ1) ;
			SET_BIT(UCSRB,UCSZ2) ;
			break;	
		default:
			ERROR = ERROR_NOK ;
			break;
	}
	/****************************PARITY CHECKING****************************/
	switch(UART_Cfg->u8_Parity)
	{
		case PARITY_DISABLED:
			CLEAR_BIT(UCSRC,UPM1);
			CLEAR_BIT(UCSRC,UPM0);
			break;
		case EVEN_PARITY:
			SET_BIT(UCSRC,UPM1);
			CLEAR_BIT(UCSRC,UPM0);
			break;
		case ODD_PARITY:
			SET_BIT(UCSRC,UPM1);
			SET_BIT(UCSRC,UPM0);
			break;
		default:
			ERROR = ERROR_NOK ;
			break;
	}
	/************************** STOP BITS************************************/
	switch(UART_Cfg->u8_StopBits)
	{
		case ONE_STOP:
			SET_BIT(UCSRC,USBS) ;
			break;
		case TWO_STOP:
			CLEAR_BIT(UCSRC,USBS) ;
			break;
		default:
			ERROR = ERROR_NOK ;
			break;		
	}
	/********************Interrup or Polling Mode****************************/
	switch(UART_Cfg->u8_Interrupt)
	{
		case INTERRUPT_MODE:
		//SET_BIT(UCSRB,TXCIE) ;
		//SET_BIT(UCSRB,RXCIE) ;
		SET_BIT(SREG,I_BIT) ;
		break;
		case POLLING_MODE:
		CLEAR_BIT(SREG,I_BIT) ;
		break;
		default:
		ERROR = ERROR_NOK ;
		break;
	}
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/ 
		
	
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/ 	
	//UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1); 
	return ERROR ;
}
	
UART_ERROR UART_sendByte(const uint16_t data)
{
	/*************running on interrupt Mode************/
	/*while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	gu8_DataTransmit = data ;
	SET_BIT(UCSRB,UDRIE) ;*/
	/*************running on Interrupt BCM MODE*******/
	//PORTB = 0x03;
	if(BIT_IS_CLEAR(UCSRA,UDRE))
	{
		 BCM_State = SENDING_BYTE ;
		 //PORTB = SENDING_BYTE ;
	}
	else
	{
		gu8_DataTransmit = data ;
		//BCM_State = SENDING_COMPLETE ;	
		SET_BIT(UCSRB,UDRIE) ;
	}  
	/************running on Polling Mode*************/
	/*SET_BIT(PORTB,5) ;
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
	SET_BIT(PORTB,6) ;*/
	return ERROR_OK ;
}

UART_ERROR UART_recieveByte(uint8_t *pu8_Received_Data)
{
	/***********Receiving on Inerrupt Mode*********/
	SET_BIT(UCSRB,RXCIE) ;
	*pu8_Received_Data = gu8_DataReceive;
	
	/***********Polling on Mode*********************/
	/*SET_BIT(PORTB,4) ;
	while(BIT_IS_CLEAR(UCSRA,RXC)){}	 
    return UDR;	*/	
   return ERROR_OK;
}

/*UART_ERROR UART_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************
}*/

/*UART_ERROR UART_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}*/
