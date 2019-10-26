/*
 * Question_Handler_Pc.h
 *
 *  Created on: 25 Oct 2019
 *      Author: RGB
 */

#ifndef QUESTION_HANDLER_PC_H_
#define QUESTION_HANDLER_PC_H_
#include "std_types.h"
#include "Question_Handler_cnfg.h"

typedef struct
{
	uint8 *Question;
	uint8 *Answer;
	uint8 correct_answer;
}Questions_ANSWER_Struct;

extern uint8 Welcome_Screen_S[];
extern uint8 Correct_Ans_S[];
extern uint8 False_Ans_S[];
extern uint8 Final_Score_S[];
extern uint8 End_Screen_S[];
extern uint8 Press_Btn_S[];
extern uint8 Skip_Btn_S[];

extern Questions_ANSWER_Struct QS[NUMBER_OF_QUESTION];

#endif /* QUESTION_HANDLER_PC_H_ */
