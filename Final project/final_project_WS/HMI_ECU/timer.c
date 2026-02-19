/*
 * timer.c
 *
 *  Created on: Oct 25, 2025
 *      Author: Abdullah Said
 */

#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use Registers */
#include <avr/interrupt.h> /* For ISR */

/* Global variables to hold the address of the call back function in the application FOR timer0 */
static volatile void (*g_callBackPtr_TIMER0)(void) = NULL_PTR;

/* Global variables to hold the address of the call back function in the application FOR timer1 */
static volatile void (*g_callBackPtr_TIMER1)(void) = NULL_PTR;

/* Global variables to hold the address of the call back function in the application FOR timer2*/
static volatile void (*g_callBackPtr_TIMER2)(void) = NULL_PTR;






/*ISR for timer 1 compare com a
 * */
ISR (TIMER1_COMPA_vect) {

	if(g_callBackPtr_TIMER1 != NULL_PTR){
			/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_TIMER1)(); /* another method to call the function using pointer to function g_callBackPtr(); */

	}
}

/*ISR for timer 1 overflow
 * */
ISR (TIMER1_OVF_vect) {

	if(g_callBackPtr_TIMER1 != NULL_PTR){
				/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr_TIMER1)(); /* another method to call the function using pointer to function g_callBackPtr(); */

		}

}
/*ISR for timer 0 compare
 * */
ISR (TIMER0_COMP_vect) {
	if (g_callBackPtr_TIMER0 != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_TIMER0)(); /* another method to call the function using pointer to function g_callBackPtr(); */

	}

}
/*ISR for timer 0 overflow mode
 * */
ISR (TIMER0_OVF_vect) {

	if (g_callBackPtr_TIMER0 != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_TIMER0)(); /* another method to call the function using pointer to function g_callBackPtr(); */

	}

}
/*ISR for timer 2 compare mode
 * */
ISR (TIMER2_COMP_vect) {
	if (g_callBackPtr_TIMER2 != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_TIMER2)(); /* another method to call the function using pointer to function g_callBackPtr(); */

	}


}

/*ISR for timer 2 overflow
 * */
ISR (TIMER2_OVF_vect) {
	if (g_callBackPtr_TIMER2 != NULL_PTR) {
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr_TIMER2)(); /* another method to call the function using pointer to function g_callBackPtr(); */

	}
}

/*Description: Function to initialize the Timer driver
 * Inputs: pointer to the configuration structure with type Timer_ConfigType.
 * Return: None
 * */
void Timer_init(const Timer_ConfigType *Config_Ptr) {
	SREG |= (1 << 7);     //Enable global interrupts in MC by setting the I-Bit.
	if (Config_Ptr->timer_ID == TIMER0) {
		/*FOCO0 is active for non PWM
		 * setting the mode in WGM01 as WGN00 is zero in both cases
		 * inserting prescaler
		 * */
		TCCR0 = (1 << FOC0) | ((Config_Ptr->timer_mode) << 3)
				| (Config_Ptr->timer_clock);
		/*initializing the timer
		 * */
		TCNT0 = Config_Ptr->timer_InitialValue;
		if (Config_Ptr->timer_mode == CTC) {
			/* putting the compare match in the register
			 * enabling the interrupt for compare mode
			 * */
			OCR0 = Config_Ptr->timer_compare_MatchValue;
			TIMSK = (1 << OCIE0);
		} else if (Config_Ptr->timer_mode == NORMAL) {
			/* enabling the interrupt for overflow mode
			 * */
			TIMSK = (1 << TOIE0);

		}

	} else if (Config_Ptr->timer_ID == TIMER1) {
		/*FOC1A and FOC1B are always active for non PWM
		 * inserting the prescaler in the register
		 * */
		TCCR1A = (1 << FOC1A) | (1 << FOC1B);
		TCCR1B = Config_Ptr->timer_clock;
		/*initializing the timer
				 * */
		TCNT1 = Config_Ptr->timer_InitialValue;
		if (Config_Ptr->timer_mode == CTC) {
			/* setting the timer to compare mode
			 * putting the compare value in output compare register
			 * enabling interrupt for the module
			 * */
			TCCR1B |= (1 << WGM12);
			OCR1A = Config_Ptr->timer_compare_MatchValue;
			TIMSK = (1 << OCIE1A);

		} else if (Config_Ptr->timer_mode == NORMAL) {
			/* enabling interrupt for the module
			 * */
			TIMSK = (1 << TOIE1);

		}

	}
	else if (Config_Ptr->timer_ID == TIMER2) {
		/*FOC2 is active for non pwm
		 * setting the mode in WGM21 as WGN20 is zero in both cases
		 * setting prescaler
		 * */
		TCCR2 = (1 << FOC2) | ((Config_Ptr->timer_mode) << 3)
				| (Config_Ptr->timer_clock);
		/*initializing the timer
				 * */
		TCNT2=Config_Ptr->timer_InitialValue;
		if (Config_Ptr->timer_mode == CTC) {
			/*putting compare value in the register
			 * enabling interrupt for the module
			 * */
			OCR2=Config_Ptr->timer_compare_MatchValue;
			TIMSK=(1<<OCIE2);


		} else if (Config_Ptr->timer_mode == NORMAL) {
			/* enabling interrupt for the module
			 * */
			TIMSK=(1<<TOIE2);
		}


	}

}

/*Description: Function to disable the Timer via Timer_ID.
 * Inputs: Timer_ID
 * Return: None
 * */
void Timer_deInit(Timer_ID_Type timer_type) {
	if(timer_type== TIMER0){
		/*clearing all timer 0 registers
		 * */
		TCCR0=0;
		TCNT0=0;
		OCR0=0;
		/*disabling interrupts
		 * */
		TIMSK&=~(1<<TOIE0);
		TIMSK&=~(1<<OCIE0);
		/*resting the ISR function
		 * */


	}
	else if(timer_type==TIMER1){
		/*clearing all timer 1 registers
		 * */
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		OCR1A = 0;
		OCR1B = 0;
		/*disabling interrupts
		 * */
		TIMSK &= ~(1 << TOIE1);
		TIMSK &= ~(1 << OCIE1A);
		TIMSK &= ~(1 << OCIE1B);
		/*resting the ISR function
		 * */

	}
	else if(timer_type==TIMER2){
		/*clearing all timer 1 registers
		 * */
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		/*disabling interrupts
		 * */
		TIMSK &= ~(1 << TOIE2);
		TIMSK &= ~(1 << OCIE2);
		/*resting the ISR function
		 * */
	}


}

/* Description: Function to set the Call Back function address to the required Timer.
 * Inputs: pointer to Call Back function and Timer Id you want to set The Callback to it.
 *  Return: None
 * */
void Timer_setCallBack(void (*a_ptr)(void), Timer_ID_Type a_timer_ID) {
	if(a_timer_ID==TIMER0){
		/* Save the address of the Call back function in a global variable */
		g_callBackPtr_TIMER0=a_ptr;
	}
	else if (a_timer_ID==TIMER1){
		/* Save the address of the Call back function in a global variable */
		g_callBackPtr_TIMER1 = a_ptr;

	}
	else if (a_timer_ID==TIMER2){
		/* Save the address of the Call back function in a global variable */
		g_callBackPtr_TIMER2 = a_ptr;
	}

}
