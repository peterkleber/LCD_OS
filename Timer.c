/*
 * sprint_Timer.c
 *
 *  Created on: 20 Sep 2019
 *      Author: RGB
 */
#include <avr/interrupt.h>

#include "timer.h"
#include "registers.h"

static uint8   prescaler(uint8 timer , uint8 pre_scaler) ;
static uint8   mode_fnc (uint8 timer , uint8 Mode) ;
static uint8   options(uint8 timer);
static uint8  Timer0_Timer2_option(uint8 timer,uint8 Com_Mode);
static uint8 Timer1_option (uint8 timer,uint8 Com_Mode,uint8 icu_edge);
static uint8 set_OCR (uint8 timer,uint16 cmp_value);
static uint8 set_ICR (uint8 timer,uint16 ICR);
static uint8 Timer_interrupt_init(uint8 timer,uint8 interrupt);


static volatile void (*g_cbk_ptr) (void) = NULL;



uint8 Timer_init(void)
{uint8 retvalue = OK ;
	uint8 loop_index = 0;

	for(loop_index=0;loop_index<MAX_NUM_OF_TIMERS;loop_index++)
	{
		if(TIMER_cnfg_arr[loop_index].used==USED) //this timer is used or not
		{

			retvalue = prescaler(loop_index,TIMER_cnfg_arr[loop_index].prescaler);
			retvalue = mode_fnc(loop_index,TIMER_cnfg_arr[loop_index].mode);
			retvalue = options(loop_index);
			retvalue =Timer_interrupt_init(loop_index,TIMER_cnfg_arr[loop_index].Interrupt);
			retvalue = set_preload (loop_index,TIMER_cnfg_arr[loop_index].Preload_Val);
			retvalue = set_OCR (loop_index,TIMER_cnfg_arr[loop_index].Compare_Val);
			if (1==loop_index)
			{
				retvalue = set_ICR (loop_index,TIMER_cnfg_arr[loop_index].ICR1_val);

			}

		}
		else if(TIMER_cnfg_arr[loop_index].used==NOT_USED)
		{
			//loop_index++;
		}
		else
		{
			retvalue=NOK;
		}
	}

	return retvalue ;
}

/*function to set prescaler that takes timer value and prescaler value as argument */
uint8 prescaler(uint8 timer , uint8 pre_scaler)
{uint8 retvalue = OK ;
	switch (timer)
	{
		case 0 :
			REG_TCCR0 &=0XF8;/* andding reg with 11111000 to clear first 3 bits of the register*/
			REG_TCCR0 |= pre_scaler ;
			break ;
		case 1 :
			REG_TCCR1B &=0XF8;
			REG_TCCR1B |= pre_scaler ;
			break ;
		case 2 :
			REG_TCCR2 &=0XF8;
			REG_TCCR2 |= pre_scaler ;
					break ;

		default :
			retvalue = NOK;
			break ;
	}
	return retvalue ;
}

/*function to set mode that takes timer value and mode value as argument */
uint8 mode_fnc (uint8 timer , uint8 Mode)
{uint8 retvalue = OK ;
	switch (timer)
		{
	/*set timer0 mode */

		case 0 :
			REG_TCCR0 &=0XB7; /*andding reg with 101101111*/
			REG_TCCR0 |= Mode ; /*orring reg with Mode check timer.h*/
				break ;


				/*set timer1 mode */
		case 1 :
				switch(Mode)
				{
				case NORMAL_T1 :

					REG_TCCR1A &=0xFC; /*andding reg with 11111100*/
					REG_TCCR1A |=0;
					REG_TCCR1B  &=0xE7;/*andding reg with 11100111*/
					REG_TCCR1B |=0;

					break ;
				case COMPER_T1_OCR1 :

					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=0;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=8;

					break ;

				case FAST_PWM_T1_OCR1 :

					REG_TCCR1A &=0xFC; /*andding reg with 11111100*/
					REG_TCCR1A |=3;
					REG_TCCR1B  &=0xE7;/*andding reg with 11100111*/
					REG_TCCR1B |=24;

					break ;

				case PHASE_CORRECT_T1_OCR1 :

					REG_TCCR1A &=0xFC; /*andding reg with 11111100*/
					REG_TCCR1A |=3;
					REG_TCCR1B  &=0xE7;/*andding reg with 11100111*/
					REG_TCCR1B |=16;

					break ;

				case FAST_PWM_T1_ICR1 :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=2;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=24;
					break ;
				case FAST_PWM_T1_8BIT :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=1;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=8;
									break ;
				case FAST_PWM_T1_9BIT :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=2;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=8;
									break ;
				case FAST_PWM_T1_10BIT :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=3;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=8;
									break ;
				case PHASE_CORRECT_T1_ICR1 :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=2;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=24;
									break ;

				case PHASE_CORRECT_T1_8BIT :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=1;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=0;
									break ;
				case PHASE_CORRECT_T1_9BIT :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=2;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=0;
									break ;
				case PHASE_CORRECT_T1_10BIT :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=3;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=0;
									break ;
				case PHASE_CORRECT_FREQ_CORRECT_ICR1 :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=0;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=16;
									break ;
				case PHASE_CORRECT_FREQ_CORRECT_OCR1 :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=1;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=16;
									break ;
				case COMPER_T1_ICR1 :
					REG_TCCR1A &=0xFC;
					REG_TCCR1A |=0;
					REG_TCCR1B  &=0xE7;
					REG_TCCR1B |=24;
									break ;


				default :

					retvalue = NOK;
					break ;
				}

				break ;
				/*set timer2 mode */

		case 2 :
			REG_TCCR2 &=0XB7;
			REG_TCCR2 |= Mode ;
				break ;


		default :
				retvalue = NOK;
				break ;
		}
		return retvalue ;


}


/*function to that takes timer value and oco , oc2 pins value and
 * set which mode you want to use*/
uint8 Timer0_Timer2_option (uint8 timer,uint8 Com_Mode)
{
	uint8 retvalue = OK ;
	switch(timer)
	{
	case 0 :
		REG_TCCR0 &=0xCF;/*andding with 11001111*/
		REG_TCCR0 |=Com_Mode ;
		break ;
	case 2 :
		REG_TCCR2 &=0xCF;/*andding with 11001111*/
		REG_TCCR2 |=Com_Mode ;
		break;
	default :
		retvalue = NOK;
		break ;
	}
	return retvalue ;
}



/*function to that takes timer value and oc1 , icu  pins value and
 * set which mode you want to use*/
uint8 Timer1_option (uint8 timer,uint8 Com_Mode,uint8 icu_edge)
{
	uint8 retvalue = OK ;
	if (timer ==1)
	{
		REG_TCCR1A &=0x0F;/*andding with 00001111*/
		REG_TCCR1A |= Com_Mode ;
		REG_TCCR1B &=0XBF;/*adding 10111111*/
		REG_TCCR1B |=icu_edge;

	}

	else
	{
		retvalue = NOK;
	}
	return retvalue ;

}
/*fuction to switch between timers option for timer 0  , 1 and 2*/
uint8 options(uint8 timer)
	{
	uint8 retvalue = OK ;
	 switch(timer)
	 {
	 case 0 :
			retvalue = Timer0_Timer2_option( timer,TIMER_cnfg_arr[timer].com_mode);
			break;
	 case 1 :
			retvalue = Timer1_option (timer,TIMER_cnfg_arr[timer].com_mode,TIMER_cnfg_arr[timer].ICU_Edge);
			break ;
	 case 2 :
		 retvalue = Timer0_Timer2_option( timer,TIMER_cnfg_arr[timer].com_mode);
			break;
	 default :
		retvalue = NOK;
	 		break ;

	 }
		return retvalue ;
	}

/* function to set preload value */
uint8 set_preload (uint8 timer,uint16 Pre_Load)
{
	uint8 retvalue = OK ;
	switch(timer)
	{
	case 0 :
		REG_TCNT0= Pre_Load ;
		break ;
	case 1 :
		REG_TCNT1H= (Pre_Load&0xF0);
		REG_TCNT1L=(Pre_Load&0x0F);
		break;
	case 2 :
		REG_TCNT2= Pre_Load ;
		break ;

	default :
			retvalue = NOK;
		 		break ;
	}
	return retvalue ;

}
/* function to set OCR value */

uint8 set_OCR (uint8 timer,uint16 cmp_value)
{
	uint8 retvalue = OK ;
	switch(timer)
		{
		case 0 :
			REG_OCR0= cmp_value ;
			break ;
		case 1 :
			REG_OCR1AH= (cmp_value&0xF0);
			REG_OCR1AL=(cmp_value&0x0F);
			break;
		case 2 :
			REG_OCR2= cmp_value ;
			break ;

		default :
				retvalue = NOK;
			 		break ;
		}
		return retvalue ;

}

/* function to set ICR value */

uint8 set_ICR (uint8 timer,uint16 ICR)
{uint8 retvalue = OK ;
	if (timer ==1)
		{
		REG_ICR1H =(ICR&0xF0);
		REG_ICR1L =(ICR&0x0F);

		}
		return retvalue ;
}
/*timer to set which interrupt to use for timer*/
uint8 Timer_interrupt_init(uint8 timer,uint8 interrupt )
{uint8 retvalue = OK ;
	switch(timer)
		 {
		 case 0 :
			 REG_TIMSK &=0xFC;     /*andding reg with 11111100*/
			 REG_TIMSK |=interrupt;
				break;
		 case 1 :
			 REG_TIMSK &=0xC3;
			 REG_TIMSK |=interrupt;
				break ;
		 case 2 :
			 REG_TIMSK &=0x3F;
			 REG_TIMSK |=interrupt;
				break;
		 default :
			retvalue = NOK;
		 		break ;

		 }
			return retvalue ;

}

uint8 pwm_generation_fnc(uint8 duty_cycle)
{uint8 value ;


	value = 255-((duty_cycle*255)/100);
	REG_TCNT2 = value ;
	return value;

}




ISR(TIMER0_OVF_vect)
{
	set_preload(0,131);
	if (*g_cbk_ptr != NULL)
	{
		(*g_cbk_ptr) ();
	}
}
void timer_set_cb(void(*ptr_fn)(void))
{
	g_cbk_ptr = ptr_fn;
}
