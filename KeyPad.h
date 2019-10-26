/*
 * KeyPad.h
 *
 *  Created on: Oct 26, 2019
 *      Author: PeterKleber
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"
#include "std_types.h"

typedef enum {Key_1,Key_2,Key_3,No_key}Keys_t ;

#define KeyPad_PORT DIO_PORTC_ID

#define KeyPad_C1 pin5
#define KeyPad_C2 pin6
#define KeyPad_C3 pin7

#define KeyPad_R1 pin2
#define KeyPad_R2 pin3
#define KeyPad_R3 pin4

Std_Func_t KeyPad_Init(void);
Std_Func_t KeyPad_GetKeyPressed(uint8 *Key);

#endif /* KEYPAD_H_ */
