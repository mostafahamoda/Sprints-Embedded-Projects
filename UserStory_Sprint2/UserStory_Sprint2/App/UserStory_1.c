/*
 * UserStory_2.c
 *
 * Created: 2/20/2020 8:49:46 PM
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
#include "UserStory_1.h"
#include <string.h>
QueueHandle_t LCD_Q = NULL ;
static u8 gu8_State  ;
int Q_Size = 10 ;
static char  Data_B[] = "Hello LCD !!" ;
static char  Data_C[] = "over-written " ;
void User1_StartApp(void)
{
	LCD_Q = xQueueCreate(Q_Size,sizeof(char)) ;
	xTaskCreate( TaskA, "Button1",200,NULL, 1, NULL );
	xTaskCreate( TaskB, "Button2",200,NULL, 3, NULL );
	xTaskCreate( TaskC, "Queue",200,NULL, 2, NULL );
	vTaskStartScheduler();
}

void TaskA(void *pv)
{
	/*Initializations*/
	BaseType_t queueState=pdFALSE;
	char Data_Rec  ;
	char * Data_ptr = 0 ;
	int Data = &Data_B ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;
	while(1)
	{
		queueState = xQueueReceive(LCD_Q,&Data_Rec,5000);
		if(queueState == pdPASS)
		{
		Data_ptr = Data_Rec ;
		if(Data_ptr != NULL)
		{
			LCD_Write_Command(LCD_CLEAR_CMD);
			if(gu8_State == PRESSED)
			{
				LCD_Go_To_X_Y(LCD_ROW_2,LCD_POSITION_2) ;
			}
			LCD_Write_String(Data_Rec) ;
			LCD_Write_Character(gu8_State) ;
		}
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}
void TaskC(void *pv)
{
	/*Initializations*/
	char Data ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 400;
	while(1)
	{
		if(NOTPRESSED == gu8_State)
		{
			Data = &Data_B ;
			xQueueSendToBack(LCD_Q,&Data,0);	
		}
		else if(PRESSED == gu8_State)
		{
			Data = &Data_C ;
			xQueueSendToBack(LCD_Q,&Data,0);	
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}
void TaskD(void *pv)
{
	char Data = &Data_B ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;
	while(1)
	{
/*
		LCD_Write_String(Data_B) ;
		vTaskDelay(400) ;
		LCD_Write_Command(LCD_CLEAR_CMD) ;
		xQueueSendToBack(LCD_Q,&Data,0);
*/
		/*itoa(Data_B,a,10) ;
		//LCD_vClear();
		LCD_Write_String(a) ;*/
		/*vTaskDelay(400) ;*/
// 		LCD_Write_Character('C') ;
// 		xLastWakeTime = xTaskGetTickCount();
// 		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		//LCD_vClear() ;
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		PORTD ^= (1<<6) ;
	}
}
void TaskB(void *pv)
{
	/*Initializations*/
	char State = 10 ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 30;
	while(1)
	{
		if(READ_BIT(PIND,2) == PRESSED)
		{
			gu8_State = PRESSED ;
		}
		else
		{	
			gu8_State = NOTPRESSED ;
		}
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}
