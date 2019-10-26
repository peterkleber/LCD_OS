/*
 * LCD.h
 *
 *  Created on: Oct 24, 2019
 *      Author: PeterKleber
 */

#ifndef LCD_H_
#define LCD_H_

//define libraries

#include "std_types.h"
#include "DIO.h"

//#define LCD_PORT PORTA //LCD DATA PORT from PD4 to PD7 // we can’t take PD3 as it is existed in least nibble.
//#define LCD_DDR DDRA //LCD DATA DDR from PD4 to PD7

#define LCD_PORT DIO_PORTA_ID //LCD DATA PORT from PD4 to PD7 // we can’t take PD3 as it is existed in least nibble.
#define LCD_DDR DIO_PORTA_ID //LCD DATA DDR from PD4 to PD7

//define LCD Control Pins MACROS
#define	LCD_RS           		 1				//LCD	RS
#define	LCD_RW    				 2				//LCD	RW
#define	LCD_EN     			     3				//LCD	EN


//LCD_4Bits_FUNCTIONS PROTOTYPE
Std_Func_t LCD_Init (void);
Std_Func_t LCD_Write_Command ( uint8 Command );
Std_Func_t LCD_Write_Data ( uint8 Data );
Std_Func_t LCD_Set_Cursor_Position( uint8 x , uint8 y);   		// define Cursor Position in the LCD
Std_Func_t LCD_Clear (void);

Std_Func_t LCD_Print_Character( uint8 row , uint8 column , uint8 ch );
Std_Func_t LCD_Print_String( uint8 row , uint8 column , uint8 *str );
Std_Func_t LCD_Print_Number(uint8 row , uint8 column , uint8 num); //number to print is 0-9


#endif /* LCD_H_ */
