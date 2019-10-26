/*
 * Question_Handler_Pc.c
 *
 *  Created on: 25 Oct 2019
 *      Author: RGB
 */

#include "Question_Handler_Pc.h"

uint8 Welcome_Screen_S[] = "SBA7 EL FOL" ;
uint8 Correct_Ans_S[] = "SA7 BS HNKR" ;
uint8 False_Ans_S[] = "hhhh 8lt" ;
uint8 Final_Score_S[] = "NTYGTK :" ;
uint8 End_Screen_S[] = "Have fun !! :D" ;
uint8 Press_Btn_S[] = "Doos ay 7aga" ;
uint8 Skip_Btn_S[] = "Eshta Faks" ;

Questions_ANSWER_Struct QS[NUMBER_OF_QUESTION]=
{

		{
				"3+2=",
				"5  -5  pass ",
				1

		},

		{
				"HELL-",
				"O U pass",
				0

		},

		{
				"MEEN 7beb baba",
				"ana ana pass",
				1
		},

		{
				"meen roo7 baba ?",
				"ana ana pass",
				1

		},

		{
				"kt4 kadr fela2lol",
				"kmnna kamanwa7d pass",
				0

		}

};
