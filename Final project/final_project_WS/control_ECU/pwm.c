/*
 * pwm.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */


#include "PWM.h"
#include "gpio.h"
#include "std_types.h"
#include <avr/io.h>
/*description:
 *Initializes Timer0 in PWM mode and sets the required duty cycle.
 *Initializes  Prescaler: F_CPU/64
 *Initializes  Non-inverting mode
 *Initializes  The function configures OC0 as the output pin.
 * */
void PWM_Timer0_Start(uint8 duty_cycle){
	/* choosing  pwm with F_CPU/64 and non inverting
	 * */
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01)|(1<<CS00);
	/*setting the pin to be output pin
	 * */
			DDRB|=(1<<PB3);
	/*calculating the compare number and initializing the counter with zero
	 * */
			OCR0=((duty_cycle*255)/100);
			TCNT0=0;
}


