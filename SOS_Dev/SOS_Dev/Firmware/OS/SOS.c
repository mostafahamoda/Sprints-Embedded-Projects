/*
 * TMU.c
 *
 * Created: 12/17/2019 9:34:54 AM
 *  Author: mostafahamoda1995
 */ 
#include "timer.h"
#include "SOS.h"
#include "LCD_head.h"
#include "Error_Ret_Sos.h"
/*Initializing the Delay ID*/
/*
* Externing the Variable Responsible for choosing the Running Task
*/
extern Ignite_Flag_Var ;
u32 *Ignite_Flag = &Ignite_Flag_Var ;
/*
* Creating Static Variable Defining if the Task is Periodic or not 
*/
static u32 One_Time  ;
su8 One_Shot ;
/*
*	Dummy Variables used for the calculations 
*/
u32 Dummy  ;
u32 Per_Time ;
/************Initializing the Structure ID*******************************/
Struct_ID Struct2[TASKS_NO];
/**************Initializing the Configuration Structure******************/
Timer_Configuration_S_H Struct_Init_t ;
/***Creating Pointer to Structure*********************************/
Timer_Configuration_S_H *Struct_Init = &Struct_Init_t ;
/*
* Creating a Static Variable for Error Error Checking 
*/
static u32 gu32Return_Status = OS_NOT_INITILIZED ;
/*
* a static variable to tell if my OS was Previously Defined 
*/
static u32 gu32OS_Init_Status = OS_NOT_INITILIZED ;
/***********This Will Be Called only one Time in my main******/
extern ERROR_CHECK_t Sos_Init(u8 Timer_ID,u32 Res) 
{
	if(gu32OS_Init_Status == OS_PREVIOUSLY_INITILIZED)
	{
		gu32Return_Status = OS_PREVIOUSLY_INITILIZED ;
	}
	else if(gu32OS_Init_Status == OS_NOT_INITILIZED)
	{
	/*
	* Creating a Counter for the for Loop 
	*/
	u32 u32j_Counter;
	/*
	* Initializing my Timer Structure 
	*/
	Struct_Init->Timer_Channel = Timer_ID;
	Struct_Init->Mode = 0 ;
	Struct_Init->Timer_Mode = 0 ;
	Struct_Init->Timer_Psc = PSC_64 ;
	Struct_Init->Res = Res ;
	/*
	*Choosing the Right Pre-Scalar
	*/
	Timer_Init(Struct_Init) ;
	/*
	* Note that we Do not Need to Handle the Maximum Resolution Case as our Timer is Well Defined 
	*/
	/*
	* Initializing the Pointers to Null
	* Making Sure that my Buffer is Ready for Usage 
	*/
	for(u32j_Counter=0;u32j_Counter<TASKS_NO;u32j_Counter++)
		{
		Struct2[u32j_Counter].ptr = NULL_PTR ;
		Struct2[u32j_Counter].ID = FREE_ID_TASK ;
		Struct2[u32j_Counter].Priority = 0;
		}
		
	gu32OS_Init_Status = OS_PREVIOUSLY_INITILIZED ;
	gu32Return_Status = OS_SUCCESSFULLY_INITIALIZED ;
	}
	return gu32Return_Status ;
}
/*
*This Function Takes a Pointer to Function and Delays by the Given Time
*/
extern ERROR_CHECK_t Sos_Create_Task(u32 Ticks, void* FunPtr,u8 One_Shot,u32 ID_User,u32 Priority)
{
	if(gu32Return_Status == OS_NOT_INITILIZED || gu32Return_Status == OS_PREVIOUSLY_INITILIZED )
	{
		gu32Return_Status = OS_NOT_INITILIZED ;
	}
	else if(gu32Return_Status == OS_SUCCESSFULLY_INITIALIZED)
	{
	/*
	* Declaring my Counters
	*/
	int i_counter = 0 ;
	/*
	* Declaring a Pointer to the Function to be Called
	*/
	void (* PtrRun)() ;
	/*****************Checking if the Pointer Was Previously Allocated in my Structure****************/
	while(i_counter < TASKS_NO)
	{
		if(Struct2[i_counter].ID != FREE_ID_TASK)
		{
			i_counter++; 
		}
		else if(Struct2[i_counter].ID == FREE_ID_TASK)
		{
			Struct2[i_counter].ID = ID_User ;
			Struct2[i_counter].ptr = FunPtr ;
			Struct2[i_counter].Ticks_Delay = Ticks ;
			Struct2[i_counter].Periodic = One_Shot ; 
			Struct2[i_counter].Priority = Priority ;
			break;
		}
	}
	/*******Initializing the Timer*******************************/
	Timer_Start(Struct_Init->Timer_Channel,Struct_Init->Res) ;
	gu32Return_Status = TASK_CREATED ;
	}
	return gu32Return_Status ;
}
/*
* My Scheduler Function that will be Called in the While Loop Calling the Primary Task
*/
extern ERROR_CHECK_t Scheduler(void)
{
	/****************Initializing Varibles********************************/
	u32 Delay ;
	u32 Prio ;
	u32 k_count ;
	u32 High_Priority_U = Priority_High ;
	void (* PtrRun)() ;
	u32 j_count,i_count;
	u32 i_counter ;
	u32 Task_count ; 
	for(k_count=0;k_count<Priority_High;k_count++)
	{
	Task_count = 0 ;
	u32 i_Arr[TASKS_NO] = {TASKS_NO} ;
	/**********Checking the Highest Priority Tasks****************************/
	for(j_count = 0;j_count<TASKS_NO;j_count++)
	{
		if(Struct2[j_count].Priority == High_Priority_U)
		{
		i_Arr[Task_count] = j_count ;
		Task_count++ ;
		}
	}
	/*****************Checking for my Conditions*****************************/
	for(Dummy=0;Dummy<Task_count;Dummy++)
	{
		i_count = i_Arr[Dummy] ;
		if(Struct2[i_count].ID == FREE_ID_TASK)
		{
			break ;
		}
		else if(i_count != TASKS_NO)
		{
			One_Shot = Struct2[i_count].Periodic ;
			Delay = Struct2[i_count].Ticks_Delay ;
			Prio = Struct2[i_count].Priority ;
			if(One_Shot == 0)
			{
				if(((*Ignite_Flag%Delay)== 0)&& (Per_Time != *Ignite_Flag) )
				{
					Per_Time  =  *Ignite_Flag ;
					PtrRun = Struct2[i_count].ptr ;
					LCD_vPrintchar('B') ;
				}
			}
			else if(One_Shot == 1)
			{
				if(One_Time != ONESHOTDONE)
				{
					if(*Ignite_Flag == Delay)
					{
						One_Time =  ONESHOTDONE ;
						PtrRun = Struct2[i_count].ptr ;
						LCD_vPrintchar('A') ;
					}
				}
			}
		}
	}
	High_Priority_U -- ;
	}
	return E_OK ;
}

extern ERROR_CHECK_t Sos_Stop(u32 ID_User)
{
/*********Checking for the Available ID*************/
	u32 i_count;
	for(i_count=0;i_count<TASKS_NO;i_count++)
	{
		if(Struct2[i_count].ID == ID_User)
		{
			Struct2[i_count].ptr = NULL_PTR ;
			Struct2[i_count].ID = FREE_ID_TASK ;
		}	
	}
	return E_OK;
}
	

