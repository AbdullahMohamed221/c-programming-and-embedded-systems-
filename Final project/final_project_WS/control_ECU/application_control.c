/*
 * application_control.c
 *
 *  Created on: Oct 25, 2025
 *      Author: Abdullah Said
 */

/*including the libraries
 * */
#include "uart.h"
#include "ultrasonic_sensor.h"
#include "sensor_lm35.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "twi.h"
#include "pwm.h"
#include <avr/io.h>
#include <util/delay.h>

#define HMI_READY 0x10
#define HMI_STOP 0x11
#define SEND_AGAIN_ERROR 0x12

int main() {
	/*initializing modules
	 * */
	/* enabling the global interrupt */
	SREG |= (1 << 7);

	UART_ConfigType uart_configurations = { BIT_8, NO_PARITY, ONE_BIT,
			BAUD_RATE_9600 };
	UART_init(&uart_configurations);
	/*counter for number of error logged
	 * counter for the loop of the sending
	 * variable that hold the value of the error
	 * */
	static uint8 error_counter = 0;
	uint8 display_counter = 0;
	uint8 error;


	/*flags used for error logging
	 * */
	boolean temp_flag = FALSE;
	boolean dis_flag = FALSE;
	/*variable used for the cases of the switch case
	 * */
	uint8 cases;

	while (1) {
		if (Ultrasonic_readDistance() < 10) {
			if (dis_flag == FALSE) {
				EEPROM_writeByte(0x0311 + error_counter, 1);
				error_counter++;
				dis_flag = TRUE;
			}

		}

		else {
			dis_flag = FALSE;
		}

		if (LM35_getTemperature() > 90) {
			if (temp_flag == FALSE) {

				EEPROM_writeByte(0x0311 + error_counter, 2);
				error_counter++;
				temp_flag = TRUE;
			}

		} else {
			temp_flag = FALSE;
		}


		cases = UART_recieveByte();
		switch (cases) {
		case 1:
			/*start monitoring
			 * initializing modules
			 * */
			DcMotor_Init();
			Ultrasonic_init();
			TWI_ConfigType twi_configuration = { 1, BIT_RATE_400K };
			TWI_init(&twi_configuration);

			break;
		case 2:
			/*display variables
			 * sending variables
			 * */

			do {
				UART_sendByte(HMI_READY);
				UART_sendByte(LM35_getTemperature());
				UART_sendByte((uint8) Ultrasonic_readDistance());
				UART_sendByte(DCMotor_Get_Button_WIN1());
				UART_sendByte(DCMotor_Get_Button_WIN2());
			} while (UART_recieveByte() != HMI_STOP);
			break;

		case 3:
			/*logged errors
			 * */

			for (display_counter = 0; display_counter < error_counter;
					display_counter++) {
				EEPROM_readByte(0x0311+display_counter,&error);
				UART_sendByte(HMI_READY);
				UART_sendByte(error);
				UART_sendByte(error_counter);
				while(UART_recieveByte()!=SEND_AGAIN_ERROR);
			}
			UART_sendByte(HMI_STOP);
			break;
		case 4:
			/*stop monitoring
			 * this will deinitialize the sensors
			 * */
			LM55_deinit();
			Ultrasonic_deint();
			break;
		case 0:
			/*main menu
			 * */
			break;

		}

	}

}
