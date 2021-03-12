/*
 * SOS.h
 *
 * Created: 1/3/2020 4:36:22 PM
 *  Author: mostafahamoda1995
 */ 


#ifndef SOS_H_
#define SOS_H_
/*
 * TMU.h
 *
 * Created: 12/17/2019 9:35:15 AM
 *  Author: mostafahamoda1995
 */ 
#include "Platform_Types.h"
#include "timer.h"
#include "Std_Types.h"
#define TASKS_NO 2
#define FREE_ID_TASK -1
#define NULL_PTR 0
#define ONESHOTDONE -1
#define Priority_High 5 
#define OS_PREVIOUSLY_INITILIZED  2
#define OS_SUCCESSFULLY_INITIALIZED 0
#define OS_NOT_INITILIZED 9 
#define TASK_CREATED 18
typedef struct{ 
	su32 ID ;
	u32 Priority;
	void *ptr ;
	u32 Ticks_Delay ;
	u8 Periodic ;
} Struct_ID;
u8 Sos_Init(u8 Timer_ID,u32 Res) ;
u8 Sos_Create_Task(u32 Time,void* FunPtr,u8 One_Shot,u32 ID_User,u32 Priority) ;
u8 Sos_Stop(u32 ID_User) ;
u8 Scheduler(void) ;
#endif /* SOS_H_ */