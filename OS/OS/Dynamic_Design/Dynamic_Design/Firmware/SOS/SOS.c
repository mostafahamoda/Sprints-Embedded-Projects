/*
 * SOS.c
 *
 * Created: 12/30/2019 9:56:30 PM
 *  Author: A.Elkady
 */ 

#include "SOS.h"
#include "Power_Management.h"

/*
*	Static variable that tells if the SOS module is initialized or not 
*/
static u8 gu8Is_SOS_initialized = SOS_E_NOT_INTIALIZED_YET ;

/*
*	Static variables that hold the minimum and maximum limits for the resolution 
*/
static u32 gu32Min_resolution_allowed = 0 ;
static u32 gu32Max_resolution_allowed = 0 ;

/*
*	Static variable that will hold the ISR count
*/
static u8 gu8Count = 0 ;

/*
*	A static variable that will hold the number of ticks needed to acheive the desired resolution 
*/
static u16 gu16Number_of_resolution_counts = 0 ;

/*
*	A static variable that will hold the index of the next free element in the events array
*/
static u8 gu8Index = 0 ;

/*
*	A static variable that will hold the overflow multiple value
*/
volatile static u32 gu32System_ticks_number = 1 ;

/*
*	Declaring the struct that will hold the information about a particular event
*/
typedef struct
{
	u8 u8Periodicity ;
	u8 u8Priority ;
	u8 u8Task_state ;
	u32 u32System_ticks_number ;
	pfunc_SOS_Callback pfunc_event ;
}stSOS_Event;

/*
*	Allocating space for the configuration of the events with a predefined number in SOS_cfg.h
*/
static stSOS_Event garstSOS_Tasks[SOS_BUFFER_SIZE] ;


/** 
 * \brief SOS_Init 
 *
 * \param u8Resoltuion (Input) : The desired resolution in microseconds
 * \return u8 : Indication of the execution
 *
 **/  
extern Error SOS_Init(u32 u32System_tick)
{
	/*
	*	An integer that holds the indication of the execution 
	*/
	Error u8Execution_indication = SOS_E_OK ;
	
	/* A variable that will hold the time per tick for the chosen timer */
	u32 u32Tick_time = 0 ;
	
	/*
	*	Calculating the minimum and maximum resolution for the chosen timer configuration 
	*/
	gu32Min_resolution_allowed = ( (PRESCALE_VALUE) / FREQ_OVER_MICRO ) ;
	
	if (TIMER0 == SOS_Config.u8Channel || TIMER2 ==  SOS_Config.u8Channel )
	{
		gu32Max_resolution_allowed = gu32Min_resolution_allowed * MAX_TCNT0_NUMBER ;
		
	} 
	else if(TIMER1 == SOS_Config.u8Channel)
	{
		gu32Max_resolution_allowed = gu32Min_resolution_allowed * MAX_TCNT1_NUMBER ;
	}
	else
	{
		/* Handling of entering wrong timer channel is already done in Timer_Init function in Timer.c */
	}

	/*
	*	Checking if the passed resolution is in the allowed range for the resolution 
	*/
	if (u32System_tick >= gu32Min_resolution_allowed && u32System_tick <= gu32Max_resolution_allowed) 
	{
		/*
		*	Initializing the timer with the configuration defined in SOS_cfg.c
		*/
		u8Execution_indication = Timer_Init(&SOS_Config);
		
		/* Now u32Tick_time holds the value of tick time in nano seconds*/
		u8Execution_indication = Timer_Get_Tick_Time(SOS_Config.u8Channel , &u32Tick_time) ; 
		
		u32Tick_time /= 1000 ; /* so we divide it by 1000 to get it in micros */
		
		gu16Number_of_resolution_counts = u32System_tick / u32Tick_time ;
	} 
	else
	{
		/* Handling of entering wrong resolution */
		u8Execution_indication = SOS_E_RESOLUTION_NOT_IN_RANGE ;
	}
	
	if (SOS_E_OK == u8Execution_indication)
	{
		gu8Is_SOS_initialized = SOS_E_INITIALIZED ;
		Timer_Start(SOS_Config.u8Channel , gu16Number_of_resolution_counts);
	} 
	else
	{
		/* Do nothing */
	}
	
	return u8Execution_indication ;
}

/** 
 * \brief Deinitialize the used timer
 *
 * \param void
 * \return u8 : Indication of the execution if it fails or not
 *
 **/     
extern Error SOS_Deinit(void)
{
	/*
	*	An integer that holds the indication of the execution 
	*/
	Error u8Execution_indication = SOS_E_OK ;
	
	if (SOS_E_INITIALIZED == gu8Is_SOS_initialized)
	{
		u8Execution_indication = Timer_Stop(SOS_Config.u8Channel);
		gu8Is_SOS_initialized = SOS_E_NOT_INTIALIZED_YET ;
	} 
	else
	{
		/* Handling of using the SOS module before intiializing it */
		u8Execution_indication = SOS_E_NOT_INTIALIZED_YET ;
	}
	
	return u8Execution_indication ;
}

/** 
 * \brief SOS_Create_Task : Adds a certain function with a certain interval as an event
 *
 * \param pfunc (Input) : A pointer to the function that is desired to be executed 
 * \param u32System_ticks_number (Input) : The delay time before executing the desired function
 * \param u8Periodicity (Input) : Tells if the user wants to execute this function periodically or one shot
 * \param u8Priority (Input) : Determine the priority of the desired task to be run (0 is the lowest priority)
 * \return  u8 : Indication of the execution if it fails or not 
 *
 **/     
extern Error SOS_Create_Task(pfunc_SOS_Callback pfunc , u32 u32System_ticks_number , u8 u8Periodicity , u8 u8Priority) 
{
	/*
	*	An integer that holds the indication of the execution 
	*/
	Error u8Execution_indication = SOS_E_OK ;
	
	if (SOS_E_INITIALIZED == gu8Is_SOS_initialized)
	{
		/*
		*	Making sure that the passed pointer is not a null one 
		*/
		if (0 != pfunc )
		{
			if (u32System_ticks_number <= gu32Max_resolution_allowed)
			{
				if (PERIODIC == u8Periodicity|| ONE_SHOT == u8Periodicity )
				{
					if (gu8Index < SOS_BUFFER_SIZE)
					{
						/*
						*	Passing the event information to the events array
						*/
						garstSOS_Tasks[gu8Index].pfunc_event = pfunc ;
						garstSOS_Tasks[gu8Index].u32System_ticks_number = u32System_ticks_number ;
						garstSOS_Tasks[gu8Index].u8Periodicity = u8Periodicity ;
						garstSOS_Tasks[gu8Index].u8Priority = u8Priority ;
						garstSOS_Tasks[gu8Index].u8Task_state = WAITING ;

						gu8Index ++ ; /* Increasing the index so the next event can be stored in the next free element in the events array */
					} 
					else
					{
						/* Handling of starting new task while the buffer is full */
						u8Execution_indication = SOS_E_BUFFER_IS_FULL ;
					}
				} 
				else
				{
					/* Handling of entering wrong periodicity */
					u8Execution_indication = SOS_E_WRONG_PERIODICITY ;
				}
			} 
			else
			{
				/* Handling of entering delay beyond the defined limits */
				u8Execution_indication = SOS_E_DELAY_TIME_NOT_IN_RANGE ;
			}
		} 
		else
		{
			/* Handling of entering null pointer*/
			u8Execution_indication = SOS_E_NULL_POINTER ;
		}
	} 
	else
	{
		/* Handling of using the SOS module before intiializing it */
		u8Execution_indication = SOS_E_NOT_INTIALIZED_YET ;
	}
	
	return u8Execution_indication ;	
}

/** 
 * \brief SOS_Delete_Task : Stops a certain event from being executed
 *
 * \param pfunc (Input) : A pointer to the function that is desired to be stopped
 * \return u8 : Indication of the execution if it fails or not 
 *
 **/ 
extern Error SOS_Delete_Task(pfunc_SOS_Callback pfunc) 
{
	/*
	*	An integer that holds the indication of the execution 
	*/
	Error u8Execution_indication = SOS_E_OK ;
	u8 u8Count = 0 ;
	
	if (SOS_E_INITIALIZED == gu8Is_SOS_initialized)
	{
		if ( 0 != pfunc )
		{
			for (u8Count = 0 ; u8Count < gu8Index ; u8Count ++)
			{
				if (pfunc == garstSOS_Tasks[u8Count].pfunc_event)
				{
					gu8Index -- ;
					
					garstSOS_Tasks[u8Count].pfunc_event = garstSOS_Tasks[gu8Index].pfunc_event ;
					garstSOS_Tasks[u8Count].u32System_ticks_number = garstSOS_Tasks[gu8Index].u32System_ticks_number ;
					garstSOS_Tasks[u8Count].u8Periodicity = garstSOS_Tasks[gu8Index].u8Periodicity ;
					garstSOS_Tasks[u8Count].u8Priority = garstSOS_Tasks[gu8Index].u8Priority ;
					garstSOS_Tasks[u8Count].u8Task_state = garstSOS_Tasks[gu8Index].u8Periodicity ;
					
					garstSOS_Tasks[gu8Index].pfunc_event = 0 ;
					
				}
				else
				{
					/* Do nothing */
				}
			}
		}
		else
		{
			/* Handling of passing null pointer */
			u8Execution_indication = SOS_E_NULL_POINTER ;
		}
	} 
	else
	{
		/* Handling of using the SOS module before intiializing it */
		u8Execution_indication = SOS_E_NOT_INTIALIZED_YET ;
	}
	
	return u8Execution_indication ;
}


/** 
 * \brief SOS_Run : The manager of the SOS
 *
 * \param void
 * \return u8 : Indication of the execution if it fails or not 
 *
 **/     
extern void SOS_Run(void) 
{	
	u8 u8Count = 0 ;
	u8 u8Dominant_task_index = 0 ;
	u8 u8Is_there_aReady_task= NO ;
	
	while (1)
	{
		/*
		*	Looping for all of the events looking for the dominant task of the all waiting tasks
		*/
		for (u8Count = 0 ; u8Count < gu8Index ; u8Count++)
		{
			/* Checking for the READY tasks */
			if ( READY == garstSOS_Tasks[u8Count].u8Task_state)
			{
				/* Searching for the first ready task to make it a dominant one temporarily */
				if (NO == u8Is_there_aReady_task)
				{
					u8Dominant_task_index = u8Count ;
					u8Is_there_aReady_task = YES ;
				} 
				else
				{
					/* Now there are more than one waiting task , so according to the priority, the dominant task will be determined */
					if (garstSOS_Tasks[u8Count].u8Priority > garstSOS_Tasks[u8Dominant_task_index].u8Priority)
					{
						u8Dominant_task_index = u8Count ;
					} 
					else
					{
						/* Do nothing */
					}
				}
			} 
			else
			{
				/* Do nothing */
			}
			
		}
		
		if (READY == garstSOS_Tasks[u8Dominant_task_index].u8Task_state)
		{
			garstSOS_Tasks[u8Dominant_task_index].u8Task_state = RUNNING ;
			garstSOS_Tasks[u8Dominant_task_index].pfunc_event();
			
			if (ONE_SHOT == garstSOS_Tasks[u8Dominant_task_index].u8Periodicity )
			{
				SOS_Delete_Task(garstSOS_Tasks[u8Dominant_task_index].pfunc_event);
			}
			else
			{
				garstSOS_Tasks[u8Dominant_task_index].u8Task_state = WAITING ;
			}
		}
		else
		{
			/* Do nothing */
		}
		
		/* Now making No ready task , so that the next time we will determine again from scratch */
		u8Is_there_aReady_task = NO ;
		u8Dominant_task_index = 0;
		
	}
}


ISR(TIMER1_COMPA_vect)
{	
	/*
	*	Flag handling ( It counts up till the RESTART_SYSTEM_TICK_VALUE then go back to 1 )
	*/
	if (gu32System_ticks_number <= RESTART_SYSTEM_TICK_VALUE)
	{
		gu32System_ticks_number ++ ;
	} 
	else
	{
		gu32System_ticks_number = 1 ;
	}
	
	/*
	*	Letting this loop tells which event needs to be executed and which is not ( Depending on the entered delay time and the periodicity )
	*/
	for (gu8Count = 0 ; gu8Count < gu8Index ; gu8Count++)
	{
		if (0 == gu32System_ticks_number % garstSOS_Tasks[gu8Count].u32System_ticks_number)
		{
			garstSOS_Tasks[gu8Count].u8Task_state = READY ;
		}
		else
		{
			/* Do nothing */
		}
	}
}
