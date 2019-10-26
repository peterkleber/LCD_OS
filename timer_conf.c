/*
 * sprint_timer_conf.c
 *
 *  Created on: 20 Sep 2019
 *      Author: RGB
 */

#include "timer.h"

	/* Timers configrations */

 TIMER_cnfg_t TIMER_cnfg_arr [MAX_NUM_OF_TIMERS] =
	{
		/* Timer 0 */
		{
			USED,
			NORMAL_T0_T2,
			NORMAL_OPERATION_T0_T2 ,
			INTERRPUT_OVF_T0,
			130,
			NP,
			NP,
			prescaler_64_T0_T1,
			NP,
			NP,


		},
		/* Timer 1 */
		{
			NOT_USED,
			NORMAL_T1,
			NORMAL_OPERATION_T1_CHANELA,
			INTERRPUT_OVF_T1,
			0,
			NP,
			NP,
			prescaler_8_T0_T1,
			NP,
			RISING_EDGE
		},
		/* Timer 2 */
		{
			NOT_USED,
			NORMAL_T0_T2,
			NORMAL_OPERATION_T0_T2 ,
			INTERRPUT_OVF_T2,
			0,
			NP,
			NP,
			prescaler_8_T2,
			NP,
			NP,
		}
	};





