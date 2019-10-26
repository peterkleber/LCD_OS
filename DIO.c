/*
 * DIO.c
 *
 *  Created on: Oct 25, 2019
 *      Author: PeterKleber
 */

#include "DIO.h"

void DIO_Set_Pin_Direction (uint8 port_id , uint8 pin_number,uint8 direction)
{

	if (direction==output)
	{
		switch(port_id)
		{
		case DIO_PORTA_ID :

			set_bit(DDRA,pin_number);
			break ;
		case DIO_PORTB_ID :
			set_bit(DDRB,pin_number);
			break ;
		case DIO_PORTC_ID :
			set_bit(DDRC,pin_number);
			break ;
		case DIO_PORTD_ID :
			set_bit(DDRD,pin_number);
			break ;
		}
	}
	else
	{

		switch(port_id)
		{
		case DIO_PORTA_ID :
			clear_bit(DDRA,pin_number);
			break ;
		case DIO_PORTB_ID :
			clear_bit(DDRB,pin_number);
			break ;
		case DIO_PORTC_ID :
			clear_bit(DDRC,pin_number);
			break ;
		case DIO_PORTD_ID :
			clear_bit(DDRD,pin_number);
			break ;
		}



	}
}

void DIO_Set_Pin_Value (uint8 port_id , uint8 pin_number,uint8 value)
{

	if (value==output)
	{
		switch(port_id)
		{
		case DIO_PORTA_ID :
			set_bit(PORTA,pin_number);
			break ;
		case DIO_PORTB_ID :
			set_bit(PORTB,pin_number);
			break ;
		case DIO_PORTC_ID :
			set_bit(PORTC,pin_number);
			break ;
		case DIO_PORTD_ID :
			set_bit(PORTD,pin_number);
			break ;
		}
	}
	else
	{

		switch(port_id)
		{
		case DIO_PORTA_ID :
			clear_bit(PORTA,pin_number);
			break ;
		case DIO_PORTB_ID :
			clear_bit(PORTB,pin_number);
			break ;
		case DIO_PORTC_ID :
			clear_bit(PORTC,pin_number);
			break ;
		case DIO_PORTD_ID :
			clear_bit(PORTD,pin_number);
			break ;
		}


	}
}

uint8 DIO_Get_Pin_Value (uint8 port_id , uint8 pin_number)
{
	uint8 reading_value ;

	switch(port_id)
	{
	case DIO_PORTA_ID :
		reading_value= get_bit(PINA,pin_number);
		break ;
	case DIO_PORTB_ID :
		reading_value= get_bit(PINB,pin_number);
		break ;
	case DIO_PORTC_ID :
		reading_value= get_bit(PINC,pin_number);
		break ;
	case DIO_PORTD_ID :
		reading_value=get_bit(PIND,pin_number);
		break ;
	}

	return reading_value ;

}
void DIO_Set_Port_Value (uint8 port_id,uint8 value)
{
	switch(port_id)
			{
			case DIO_PORTA_ID :

				PORTA=value ;
				break ;
			case DIO_PORTB_ID :
				PORTB=value ;
				break ;
			case DIO_PORTC_ID :
				PORTC=value ;
				break ;
			case DIO_PORTD_ID :
				PORTD=value ;
				break ;
			}
}


void DIO_set_port_Direction (uint8 port_id,uint8 direction)
{

	switch(port_id)
				{
				case DIO_PORTA_ID :

					DDRA=direction ;
					break ;
				case DIO_PORTB_ID :
					DDRB=direction ;
					break ;
				case DIO_PORTC_ID :
					DDRC=direction ;
					break ;
				case DIO_PORTD_ID :
					DDRD=direction ;
					break ;
				}

}

