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
#define DC_MOTOR_IN1_PORT_ID PORTB_ID
#define DC_MOTOR_IN1_PIN_ID PIN0_ID

#define DC_MOTOR_IN2_PORT_ID PORTB_ID
#define DC_MOTOR_IN2_PIN_ID PIN1_ID

/*enum for the motor states
 */
typedef enum {
	STOP,CLOCKWISE,ANTICLOCKWISE
}DcMotor_State;

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
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
