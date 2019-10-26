/*
 * sprint_timer.h
 *
 *  Created on: 20 Sep 2019
 *      Author: RGB
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "timer_conf.h"


#define NULL ((void*)0)
#define OK  1
#define NOK 0
#define TIMER0 0
#define TIMER1 1
#define TIMER2 2

/* MODE FOR TIMER 0 AND TIMER 2 */
#define NORMAL_T0_T2	      0
#define COMPER_T0_T2          8
#define FAST_PWM_T0_T2        72
#define PHASE_CORRECT_T0_T2   64

/* MODE FOR TIMER 1 */

#define NORMAL_T1	          				1
#define COMPER_T1_OCR1        			 	2
#define FAST_PWM_T1_OCR1      				3
#define FAST_PWM_T1_ICR1      				4
#define PHASE_CORRECT_T1_OCR1 				5
#define PHASE_CORRECT_T1_ICR1 			 	6
#define PHASE_CORRECT_T1_8BIT			 	7
#define PHASE_CORRECT_T1_9BIT  				8
#define PHASE_CORRECT_T1_10BIT  			9
#define PHASE_CORRECT_FREQ_CORRECT_ICR1  	10
#define PHASE_CORRECT_FREQ_CORRECT_OCR1  	11
#define FAST_PWM_T1_8BIT       				12
#define FAST_PWM_T1_9BIT       				13
#define FAST_PWM_T1_10BIT      				14
#define COMPER_T1_ICR1        				15


/******************************************/

/* COM pins operation FOR TIMER 0 AND TIMER 2 */

#define  NORMAL_OPERATION_T0_T2    0
#define  TOGGLE_T0_T2			   16
#define  CLEAR_ON_CMP_T0_T2	       32
#define  SET_ON_CMP_T0_T2		   48

/*******************************************/

/* COM pins operation FOR TIMER 1  */

#define  NORMAL_OPERATION_T1_CHANELA          0
#define  TOGGLE_T1_CHANELA		  	 		  64
#define  CLEAR_ON_CMP_T1_CHANELA              128
#define  SET_ON_CMP_T1_CHANELA		   	 	  192

/*******************************************/


#define RISING_EDGE   64
#define FALING_EDGE   0

/*******************************************/
#define INTERRPUT_OFF                  0
#define INTERRPUT_OVF_T0               1
#define INTERRPUT_CMP_T0       	       2
#define INTERRPUT_CMP_OVF_T0           3
#define INTERRPUT_CMP_T2       	       128
#define INTERRPUT_OVF_T2           	   64
#define INTERRPUT_CMP_OVF_T2           192
#define INTERRPUT_OVF_T1      		   4
#define INTERRPUT_CMP_CHANELA_T1       16
#define INTERRPUT_CMP_CHANELB_T1	   8
#define INTERRPUT_ICU_T1       		   32



#define NOT_USED  20
#define USED      21


#define OC0       30
#define OC2       31
#define OC1A      32
#define OC1B      33
#define OC1AB     34


#define prescaler_1_T0_T1      1
#define prescaler_8_T0_T1      2
#define prescaler_64_T0_T1     3
#define prescaler_256_T0_T1    4
#define prescaler_1024_T0_T1   5

#define prescaler_1_T2      1
#define prescaler_8_T2      2
#define prescaler_32_T2     3
#define prescaler_64_T2     4
#define prescaler_128_T2    5
#define prescaler_256_T2    6
#define prescaler_1024_T2   7

#define NP   0xff

/*APIS*/
extern uint8 Timer_init(void);
extern uint8  pwm_generation_fnc(uint8 duty_cycle);
extern  uint8 set_preload (uint8 timer,uint16 Pre_Load);
void timer_set_cb(void(*ptr_fn)(void));



#endif /* TIMER_H_ */
