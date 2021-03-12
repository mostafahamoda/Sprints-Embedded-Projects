/*
 * dio.c
 *
 *  Created on: Nov 23, 2019
 *      Author: Mario
 */


#include "dio.h"
extern uint8_t DIO_WRITE_PIN (uint8_t u8Pin_Number,uint8_t u8Value )
{
	if(u8Pin_Number < MAX_PINS)
		{
		if (u8Value == HIGH)
		{
			if     (u8Pin_Number >= 0 && u8Pin_Number < 8)     PORTA |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 8 && u8Pin_Number < 16)    PORTB |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 16 && u8Pin_Number < 24)   PORTC |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 24 && u8Pin_Number < 32)   PORTD |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
		}
		else if (u8Value == LOW)
		{
			if     (u8Pin_Number >= 0 && u8Pin_Number < 8)     PORTA &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 8 && u8Pin_Number < 16)    PORTB &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 16 && u8Pin_Number < 24)   PORTC &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 24 && u8Pin_Number < 32)   PORTD &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
		}
		else
		{
			return ERROR_NOK;
		}
		return ERROR_OK;

		}else
		{
			return ERROR_NOK;
		}

}
extern uint8_t DIO_INIT_Pin (uint8_t u8Pin_Number,uint8_t u8State)
{
	if(u8Pin_Number < MAX_PINS)
	{
		if (u8State == OUTPUT)
		{
			if     (u8Pin_Number >= 0 && u8Pin_Number < 8)     DDRA |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 8 && u8Pin_Number < 16)    DDRB |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 16 && u8Pin_Number < 24)   DDRC |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 24 && u8Pin_Number < 32)   DDRD |=   (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
		}
		else if(u8State == INPUT)
		{
			if     (u8Pin_Number >= 0 && u8Pin_Number < 8)     DDRA &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 8 && u8Pin_Number < 16)    DDRB &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 16 && u8Pin_Number < 24)   DDRC &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 24 && u8Pin_Number < 32)   DDRD &=  ~(1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
		}
		else
		{
			return ERROR_NOK;
		}
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}

extern uint8_t DIO_PIN_READ (uint8_t u8Pin_Number,uint8_t* ppu8Reading )
{
	uint8_t u8temp=0;
	if(u8Pin_Number < MAX_PINS)
		{
		if (ppu8Reading != 0) // the pointer is not a void
		{
			if     (u8Pin_Number >= 0 && u8Pin_Number < 8)    u8temp = PINA & (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 8 && u8Pin_Number < 16)   u8temp = PINB & (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 16 && u8Pin_Number < 24)  u8temp = PINC & (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;
			else if(u8Pin_Number >= 24 && u8Pin_Number < 32)  u8temp = PIND & (1 << (u8Pin_Number%BITS_PER_REGISTER)) ;

			if(u8temp != 0)
			{
				*ppu8Reading = 1;
			}
			else
			{
				*ppu8Reading = 0;
			}
		}
		else
		{
			return ERROR_NOK;
		}
		return ERROR_OK;
		}
	else
	{
		return ERROR_NOK;
	}
}

extern uint8_t DIO_WRITE_PORT (uint8_t u8Port_Number,uint8_t u8Value)
{
	if(u8Port_Number < MAX_PORTS)
	{
		u8Port_Number = u8Value;
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}

extern uint8_t DIO_INIT_PORT (uint8_t u8Port_Number,uint8_t u8State)
{
	if(u8Port_Number < MAX_PORTS)
	{
		if (u8State == INPUT)
		{
		u8Port_Number = INPUTS;

		}
		else if (u8State == OUTPUT )
		{
		u8Port_Number = OUTPUTS;
		}
		else
		{
			return ERROR_NOK;	//HANDLING WRONG STATE
		}
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}

}
extern uint8_t DIO_PORT_READ (uint8_t u8Port_Number,uint8_t* pu8Reading)
{
	uint8_t u8Temp=0;
	if(u8Port_Number < MAX_PORTS)
	{

		u8Temp = u8Port_Number ;
		*pu8Reading = u8Temp;
		return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}


}
extern uint8_t DIO_PIN_ACTIVATE_PULL_UP(uint8_t u8Pin_Number )
{
	if(u8Pin_Number < MAX_PINS)
	{
	DIO_WRITE_PIN(u8Pin_Number , HIGH);
	return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}

extern uint8_t DIO_PORT_ACTIVATE_PULL_UP(uint8_t u8Port_Number )
{
	if(u8Port_Number < MAX_PORTS)
	{
	DIO_WRITE_PORT(u8Port_Number , MAX);
	return ERROR_OK;
	}
	else
	{
		return ERROR_NOK;
	}
}



