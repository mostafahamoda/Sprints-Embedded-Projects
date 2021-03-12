/*
 * UserStory_3.c
 *
 * Created: 2/21/2020 4:59:06 PM
 *  Author: mostafahamoda1995
 */ 


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
#include "UserStory_3.h"
#include <string.h>
static u8 gu8_Button1_State ;
static u8 gu8_Button2_State ;
QueueHandle_t LCD_Q_3 = NULL ;
u32 Q_Size_3 = 10 ;
static u8 gu8_Restart ;

void User3_StartApp(void)
{
	LCD_Q_3 = xQueueCreate(Q_Size_3,sizeof(char)) ;
	xTaskCreate( TaskA_3, "Button1",200,NULL, 2, NULL );
	xTaskCreate( TaskB_3, "Button2",200,NULL, 2, NULL );
	xTaskCreate( TaskC_3, "Queue",200,NULL,1, NULL );
	xTaskCreate( TaskD_3, "LCD",200,NULL, 1, NULL );
	vTaskStartScheduler();
}



void TaskA_3(void* pv)
{
	/*Initializations*/
	char State = 10 ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 150;
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

void TaskB_3(void* pv)
{
	/*Initializations*/
	char State = 10 ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 150;
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

void TaskC_3(void* pv)
{
	/*Initializations*/
	u8 u8_State_1 = 0  ;
	u8 u8_State_2 = WIN_NUMBER  ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 250;
	while(1)
	{
		if(gu8_Restart != RESTART)
		{
		if(gu8_Button1_State == PRESSED)
		{
			u8_State_1 ++ ;
			if(u8_State_2 > 50)
			{
				u8_State_2 -- ;
			}
		}
		else if(gu8_Button2_State == PRESSED)
		{
			u8_State_2 ++ ;
			if(u8_State_1 > 0)
			{	
				u8_State_1 -- ; 
			}
		}
		}
		else
		{
			u8_State_1 = 0 ;
			u8_State_2 = WIN_NUMBER ;
			gu8_Restart = 0 ;
		}
		xQueueSendToBack(LCD_Q_3,&u8_State_1,0);
		xQueueSendToBack(LCD_Q_3,&u8_State_2,0);
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}

void TaskD_3(void* pv)
{
	/*Initializations*/
	BaseType_t queueState=pdFALSE;
	u8 Data_Rec = NULL  ;
	u8 Data_Rec_Prev =  NULL  ;
	u8 Five_Count = 0 ; 
	u8 a[5] ;  
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100;
	while(1)
	{
		queueState = xQueueReceive(LCD_Q_3,&Data_Rec,200);
		if(queueState == pdPASS)
		{
			if((Data_Rec>0) && (Data_Rec < WIN_NUMBER) && (Data_Rec != NULL) && (Data_Rec != Data_Rec_Prev))
			{
				if((Data_Rec >= WIN_WIN) && (Five_Count < 10))
				{
					LCD_Write_Command(LCD_CLEAR_CMD) ;
					LCD_Write_String("you Win !") ;	
					Five_Count ++ ;
				}
				else if((Data_Rec >= WIN_WIN) && (Five_Count >= 10))
				{
					LCD_Write_Command(LCD_CLEAR_CMD) ;
					Data_Rec = 0 ;
					Five_Count = 0 ;
					gu8_Restart = RESTART ;
				}
				else
				{
				LCD_Go_To_X_Y(LCD_ROW_1,LCD_POSITION_2) ;
				itoa(Data_Rec,a,10) ;
				LCD_Write_String(a) ;
				Data_Rec_Prev = Data_Rec ;
				Data_Rec = NULL ;
				}
			}
			else if((Data_Rec > WIN_NUMBER) && (Data_Rec != NULL) && (Data_Rec != Data_Rec_Prev))
			{
				Data_Rec   = Data_Rec - WIN_NUMBER ;
				if ((Data_Rec >= WIN_WIN) && (Five_Count < 10))
				{
					LCD_Write_Command(LCD_CLEAR_CMD) ;
					LCD_Write_String("you Win !") ;
					Five_Count ++ ;
				}
				else if((Data_Rec >= WIN_WIN) && (Five_Count >= 10))
				{
					LCD_Write_Command(LCD_CLEAR_CMD) ;
					Data_Rec = 0 ;
					Five_Count = 0 ;
					gu8_Restart = RESTART ;
				}
				else
				{
				LCD_Go_To_X_Y(LCD_ROW_2,LCD_POSITION_2) ;
				itoa(Data_Rec,a,10) ;
				LCD_Write_String(a) ;
				Data_Rec_Prev = Data_Rec ;
				Data_Rec = NULL ;
				}
			}
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}