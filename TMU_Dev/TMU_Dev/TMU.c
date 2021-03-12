/*
 * TMU.c
 *
 * Created: 12/17/2019 9:34:54 AM
 *  Author: mostafahamoda1995
 */ 
#include "timer.h"
#include "TMU.h"
#include "LCD_head.h"
/*Initializing the Delay ID*/
extern Ignite_Flag_Var ;
u32 *Ignite_Flag = &Ignite_Flag_Var ;
/************Initializing the Structure ID*******************************/
Struct_ID Struct2[TASKS_NO];
/**********Initializing my Priority Array********************************/
//u32 Prio_Arr[TASKS_NO] = {0};
/**************Initializing the Configuration Structure******************/
Timer_Configuration_S_H Struct_Init_t ;
Timer_Configuration_S_H *Struct_Init = &Struct_Init_t ;
/****************This Will Be Called only one Time in my Function******/
u8 TMU_Init(u8 Timer_ID,u32 Res) 
{
	u32 j_Counter;
	Struct_Init->Timer_Channel = Timer_ID;
	Struct_Init->Mode = 0 ;
	Struct_Init->Timer_Mode = 0 ;
	Struct_Init->Timer_Psc = PSC_1024 ;
	Struct_Init->Res = Res ;
	/*Choosing the Right Pre-Scalar*/
	Timer_Init(Struct_Init) ;
	/************Initializing the Pointers to Null**********************/
	for(j_Counter=0;j_Counter<TASKS_NO;j_Counter++)
	{
		Struct2[j_Counter].ptr = NULL_PTR ;
		Struct2[j_Counter].ID = FREE_ID_TASK ;
		Struct2[j_Counter].Priority = 0;
	}
}
/*************This Function Takes a Pointer to Function and Delays by the Given Time***********/
u8 TMU_Start(u32 Ticks, void* FunPtr,u8 One_Shot,u32 ID_User,u32 Priority)
{
	int i_counter = 0 ;
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
			//LCD_vPrintchar('H') ;
			Struct2[i_counter].ID = ID_User ;
			Struct2[i_counter].ptr = FunPtr ;
			Struct2[i_counter].Ticks_Delay = Ticks ;
			Struct2[i_counter].Periodic = One_Shot ; 
			Struct2[i_counter].Priority = Priority ;
			//LCD_vPrintchar(i_counter+'0') ;
			//Ignite_Flag = 0 ;
			// Condition for breaking the loop
			//Timer_Start(Struct_Init->Timer_Channel,Struct_Init->Res) ;
			break;
		}
	}
	/*******Initializing the Timer*******************************/
	Timer_Start(Struct_Init->Timer_Channel,Struct_Init->Res) ;
	return E_OK ;
}

/*LCD_vPrintchar(Struct2[0].ID+'0') ;
LCD_vPrintchar(Struct2[0].ptr+'0') ;
LCD_vPrintchar(Struct2[0].Ticks_Delay+'0') ;
LCD_vPrintchar(Struct2[0].Periodic+'0') ;*/
su32 One_Time = 0 ;
su8 One_Shot ;
u8 Dispatcher(void)
{
	/****************Initializing Varibles********************************/
	u32 Delay , i_count ;
	u32 Prio ;
	u32 k_count ;
	u32 High_Priority_U = Priority_High ;
	void (* PtrRun)() ;
	/*for(k_count=0;k_count<Priority_High;k_count++)
	{*/
	/*u32 i_Arr[TASKS_NO] = {TASKS_NO} ;
	u32 j_count,Task_count=0 ,i_count;
	u32 i_counter ;
	u32 Dummy ;*/
	//LCD_vPrintchar(*Ignite_Flag+'0') ;
	/**********Checking the Highest Priority Tasks****************************/
	/*for(j_count = 0;j_count<TASKS_NO;j_count++)
	{
		if(Struct2[j_count].Priority == High_Priority_U)
		{
		High_Priority_U = Struct2[j_count].Priority ;
		i_Arr[Task_count] = j_count ;
		//LCD_vPrintchar('R');
		Task_count++ ;
		}
	}*/
	/*****************Checking for my Conditions*****************************/
	for(i_count=0; i_count<=TASKS_NO ; i_count++)
	{
		if(Struct2[i_count].ID == FREE_ID_TASK)
		{
			break ;
		}
		else
		{
			One_Shot = Struct2[i_count].Periodic ;
			Delay = Struct2[i_count].Ticks_Delay ;
			Prio = Struct2[i_count].Priority ;
			if(One_Shot == 0)
			{
				if(((*Ignite_Flag%Delay)== 0)&& (One_Time != *Ignite_Flag) )
				{
				PtrRun = Struct2[i_count].ptr ;
				PtrRun('B') ;
				One_Time =  *Ignite_Flag ;
				}
			}
			else if((One_Shot == 1))
			{
				if(One_Time != ONESHOTDONE)
				{
				if(*Ignite_Flag == Delay)
				{
				PtrRun = Struct2[i_count].ptr ;
				One_Time =  ONESHOTDONE ;
				PtrRun('A') ;
				}
				}
			}
		}
	}
	//}
}

u8 TMU_Stop(u32 ID_User)
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
	

