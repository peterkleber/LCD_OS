/*
 * OS.c
 *
 *  Created on: ??�/??�/????
 *      Author: COMPUTER SHOW
 */
#include <avr/io.h>
#include"OS.h"
#include "OS_cfg.h"

/******************************************/
typedef struct/*.c*/
{
	void (*task_ptr)(void);
	uint8 task_priority;
	uint16 task_periodicity;  //system tick
	OS_STATES task_state;
}OS_createdTaskBuffer;
/******************************************/
OS_config OS_timer ;
OS_createdTaskBuffer OS_Buffer[MAX_CREATED_TASKS];

/******************************************/
/*saving system tick in global variable*/
uint16 global_resolution = 0;
/*saving created tasks global variable*/
sint8 volatile static created_tasks =0 ;
/*saving tasks states in global variable*/
OS_STATES current_taskState = READY;
/*array of period counter */
static uint16 periodArray[MAX_CREATED_TASKS] = { 0 };
/*flag set in timer ISR every system tick*/
volatile uint8 ISR_flag = 0;

/******************************************/
/*CBK function called every system tick*/
static void OS_timerCalBck(void)
{
	PORTB ^=(1<<PB0);
	uint16 index;
	ISR_flag = 1;
	static uint16 res = 0;/*static variable increment every time isr call  */
	res++;
	if (res == global_resolution)/*resolution time */
	{
		res = 0;

		for (index = 0; index < created_tasks; index++) {
			periodArray[index]++;/*increment flags */
		}
	}
}
/******************************************/
ERRORENUM Sos_Init(const OS_config * configPtr)
{
	uint8 index ;
	ERRORENUM retvalue = OK_STATE;
	if (configPtr == NULL)
	{
		retvalue = NOK_NULL;
	}

	else
	{
		for (index = 0; index < MAX_CREATED_TASKS; index++)
		{
			OS_Buffer[index].task_state = 0;
			OS_Buffer[index].task_periodicity = 0;
			OS_Buffer[index].task_ptr = NULL;
			OS_Buffer[index].task_priority = 0;
		}

		if (0 == configPtr->timer_ID)
		{
			TIMER_cnfg_arr[configPtr->timer_ID].used = USED;
		}

		else
		{
			retvalue = INVALID_TIMER;
		}

		timer_set_cb(OS_timerCalBck);
		global_resolution = configPtr->sysTick_ms;
		Timer_init();
	}

	return retvalue;

}
/******************************************/

ERRORENUM Sos_Create_Task(OS_taskPtr task_ptr,uint8 taskPriority,uint16 task_periodicity)
{

	OS_createdTaskBuffer temp1 ,temp2 ;
	uint8 local_index = 0 ;
	uint8 volatile flag=0;
	ERRORENUM retvalue = OK_STATE;

	if(task_ptr == NULL)
	{
		retvalue = NOK_NULL;
	}

	else if(created_tasks > MAX_CREATED_TASKS)
	{
		retvalue = NOK_NOT_AVAILBLE;
	}
	else if(created_tasks < MAX_CREATED_TASKS)
	{
		if(0==created_tasks)
		{
			OS_Buffer[created_tasks].task_priority = taskPriority;
			OS_Buffer[created_tasks].task_periodicity = task_periodicity;
			OS_Buffer[created_tasks].task_ptr = task_ptr;
			OS_Buffer[created_tasks].task_state = READY;
			created_tasks++;



		}

		else if(taskPriority>=OS_Buffer[created_tasks-1].task_priority)
		{

			OS_Buffer[created_tasks].task_priority = taskPriority;
			OS_Buffer[created_tasks].task_periodicity = task_periodicity;
			OS_Buffer[created_tasks].task_ptr = task_ptr;
			OS_Buffer[created_tasks].task_state = READY;
			created_tasks++;
		}


		else
		{
			for(local_index=0;local_index<created_tasks;local_index++)
			{

				if(taskPriority<OS_Buffer[local_index].task_priority)
				{

					if (flag==0)
					{

						temp1=OS_Buffer[local_index];
						OS_Buffer[local_index].task_periodicity=task_periodicity;
						OS_Buffer[local_index].task_priority=taskPriority;
						OS_Buffer[local_index].task_ptr=task_ptr;
						OS_Buffer[local_index].task_state=READY;
						flag=1;
						created_tasks++;

					}
					else if (flag==1)
					{

						temp2=OS_Buffer[local_index];
						OS_Buffer[local_index]=temp1;
						temp1=temp2;
					}
				}


			}

		}



	}

	return retvalue;

}

void Sos_Run(void)
{

	uint8 loc_index = 0;
	while(1)
	{
		if(ISR_flag == 1)
		{

			for(loc_index=0;loc_index< created_tasks;loc_index++)
			{
				if(periodArray[loc_index] >= OS_Buffer[loc_index].task_periodicity)
				{

					OS_Buffer[loc_index].task_ptr();
					periodArray[loc_index] = 0;
				}

			}
			ISR_flag = 0;

		}
	}




}

ERRORENUM Sos_Delete_Task(OS_taskPtr task_ptr)
{
	uint8 retvalue = OK_STATE;
	uint8 local_index = 0;
	uint8 delete_position = 0;

	if (task_ptr == NULL)
	{
		retvalue = NOK_NULL;
	}

	else if (OS_Buffer[created_tasks].task_ptr==task_ptr)
	{
		created_tasks--;
	}

	else
	{
		for(local_index=0;local_index<created_tasks;local_index++)
		{
			if(OS_Buffer[local_index].task_ptr==task_ptr)
			{
				delete_position = local_index;
				break;
			}
			else
			{
				retvalue =INVALID_TASK;
			}

		}
		for(local_index=delete_position;local_index<created_tasks;local_index++)
		{
			OS_Buffer[local_index] = OS_Buffer[local_index+1];
		}
		created_tasks--;


	}
	return retvalue;
}
