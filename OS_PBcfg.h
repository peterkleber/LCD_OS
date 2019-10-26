/*
 * OS_PBcfg.h
 *
 *  Created on: 23 Oct 2019
 *      Author: RGB
 */

#ifndef OS_PBCFG_H_
#define OS_PBCFG_H_
#include "std_types.h"
typedef struct
{
	uint8 timer_ID;
	uint8 sysTick_ms;// system tick
}OS_config;

OS_config OS_timer ;
#endif /* OS_PBCFG_H_ */
