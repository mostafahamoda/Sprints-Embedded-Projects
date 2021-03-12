/*
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
#include <string.h>
#include "app_tasks.h"

static uint8_t g_Password[10]={0};
static const uint8_t g_CurrentPassword[]="12345678";
QueueHandle_t LCD_Q = NULL ;
static u8 gu8_State  ;
static u8 LCD_POS_ROW ;
static u8 LCD_POS_COL ;
int Q_Size = 10 ;
char  Data_B[] = "Hello LCD !!" ;
char  Data_C[] = "over-written " ;
char a[20] ;

/ *
void vTask_KeyPad(void  *vpParamter)
{
	uint8_t KeypadLastState = NOTPRESSED;
	uint8_t KeypadKey = 0;
	Keypad_Init();
	LCD_Write_Command(LCD_CLEAR_CMD);
	LCD_Write_String("keypad ON");
	_delay_ms(1000);
	while(1)
	{
		KeypadKey = Keypad_getkey();
		if ((KeypadKey != NOTPRESSED) && (KeypadLastState == NOTPRESSED))
		{
			xQueueSend(LCD_Queue,(void *)&KeypadKey,0);
		}
		KeypadLastState = KeypadKey;
		vTaskDelay(50);
	}
	
}




void vTask_LCD(void  *vpParamter)
{
	uint8_t KeypadKey = 0;
	uint8_t passwordIndex = 0;
	BaseType_t queueState=pdFALSE;
	LCD_State_t LCD_CurrentState = Welcome;
	LCD_Write_Command(LCD_CLEAR_CMD);
	LCD_Write_String("LCD ON");
	_delay_ms(1000);
	LCD_Write_Command(LCD_CLEAR_CMD);
	LCD_Write_String("Welcome");
	while(1)
	{
		// block on queue for ever
		queueState = xQueueReceive(LCD_Queue,&KeypadKey,5000);
		if (queueState==pdPASS)
		{
			switch(LCD_CurrentState)
			{
				case Welcome:
				if (KeypadKey=='#')
				{
					LCD_CurrentState = Recieving;
					LCD_Write_Command(LCD_CLEAR_CMD);
					LCD_Write_String("Password:");
					LCD_Go_To_X_Y(LCD_ROW_2,LCD_POSITION_2);
				}
				break;
				case Recieving:
				switch(KeypadKey)
				{
					
					case 'C':
					//clear one character from lcd and string
					if (passwordIndex>0)
					{
						passwordIndex--;
						LCD_Write_Command(LCD_CURSOR_SHIFT_LIFT_CMD);
						LCD_Write_Character(' ');
						LCD_Write_Command(LCD_CURSOR_SHIFT_LIFT_CMD);
					}
					break;
					case '#':
					// add null to the end of the string
					g_Password[passwordIndex]='\0';
					LCD_CurrentState = Submit;
					// reset index
					passwordIndex = 0;
					//release semaphore to run check Task
					xSemaphoreGive(CheckPasswordSemaphore);
					break;
					default:
					// add to string and show on lcd
					// check if index over flow and don't accept other character
					if (passwordIndex<9)
					{
						g_Password[passwordIndex]=KeypadKey;
						passwordIndex++;
						LCD_Write_Character(KeypadKey);
						vTaskDelay(200);
						LCD_Write_Command(LCD_CURSOR_SHIFT_LIFT_CMD);
						LCD_Write_Character('*');
					}
					break;
				}
				break;
				case Submit:
				LCD_CurrentState = Welcome;
				passwordIndex=0;
				LCD_Write_Command(LCD_CLEAR_CMD);
				LCD_Write_String("Welcome");
				break;
			}
		}
		else
		{
			if (LCD_CurrentState != Welcome)
			{
				LCD_CurrentState = Welcome;
				passwordIndex=0;
				LCD_Write_Command(LCD_CLEAR_CMD);
				LCD_Write_String("Welcome");
			}
			
		}
	}
}

void vTask_Password_Check(void  *vpParamter)
{
	xSemaphoreTake(CheckPasswordSemaphore,0);
	LCD_Write_Command(LCD_CLEAR_CMD);
	LCD_Write_String("check ON");
	_delay_ms(1000);
	while(1)
	{
		
		// block on semaphore
		xSemaphoreTake(CheckPasswordSemaphore,portMAX_DELAY);
		// check the password with saved password
		if (strcmp((const char *)g_Password,(const char *)g_CurrentPassword)==0)
		{
			LCD_Write_Command(LCD_CLEAR_CMD);
			LCD_Write_String("Access granted");
		}
		else
		{
			LCD_Write_Command(LCD_CLEAR_CMD);
			LCD_Write_String("Access denied");
		}
		// write access granted to LCD or rejected
		
	}
}
* /


void TaskA(void *pv)
{
	/ *Initializations* /
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
	/ *Initializations* /
	char Data ;
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 200;
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
/ *
		LCD_Write_String(Data_B) ;
		vTaskDelay(400) ;
		LCD_Write_Command(LCD_CLEAR_CMD) ;
		xQueueSendToBack(LCD_Q,&Data,0);
* /
		/ *itoa(Data_B,a,10) ;
		//LCD_vClear();
		LCD_Write_String(a) ;* /
		/ *vTaskDelay(400) ;* /
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
	/ *Initializations* /
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
*/
