/*
 * dc_motor.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"
#include <util/delay.h>

/*global variable for the HMI
 * */
boolean State_to_HMI=FALSE;
/*description:
 * Initializes the DC motor by setting the direction
 * for the motor pins and stopping the
 * motor at the beginning.
 * and initializing button
 * */
void DcMotor_Init(void) {

	GPIO_setupPinDirection(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID,
			PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID,
			PIN_OUTPUT);

	GPIO_setupPinDirection(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID,
			PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID,
			PIN_OUTPUT);

	GPIO_setupPinDirection(OPEN_WINDOW_1_PORT, OPEN_WINDOW_1_PIN, PIN_INPUT);
	GPIO_setupPinDirection(CLOSE_WINDOW_1_PORT, CLOSE_WINDOW_1_PIN, PIN_INPUT);

	GPIO_setupPinDirection(OPEN_WINDOW_2_PORT, OPEN_WINDOW_2_PIN, PIN_INPUT);
	GPIO_setupPinDirection(CLOSE_WINDOW_2_PORT, CLOSE_WINDOW_2_PIN, PIN_INPUT);

	GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_LOW);

	GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID, LOGIC_LOW);
	/*initializing the pwm
	 * */
	PWM_Timer0_Start(0);
}

/*description:
 * Controls the motor's state (Clockwise/Anti-Clockwise/Stop)
 * and adjusts the speed based
 * on the input duty cycle.
 * */
void DcMotor_Rotate(DcMotor_window_number number, DcMotor_State state,
		uint8 speed) {
	switch (number) {
	case 1:
		switch (state) {
		case 0:
			GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID,
			LOGIC_LOW);
			GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID,
			LOGIC_LOW);
			PWM_Timer0_Start(0);
			break;
		case 1:
			GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID,
			LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID,
			LOGIC_LOW);
			PWM_Timer0_Start(speed);
			break;
		case 2:
			GPIO_writePin(DC_MOTOR1_IN1_PORT_ID, DC_MOTOR1_IN1_PIN_ID,
			LOGIC_LOW);
			GPIO_writePin(DC_MOTOR1_IN2_PORT_ID, DC_MOTOR1_IN2_PIN_ID,
			LOGIC_HIGH);
			PWM_Timer0_Start(speed);
			break;
		}
		break;
	case 2:
		switch (state) {
		case 0:
			GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID,
			LOGIC_LOW);
			GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID,
			LOGIC_LOW);
			PWM_Timer0_Start(0);
			break;
		case 1:
			GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID,
			LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID,
			LOGIC_LOW);
			PWM_Timer0_Start(speed);
			break;
		case 2:
			GPIO_writePin(DC_MOTOR2_IN1_PORT_ID, DC_MOTOR2_IN1_PIN_ID,
			LOGIC_LOW);
			GPIO_writePin(DC_MOTOR2_IN2_PORT_ID, DC_MOTOR2_IN2_PIN_ID,
			LOGIC_HIGH);
			PWM_Timer0_Start(speed);
			break;
		}
		break;
	}
}

/*description:
 * this function opens and closes the window as it takes window number and window state
 *   returns a number that represents the state
 * */
uint8 DCMotor_Open_Close(DcMotor_window_number number,
		DcMotor_window_state state) {
	switch (number) {
	case 1:
		switch (state) {
		case 0:
			DcMotor_Rotate(WINDOW_1, ANTICLOCKWISE, 100);
			_delay_ms(2000);
			DcMotor_Rotate(WINDOW_1, STOP, 100);
			State_to_HMI=FALSE;
			return State_to_HMI;

			break;
		case 1:
			DcMotor_Rotate(WINDOW_1, CLOCKWISE, 100);
			_delay_ms(2000);
			DcMotor_Rotate(WINDOW_1, STOP, 100);
			State_to_HMI=TRUE;
			return State_to_HMI;
			break;
		}
		break;
	case 2:
		switch (state) {
		case 0:
			DcMotor_Rotate(WINDOW_2, ANTICLOCKWISE, 100);
			_delay_ms(2000);
			DcMotor_Rotate(WINDOW_2, STOP, 100);
			State_to_HMI=FALSE;
			return State_to_HMI;
			break;
		case 1:
			DcMotor_Rotate(WINDOW_2, CLOCKWISE, 100);
			_delay_ms(2000);
			DcMotor_Rotate(WINDOW_2, STOP, 100);
			State_to_HMI=TRUE;
			return State_to_HMI;
			break;
		}
		break;
	}
	return State_to_HMI;

}
/*description: this function check which key is pressed and then make the command of this button
 * */
uint8 DCMotor_Get_Button_WIN1() {
	if (GPIO_readPin(OPEN_WINDOW_1_PORT, OPEN_WINDOW_1_PIN) == BUTTON_PRESSED) {

		return DCMotor_Open_Close(WINDOW_1, OPENED);
	} else if (GPIO_readPin(CLOSE_WINDOW_1_PORT,
			CLOSE_WINDOW_1_PIN)==BUTTON_PRESSED) {
		return DCMotor_Open_Close(WINDOW_1, CLOSED);
	}
	else{
		return 7;
	}
}
/*description: this function check which key is pressed FOR WINDOW 1 and then make the command of this button
 * */

uint8 DCMotor_Get_Button_WIN2() {
	if (GPIO_readPin(OPEN_WINDOW_2_PORT, OPEN_WINDOW_2_PIN) == BUTTON_PRESSED) {
		return DCMotor_Open_Close(WINDOW_2, OPENED);
	}
	else if (GPIO_readPin(CLOSE_WINDOW_2_PORT,
			CLOSE_WINDOW_2_PIN)==BUTTON_PRESSED) {
		return DCMotor_Open_Close(WINDOW_2, CLOSED);
	}

	else{
			return 7;
		}
}
