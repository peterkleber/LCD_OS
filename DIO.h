/*
 * DIO.h
 *
 *  Created on: Oct 25, 2019
 *      Author: PeterKleber
 */

#ifndef DIO_H_
#define DIO_H_

#define set_bit(var,bit) (var|=(1<<bit))
#define clear_bit(var,bit) (var&=(~(1<<bit)))
#define toggle_bit(var,bit) (var^=(1<<bit))
#define get_bit(var,bit)  ((var&(1<<bit))>>bit)

#include "avr/io.h"
#include "std_types.h"

#define pin0 0
#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4
#define pin5 5
#define pin6 6
#define pin7 7

#define DIO_PORTA_ID 0
#define DIO_PORTB_ID 1
#define DIO_PORTC_ID 2
#define DIO_PORTD_ID 3

#define high 1
#define low 0

#define output 1
#define input 0

#define port_output 0xFF
#define port_input 0x00


void DIO_Set_Pin_Direction (uint8 port_id , uint8 pin_number,uint8 direction);
void DIO_Set_Pin_Value (uint8 port_id , uint8 pin_number,uint8 value);
uint8 DIO_Get_Pin_Value (uint8 port_id , uint8 pin_number);
void DIO_Set_Port_Value (uint8 port_id,uint8 value);
void DIO_set_port_Direction (uint8 port_id,uint8 direction);

#endif /* DIO_H_ */
