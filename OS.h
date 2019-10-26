/*
 * OS.h
 *
 *  Created on: ??�/??�/????
 *      Author: COMPUTER SHOW
 */

#ifndef OS_H_
#define OS_H_

#include"std_types.h"
#include"timer.h"
#include "OS_PBcfg.h"

typedef void(*OS_taskPtr)(void);

typedef enum{OK_STATE,NOK_STATE,NOK_NULL,NOK_NOT_AVAILBLE,INVALID_TIMER,INVALID_TASK}ERRORENUM;
typedef enum{RUNNING,READY,WAITING,DELETE}OS_STATES;






ERRORENUM Sos_Init(const OS_config * configPtr);
void Sos_Run(void); // algorithm
ERRORENUM Sos_Create_Task(OS_taskPtr task_ptr,uint8 taskPriority,uint16 task_periodicity);
ERRORENUM Sos_Delete_Task(OS_taskPtr task_ptr);
//void OS_timerCalBck(void);

#endif /* OS_H_ */

