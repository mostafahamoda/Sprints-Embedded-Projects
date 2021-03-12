/*
 * UserStory_2.c
 *
 * Created: 2/21/2020 2:42:32 PM
 *  Author: mostafahamoda1995
 */ 
#include "main.h"
#include <util/delay.h>
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Platform_Types.h"
#include "semphr.h"
#include "queue.h"
#include "Common_Macros.h"
#include "LCD_Lib.h"
#include "UserStory_2.h"
#include <string.h>
static u8 gu8_Button1_State ;
static u8 gu8_Button2_State ;
QueueHandle_t LCD_Q_2 = NULL ;
int Q_Size_2 = 10 ;

void User2_StartApp(void)
{
	SET_BIT(DDRA,LED) ;
	LCD_Q_2 = xQueueCreate(Q_Size_2,sizeof(char)) ;
	xTaskCreate( TaskA_2, "Button1",200,NULL, 1, NULL );
	xTaskCreate( TaskB_2, "Button2",200,NULL, 3, NULL );
	xTaskCreate( TaskC_2, "Queue",200,NULL, 2, NULL );
	xTaskCreate( TaskD_2, "LCD",200,NULL, 4, NULL );
	vTaskStartScheduler();
}



void TaskA_2(void* pv)
{
	/*Initializations*/
	char State = 10 ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;
	while(1)
	{
		if(READ_BIT(PIND,BUTTON_1) == PRESSED)
		{
			gu8_Button1_State = PRESSED ;
		}
		else
		{
			gu8_Button1_State = NOTPRESSED ;
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void TaskB_2(void* pv)
{
	/*Initializations*/
	char State = 10 ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;
	while(1)
	{
		if(READ_BIT(PIND,BUTTON_2) == PRESSED)
		{
			gu8_Button2_State  = PRESSED ;
		}
		else
		{
			gu8_Button2_State = NOTPRESSED ;
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void TaskC_2(void* pv)
{
	/*Initializations*/
	u8 u8_State  ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 20;
	while(1)
	{
		if((gu8_Button1_State == 1) || (gu8_Button2_State == 1))
		{
			u8_State = PRESSED ;
			SET_BIT(PORTA,LED) ;
			xQueueSend(LCD_Q_2,&u8_State,0);
		}
		else
		{
			u8_State = NOTPRESSED ;
			CLEAR_BIT(PORTA,LED) ;
			xQueueSend(LCD_Q_2,&u8_State,0);
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void TaskD_2(void* pv)
{
	/*Initializations*/
	BaseType_t queueState=pdFALSE;
	char Data_Rec = NULL  ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100;
	while(1)
	{
		queueState = xQueueReceive(LCD_Q_2,&Data_Rec,5000);
		if(queueState == pdPASS)
		{
			if(Data_Rec == PRESSED)
			{
				LCD_Write_Command(LCD_CLEAR_CMD);
				LCD_Write_String("LED ON") ;
			}
			else if(Data_Rec == NOTPRESSED)
			{
				LCD_Write_Command(LCD_CLEAR_CMD);
				LCD_Write_String("LED OFF") ;
			}
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}