/*
 * FreeRTOS_TaskCreation.c
 *
 * Created: 10/19/2016 12:12:58 AM
 * Author : Master
 */ 
#include "main.h"
#include <util/delay.h>
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "Common_Macros.h"
#include "queue.h"
#include "LCD_Lib.h"
#include <string.h>
#include "app_tasks.h"
#include "UserStory_1.h"
#include "UserStory_2.h"

/*Externs */
extern xQueueHandle LCD_Q;
extern   Q_Size ;
extern xQueueHandle LCD_Q_2 ;
extern   Q_Size_2 ;

int main()
{
	LCD_Initialization();
	User3_StartApp() ;	
	while(1);
}
