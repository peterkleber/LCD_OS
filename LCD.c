/*
 * LCD.c
 *
 *  Created on: Oct 24, 2019
 *      Author: PeterKleber
 */

#include "LCD.h"

//--------------------------------------------------------------------------------------------------------------------------//

Std_Func_t LCD_Init(void) {

	typedef enum {
		LCD_Init_1,
		LCD_Init_2,
		LCD_Init_3,
		LCD_Init_4,
		LCD_Init_5,
		LCD_Init_6,
		LCD_Init_Done
	} LCD_Init_State_t;

	static LCD_Init_State_t State = LCD_Init_1;

	switch (State) {
	case (LCD_Init_1):
	//	LCD_DDR = 0xFF; //LCD port is output
	//	DDRA = 0xFF; //LCD port is output
		DIO_set_port_Direction(LCD_DDR, port_output);
	//	LCD_PORT &= (1 << LCD_EN); //LCD_EN = 0
		DIO_Set_Pin_Value (LCD_PORT , LCD_EN ,low);
	//PORTA &= (1 << LCD_EN); //LCD_EN = 0

		if (LCD_Write_Command(0x33) != E_OK) { //$33 for 4-bit mode

		} else {
			State = LCD_Init_2;
		}
		return E_Pending;
		break;
	case (LCD_Init_2):
		if (LCD_Write_Command(0x32) != E_OK) { //$32 for 4-bit mode

		} else {
			State = LCD_Init_3;
		}
		return E_Pending;
		break;
	case (LCD_Init_3):
		if (LCD_Write_Command(0x28) != E_OK) { //$28 for 4-bits, LCD 2 line , 5x7 matrix

		} else {
			State = LCD_Init_4;
		}
		return E_Pending;
		break;
	case (LCD_Init_4):
		if (LCD_Write_Command(0x0E) != E_OK) { //display on, cursor on

		} else {
			State = LCD_Init_5;
		}

		return E_Pending;
		break;
	case (LCD_Init_5):
		if (LCD_Write_Command(0x01) != E_OK) { //Clear Screen

		} else {
			State = LCD_Init_6;
		}
		return E_Pending;
		break;
	case (LCD_Init_6):
		if (LCD_Write_Command(0x06) != E_OK) { //shift cursor right

		} else {
			State = LCD_Init_Done;
		}
		return E_Pending;
		break;
	case (LCD_Init_Done):
		State = LCD_Init_1;
		return E_OK;
		break;
	default:
		return E_NOK;
		break;
	}

}
//--------------------------------------------------------------------------------------------------------------------------//

Std_Func_t LCD_Write_Command(uint8 Command) {
	typedef enum {
		LCD_Write_Command_Sending_High_Nibble,
		LCD_Write_Command_Sending_LOW_Nibble,
		LCD_Write_Command_Done
	} LCD_Write_Command_State_t;

	static LCD_Write_Command_State_t State =
			LCD_Write_Command_Sending_High_Nibble;

	switch (State) {
	case (LCD_Write_Command_Sending_High_Nibble):
	/*	LCD_PORT = (Command & 0xF0); //Send the Highest Nibble in Command to the outPort
		LCD_PORT &= ~(1 << LCD_RS);						//RS = 0 for command
		LCD_PORT &= ~(1 << LCD_RW);						//RW = 0 for write
		LCD_PORT |= (1 << LCD_EN);					//EN = 1 for High-to-Low*/

		DIO_Set_Port_Value (LCD_PORT,(Command & 0xF0));
		DIO_Set_Pin_Value(LCD_PORT, LCD_RS, low);
		DIO_Set_Pin_Value(LCD_PORT, LCD_RW, low);
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, high);

		//_delay_us(DELAY_AFTER_EN);							//wait to make EN wider
		State = LCD_Write_Command_Sending_LOW_Nibble;
		return E_Pending;
		break;

		//_delay_us(100);					//wait for the least nibble of the Command
	case (LCD_Write_Command_Sending_LOW_Nibble):
		//LCD_PORT &= ~(1 << LCD_EN);					//EN = 0 for High-to-Low
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, low);

		/*LCD_PORT = (LCD_PORT & 0x0F) | (Command << 4);// Shift the least nibble by 4 to send the Highest Nibble in   Command  to the outPort
		LCD_PORT &= ~(1 << LCD_RS);						//RS = 0 for command
		LCD_PORT &= ~(1 << LCD_RW);						//RW = 0 for write
		LCD_PORT |= (1 << LCD_EN);					//EN = 1 for High-to-Low*/

		DIO_Set_Port_Value(LCD_PORT, (Command << 4));
		DIO_Set_Pin_Value(LCD_PORT, LCD_RS, low);
		DIO_Set_Pin_Value(LCD_PORT, LCD_RW, low);
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, high);

		//_delay_us(DELAY_AFTER_EN);							//wait to make EN wider
		State = LCD_Write_Command_Done;
		return E_Pending;
		break;

		//_delay_us(100);					//wait for the least nibble of the Command
	case (LCD_Write_Command_Done):
		//LCD_PORT &= ~(1 << LCD_EN);					//EN = 0 for High-to-Low
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, low);
		State = LCD_Write_Command_Sending_High_Nibble;
		return E_OK;
		break;
	default:
		return E_NOK;
	}
}

//--------------------------------------------------------------------------------------------------------------------------//
Std_Func_t LCD_Write_Data(uint8 Data) {
	typedef enum {
			LCD_Write_Data_Sending_High_Nibble,
			LCD_Write_Data_Sending_LOW_Nibble,
			LCD_Write_Data_Done
		} LCD_Write_Command_State_t;

		static LCD_Write_Command_State_t State =
				LCD_Write_Data_Sending_High_Nibble;

		switch (State) {
		case (LCD_Write_Data_Sending_High_Nibble):
		/*	LCD_PORT = (Data & 0xF0); //Send the Highest Nibble in Command to the outPort
			LCD_PORT |= (1 << LCD_RS);						//RS = 1 for Data
			LCD_PORT &= ~(1 << LCD_RW);						//RW = 0 for write
			LCD_PORT |= (1 << LCD_EN);					//EN = 1 for High-to-Low*/
		DIO_Set_Port_Value(LCD_PORT, (Data & 0xF0));
		DIO_Set_Pin_Value(LCD_PORT, LCD_RS, high);
		DIO_Set_Pin_Value(LCD_PORT, LCD_RW, low);
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, high);

			//_delay_us(DELAY_AFTER_EN);							//wait to make EN wider
			State = LCD_Write_Data_Sending_LOW_Nibble;
			return E_Pending;
			break;

			//_delay_us(100);					//wait for the least nibble of the Command
		case (LCD_Write_Data_Sending_LOW_Nibble):
		//	LCD_PORT &= ~(1 << LCD_EN);					//EN = 0 for High-to-Low
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, low);

		/*	LCD_PORT = (LCD_PORT & 0x0F) | (Data << 4);// Shift the least nibble by 4 to send the Highest Nibble in   Command  to the outPort
			LCD_PORT |= (1 << LCD_RS);						//RS = 1 for Data
			LCD_PORT &= ~(1 << LCD_RW);						//RW = 0 for write
			LCD_PORT |= (1 << LCD_EN);					//EN = 1 for High-to-Low*/

		DIO_Set_Port_Value(LCD_PORT,(Data << 4));
		DIO_Set_Pin_Value(LCD_PORT, LCD_RS, high);
		DIO_Set_Pin_Value(LCD_PORT, LCD_RW, low);
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, high);


			//_delay_us(DELAY_AFTER_EN);							//wait to make EN wider
			State = LCD_Write_Data_Done;
			return E_Pending;
			break;

			//_delay_us(100);					//wait for the least nibble of the Command
		case (LCD_Write_Data_Done):
			//LCD_PORT &= ~(1 << LCD_EN);					//EN = 0 for High-to-Low
		DIO_Set_Pin_Value(LCD_PORT, LCD_EN, low);
			State = LCD_Write_Data_Sending_High_Nibble;
			return E_OK;
			break;
		default:
			return E_NOK;
		}
}

//--------------------------------------------------------------------------------------------------------------------------//

Std_Func_t LCD_Set_Cursor_Position( uint8 x , uint8 y)  		// define Cursor Position in the LCD
{

unsigned char firstCharAdr [ ] ={0x80,0xC0,0x94,0xD4} ;			// See the Table of Cursor Position adjustment

return LCD_Write_Command (  firstCharAdr [y-1] + x - 1);

 }
//--------------------------------------------------------------------------------------------------------------------------//

Std_Func_t LCD_Clear (void)
{
return LCD_Write_Command(0x01) ;
}
//--------------------------------------------------------------------------------------------------------------------------//

Std_Func_t LCD_Print_Character(uint8 row, uint8 column, uint8 ch) {
	typedef enum {
		LCD_Set_Cursor_Position_State, LCD_Write_Data_State, LCD_Print_Character_Done
	} LCD_Print_Character_State_t;

	static LCD_Print_Character_State_t State = LCD_Set_Cursor_Position_State;

	switch (State) {
	case (LCD_Set_Cursor_Position_State):
		if (LCD_Set_Cursor_Position(row, column) == E_OK) {
			State = LCD_Write_Data_State;
		}
		return E_Pending;
		break;
	case (LCD_Write_Data_State):
		if (LCD_Write_Data(ch) == E_OK) {
			State = LCD_Print_Character_Done;
		}
		return E_Pending;
		break;
	case (LCD_Print_Character_Done):
		State = LCD_Set_Cursor_Position_State;
		return E_OK;
		break;
	default:
		return E_NOK;
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------//
Std_Func_t LCD_Print_String(uint8 row, uint8 column, uint8 *str) {
	static uint8 Char_Counter = 0;
	typedef enum {
		LCD_Set_Cursor_Position_State,
		LCD_Write_Data_State,
		LCD_Print_String_Done
	} LCD_Print_String_State_t;

	static LCD_Print_String_State_t State = LCD_Set_Cursor_Position_State;

	switch (State) {
	case (LCD_Set_Cursor_Position_State):
		if (LCD_Set_Cursor_Position(row, column) == E_OK) {
			State = LCD_Write_Data_State;
		}
		return E_Pending;
		break;
	case (LCD_Write_Data_State):
		if (str[Char_Counter] != '\0') {
			if (LCD_Write_Data(str[Char_Counter]) == E_OK) {
				Char_Counter++;
			}
		} else {
			Char_Counter = 0 ;
			State = LCD_Print_String_Done;
		}
		return E_Pending;
		break;
	case (LCD_Print_String_Done):
		State = LCD_Set_Cursor_Position_State;
		return E_OK;
		break;
	default:
		return E_NOK;
		break;
	}
}

//--------------------------------------------------------------------------------------------------------------------------//
Std_Func_t LCD_Print_Number(uint8 row, uint8 column, uint8 num) {
	typedef enum {
		LCD_Set_Cursor_Position_State,
		LCD_Write_Data_State,
		LCD_Print_Number_Done
	} LCD_Print_Number_State_t;

	static LCD_Print_Number_State_t State = LCD_Set_Cursor_Position_State;

	switch (State) {
	case (LCD_Set_Cursor_Position_State):
			PORTB |= (1<<PB2);
		if (LCD_Set_Cursor_Position(row, column) == E_OK) {
			State = LCD_Write_Data_State;
		}
		return E_Pending;
		break;
	case (LCD_Write_Data_State):
		if (LCD_Write_Data(num + '0') == E_OK) {
			State = LCD_Print_Number_Done;
		}
		return E_Pending;
		break;
	case (LCD_Print_Number_Done):
		State = LCD_Set_Cursor_Position_State;
	PORTB &= ~(1<<PB2);
		return E_OK;
		break;
	default:
		return E_NOK;
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------//
