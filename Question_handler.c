/*
 * QUEStion_handler.c
 *
 *  Created on: 25 Oct 2019
 *      Author: RGB
 */

#include "Question_Handler.h"
/*********************************************************/

typedef enum{Welcome,Key_Pressed,Question,Final_Score,End_Screen}Question_Task_State_t;
typedef enum{Display_Question,Display_Answer,Question_Result}Question_Process;

typedef enum{Screen1,Screen2,}Screen_States_t;

//typedef enum{Goto_Question,Goto_Welcome}KeyPad_GoTo_t;

typedef enum{LCD_Idle,LCD_Requested,LCD_Finished}LCD_Status;
typedef enum{Key_Idle,Key_Requested,Key_Finished}KeyPad_Status;


volatile static uint8 Row=1;
volatile static uint8 Clm=1;
volatile static uint8 *data_to_print ;

volatile static uint8 Score_Counter = 0;

volatile static uint8 Global_Keypad_Data ;
volatile static uint8 Question_Counter = 0;

volatile static Question_Task_State_t Question_Task_State = Welcome ;
volatile static Question_Process Question_process_state =Display_Question;
//KEYPAD_PROCESS static KEY_PRESS = WELCOME_PRESS ;
volatile static KeyPad_Status global_Keypad_flag= Key_Idle;

volatile static Screen_States_t Welcom_Screen_Status = Screen1 ;
volatile static Screen_States_t Score_Screen_Status = Screen1 ;

//volatile static KeyPad_GoTo_t KeyPad_GoTo = Goto_Welcome ;

volatile static LCD_Status global_Print_data_flag = LCD_Idle;

volatile static uint8 LCD_Clear_Req = 0 ;

volatile static uint8 LCD_Init_Flag = 0;
volatile static uint8 KeyPad_Init_Flag = 0;

volatile static uint8 Score_Counter_S[] = "0" ;
//A string holding the score because we print "strings"


/***********************************************************/
#define LCD_FILL_DATA(ROW,CLM,DATA)  Row=ROW;  \
									 Clm=CLM;  \
									 data_to_print=DATA

/*********************************************************/

void Question_Task_1sec(void) {
	if (LCD_Init_Flag == 1) {
		if (KeyPad_Init_Flag == 1) {

		switch (Question_Task_State) {
		case Welcome:
			switch(Welcom_Screen_Status){
			case Screen1 :
			if (LCD_Idle == global_Print_data_flag) {

				LCD_Clear_Req = 1;
				global_Print_data_flag = LCD_Requested;
				LCD_FILL_DATA(1, 1, Welcome_Screen_S);

			} else if (LCD_Finished == global_Print_data_flag) {
				global_Print_data_flag = LCD_Idle;
				Welcom_Screen_Status = Screen2 ;
			}
			break;
			case Screen2 :
			if (LCD_Idle == global_Print_data_flag) {
				global_Print_data_flag = LCD_Requested;
				LCD_FILL_DATA(1, 2, Press_Btn_S);

			} else if (LCD_Finished == global_Print_data_flag) {
				global_Print_data_flag = LCD_Idle;
				Welcom_Screen_Status = Screen1 ;
				Question_Task_State = Key_Pressed;

			}
			break;
			}
			break;
			/////////////////////////////////////////////////////////////////////////////////////
		case Key_Pressed :

					if(Key_Idle==global_Keypad_flag)
					{
						global_Keypad_flag=Key_Requested;
					}
					else if(Key_Finished==global_Keypad_flag)
					{
						global_Keypad_flag=Key_Idle;

						Question_Task_State=Question;

					}
				break;
				/////////////////////////////////////////////////////////////////////////////////////
		case Question:
			if (Question_Counter > (NUMBER_OF_QUESTION -1)) { //(NUMBER_OF_QUESTION -1)
				Question_Task_State = Final_Score;
				Question_Counter = 0;
			} else {
				switch (Question_process_state) {

				case Display_Question:
					if (LCD_Idle == global_Print_data_flag) {
						LCD_Clear_Req = 1;
						global_Print_data_flag = LCD_Requested;
						LCD_FILL_DATA(1, 1, QS[Question_Counter].Question);
					} else if (LCD_Finished == global_Print_data_flag) {
						global_Print_data_flag = LCD_Idle;
						Question_process_state = Display_Answer;
					}
					break;
				case Display_Answer:
					if (LCD_Idle == global_Print_data_flag) {
						global_Print_data_flag = LCD_Requested;
						LCD_FILL_DATA(1, 2, QS[Question_Counter].Answer);
					} else if (LCD_Finished == global_Print_data_flag) {
						global_Print_data_flag = LCD_Idle;
						Question_Task_State = Key_Pressed;
						Question_process_state = Question_Result;
					}
					break;

				case Question_Result:
					if (LCD_Idle == global_Print_data_flag) {
						LCD_Clear_Req = 1;
						global_Print_data_flag = LCD_Requested;
						if(Global_Keypad_Data == Key_3){
							LCD_FILL_DATA(1, 1,Skip_Btn_S );
						}
						else{
						if (QS[Question_Counter].correct_answer
								== Global_Keypad_Data) {
							LCD_FILL_DATA(1, 1, Correct_Ans_S);
							Score_Counter += 1 ;
						} else {
							LCD_FILL_DATA(1, 1, False_Ans_S);
						}
						}
					} else if (LCD_Finished == global_Print_data_flag) {
						global_Print_data_flag = LCD_Idle;
						Question_Counter++;
						Question_process_state = Display_Question;
					}
					break;

				}
			}
			break;
			/////////////////////////////////////////////////////////////////////////////////////
		case Final_Score:
			switch (Score_Screen_Status) {
			case Screen1:
				if (LCD_Idle == global_Print_data_flag) {
					LCD_Clear_Req = 1;
					global_Print_data_flag = LCD_Requested;
					LCD_FILL_DATA(1, 1, Final_Score_S);
				}

				else if (LCD_Finished == global_Print_data_flag) {
					global_Print_data_flag = LCD_Idle;
					Score_Screen_Status = Screen2;
				}
				break;
			case Screen2:
				if (LCD_Idle == global_Print_data_flag) {
					global_Print_data_flag = LCD_Requested;
					Score_Counter_S[0] = (Score_Counter + '0');
					LCD_FILL_DATA(9, 1, Score_Counter_S);

				}

				else if (LCD_Finished == global_Print_data_flag) {
					global_Print_data_flag = LCD_Idle;
					Score_Screen_Status = Screen1;
					Question_Task_State = End_Screen;
				}
				break;
			}
			break;
			/////////////////////////////////////////////////////////////////////////////////////
		case End_Screen:
			if (LCD_Idle == global_Print_data_flag) {
				LCD_Clear_Req = 1;
				global_Print_data_flag = LCD_Requested;
				LCD_FILL_DATA(1, 1, End_Screen_S);

			} else if (LCD_Finished == global_Print_data_flag) {
				global_Print_data_flag = LCD_Idle;
				Question_Task_State = Welcome ;
			}
					break;
			}
	}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tick_Task_2msec(void) {

	if(LCD_Init_Flag == 0){
		if((LCD_Init() == E_OK)){
			LCD_Init_Flag = 1;
		}
	}
	else if (LCD_Init_Flag == 1){

		if(LCD_Clear_Req == 1 ){
			if(LCD_Clear () == E_OK){
				LCD_Clear_Req = 0 ;
			}
		}

		else if (LCD_Requested == global_Print_data_flag) {
		if (E_OK != LCD_Print_String(Row, Clm,data_to_print)) { // g_String // data_to_print
		}
		else {
			global_Print_data_flag = LCD_Finished;
		}

	}

	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KEYPad_Task_30ms(void) {
	typedef enum {
		First_Reading, Second_Reading
	} Debouncing_Counter_t;
	static Debouncing_Counter_t Debouncing_Counter = First_Reading;
	static uint8 First_Reading_Value = 3; //3 outside range
	static uint8 Second_Reading_Value = 3; //3 outside range

	if (KeyPad_Init_Flag == 0) {
		if (KeyPad_Init() == E_OK) {
			KeyPad_Init_Flag = 1;
		}
	} else if (KeyPad_Init_Flag == 1) {
		if (Key_Requested == global_Keypad_flag) {
			switch (Debouncing_Counter) {
			case First_Reading:
				if (KeyPad_GetKeyPressed(&First_Reading_Value) == E_OK) {
					if(First_Reading_Value != No_key){
					Debouncing_Counter = Second_Reading;
					}
				}
				break;
			case Second_Reading:
				if (KeyPad_GetKeyPressed(&Second_Reading_Value) == E_OK) {
					if(Second_Reading_Value != No_key){
					if (First_Reading_Value == Second_Reading_Value) {
						Global_Keypad_Data = Second_Reading_Value;
						global_Keypad_flag = Key_Finished;
						First_Reading_Value = 3;
						Second_Reading_Value = 3;
						Debouncing_Counter = First_Reading;

					} else {
						First_Reading_Value = Second_Reading_Value;
					}
				}
				}
				break;

			}

		}
	}
}

