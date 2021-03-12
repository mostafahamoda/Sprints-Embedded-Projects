/*
 * TMU.h
 *
 * Created: 12/17/2019 9:35:15 AM
 *  Author: mostafahamoda1995
 */ 


#ifndef TMU_H_
#define TMU_H_
#include "Platform_Types.h"
#include "timer.h"
#include "Std_Types.h"
#define TASKS_NO 2
#define FREE_ID_TASK -1
#define NULL_PTR 0
#define ONESHOTDONE -1
#define Priority_High 5 
typedef struct{
	su32 ID ;
	u32 Priority;
	void *ptr ;
	u32 Ticks_Delay ;
	u8 Periodic ;
} Struct_ID;
u8 TMU_Init(u8 Timer_ID,u32 Res) ;
u8 TMU_Start(u32 Time,void* FunPtr,u8 One_Shot,u32 ID_User,u32 Priority) ;
u8 TMU_Stop(u32 ID_User) ;
u8 Dispatcher(void) ;
#endif /* TMU_H_ */