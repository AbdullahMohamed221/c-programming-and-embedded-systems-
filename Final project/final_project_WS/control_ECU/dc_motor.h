/*
 * dc_motor.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"


/*port and pin id for each led
 * */
#define DC_MOTOR1_IN1_PORT_ID PORTB_ID
#define DC_MOTOR1_IN1_PIN_ID PIN4_ID

#define DC_MOTOR1_IN2_PORT_ID PORTB_ID
#define DC_MOTOR1_IN2_PIN_ID PIN5_ID

#define DC_MOTOR2_IN1_PORT_ID PORTB_ID
#define DC_MOTOR2_IN1_PIN_ID PIN6_ID

#define DC_MOTOR2_IN2_PORT_ID PORTB_ID
#define DC_MOTOR2_IN2_PIN_ID PIN7_ID

/*buttons for closing and opening the windows
 * */
#define OPEN_WINDOW_1_PORT	PORTA_ID
#define OPEN_WINDOW_1_PIN	PIN2_ID

#define CLOSE_WINDOW_1_PORT	 PORTA_ID
#define CLOSE_WINDOW_1_PIN	 PIN3_ID

#define OPEN_WINDOW_2_PORT	PORTA_ID
#define OPEN_WINDOW_2_PIN	PIN4_ID

#define CLOSE_WINDOW_2_PORT	 PORTA_ID
#define CLOSE_WINDOW_2_PIN	 PIN5_ID

#define BUTTON_PRESSED LOGIC_LOW
#define BUTTON_NOT_PRESSED LOGIC_HIGH

/*enum for the motor states
 */
typedef enum {
	STOP,CLOCKWISE,ANTICLOCKWISE
}DcMotor_State;
/*
 * */
typedef enum {
	WINDOW_1=1,WINDOW_2
}DcMotor_window_number;

typedef enum {
	CLOSED,OPENED
}DcMotor_window_state;


/*description:
 * Initializes the DC motor by setting the direction
 * for the motor pins and stopping the
 * motor at the beginning.
 * */
void DcMotor_Init(void);


/*description:
 * Controls the motor's state (Clockwise/Anti-Clockwise/Stop)
 * and adjusts the speed based
 * on the input duty cycle.
 * */
void DcMotor_Rotate(DcMotor_window_number number,DcMotor_State state, uint8 speed);

/*description:
 * this function opens and closes the window as it takes window number and window state
 *   returns a number that represents the state
 *   open:clock wise
 *   close: counter clock wise
 * */
uint8 DCMotor_Open_Close(DcMotor_window_number number,DcMotor_window_state state);

/*description: this function check which key is pressed FOR WINDOW 1 and then make the command of this button
 * */
uint8 DCMotor_Get_Button_WIN1();

/*description: this function check which key is pressed FOR WINDOW 2 and then make the command of this button
 * */
uint8 DCMotor_Get_Button_WIN2();

#endif /* DC_MOTOR_H_ */
