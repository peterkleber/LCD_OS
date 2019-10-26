/*
 * KeyPad.c
 *
 *  Created on: Oct 26, 2019
 *      Author: PeterKleber
 */

#include"KeyPad.h"


Std_Func_t KeyPad_Init(void){
	//DIO_set_port_Direction (KeyPad_PORT,port_output);
	DIO_Set_Pin_Direction (KeyPad_PORT, KeyPad_C1 ,input);
	DIO_Set_Pin_Direction (KeyPad_PORT, KeyPad_C2 ,input);
	DIO_Set_Pin_Direction (KeyPad_PORT, KeyPad_C3 ,input);

	DIO_Set_Pin_Direction (KeyPad_PORT, KeyPad_R1 ,output);
	DIO_Set_Pin_Direction (KeyPad_PORT, KeyPad_R2 ,output);
	DIO_Set_Pin_Direction (KeyPad_PORT, KeyPad_R3 ,output);

	DIO_Set_Pin_Value (KeyPad_PORT , KeyPad_R1,low);
	DIO_Set_Pin_Value (KeyPad_PORT , KeyPad_R2,low);
	DIO_Set_Pin_Value (KeyPad_PORT , KeyPad_R3,low);

return E_OK;
}

Std_Func_t KeyPad_GetKeyPressed(uint8 *Key){

	if(DIO_Get_Pin_Value (KeyPad_PORT , KeyPad_C1 ) == low){
		*Key = Key_1 ;
	}
	else if(DIO_Get_Pin_Value (KeyPad_PORT , KeyPad_C2 ) == low){
		*Key = Key_2 ;
	}
	else if(DIO_Get_Pin_Value (KeyPad_PORT , KeyPad_C3 ) == low){
		*Key = Key_3 ;
	}
	else{
		*Key = No_key ;
	}
	return E_OK;
}
