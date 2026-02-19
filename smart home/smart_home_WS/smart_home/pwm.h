/*
 * pwm.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"


/*description:
 *Initializes Timer0 in PWM mode and sets the required duty cycle.
 *Initializes  Prescaler: F_CPU/1024
 *Initializes  Non-inverting mode
 *Initializes  The function configures OC0 as the output pin.
 * */
void PWM_Timer0_Start(uint8 duty_cycle);




#endif /* PWM_H_ */
