/*
 * Question_Handler.h
 *
 *  Created on: 25 Oct 2019
 *      Author: RGB
 */

#ifndef QUESTION_HANDLER_H_
#define QUESTION_HANDLER_H_
#include "Question_Handler_Pc.h"
#include<avr/io.h>
#include "LCD.h"
#include "KeyPad.h"


void Question_Task_1sec(void);
void Tick_Task_2msec(void);
void KEYPad_Task_30ms(void);



#endif /* QUESTION_HANDLER_H_ */
