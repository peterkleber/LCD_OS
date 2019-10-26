/*
 * main.c
 *
 *  Created on: Oct 22, 2019
 *      Author: PeterKleber & Ahmed Ehab
 */
/*
#include<util/delay.h>
#include "LCD.h"*/
#include"OS.h"
#include "Question_Handler.h"

int main(void)
{
	DDRB = 0xFF ;

	Sos_Init(&OS_timer);

	Sos_Create_Task(Tick_Task_2msec , 1, 2);
	Sos_Create_Task(KEYPad_Task_30ms , 2, 30);
	Sos_Create_Task(Question_Task_1sec, 3, 1000);

	SREG |= (1<<7);
		Sos_Run();
}
