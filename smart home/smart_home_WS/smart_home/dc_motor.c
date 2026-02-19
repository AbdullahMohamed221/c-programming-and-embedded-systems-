/*
 * dc_motor.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*description:
 * Initializes the DC motor by setting the direction
 * for the motor pins and stopping the
 * motor at the beginning.
 * */
void DcMotor_Init(void) {
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID,
			PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID,
			PIN_OUTPUT);
	GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);

}

/*description:
 * Controls the motor's state (Clockwise/Anti-Clockwise/Stop)
 * and adjusts the speed based
 * on the input duty cycle.
 * */
void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
	switch (state) {
	case 0:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		PWM_Timer0_Start(0);
		break;
	case 1:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
		PWM_Timer0_Start(speed);
		break;
	case 2:
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_HIGH);
		PWM_Timer0_Start(speed);
		break;
	}
}

