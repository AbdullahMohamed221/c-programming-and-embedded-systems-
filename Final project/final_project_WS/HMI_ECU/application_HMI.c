/*
 * application_HMI.c
 *
 *  Created on: Oct 25, 2025
 *      Author: Abdullah Said
 */
/*including the libraries
 * */
#include "keypad_me.h"
#include "LCD.h"
#include "uart.h"
#include "timer.h"
#include <util/delay.h>
/* global variable, flag and a function for the 10 sec. delay
 * */
uint8 g_tick = 0;
boolean flag = FALSE;
void _10SEC_delay() {
	g_tick++;
	if (g_tick == 5) {
		flag = TRUE;
		g_tick = 0;
	}
}
/*flags to ease the uart com.
 * */
#define HMI_READY 0x10
#define HMI_STOP 0x11
#define SEND_AGAIN_ERROR 0x12

int main() {
	/*initializing modules
	 * */
	LCD_init();
	UART_ConfigType uart_configurations = { BIT_8, NO_PARITY, ONE_BIT,
			BAUD_RATE_9600 };
	UART_init(&uart_configurations);
	Timer_ConfigType timer_configurations = { 0, 15625, TIMER1, CLK_1024, CTC };
	Timer_setCallBack(_10SEC_delay, TIMER1);

	/*welcome message
	 * */
	LCD_displayStringRowColumn(0, 0, "Welcome to Vehicle ");
	LCD_displayStringRowColumn(1, 0, "Fault Detection and ");
	LCD_displayStringRowColumn(2, 0, "logging system");
	LCD_displayStringRowColumn(3, 0, "press 0 to start");
	/*this variable is used to switch between different cases of the switch
	 * counter used for displaying
	 * */
	uint8 cases;
	cases = KEYPAD_getPressedKey();
	uint8 display = 1;
	uint8 nummm;

	/*variables to store the date from control ECU
	 * */
	uint8 temp;
	uint8 dis;
	boolean win1 = FALSE;
	boolean win2 = FALSE;
	boolean win1_1;
	boolean win2_2;
	uint8 error_type;

	while (1) {
		/*always sending to the control ECU the cases
		 * */

		UART_sendByte(cases);

		switch (cases) {
		case 1:
			/*display the message
			 * */

			LCD_displayStringRowColumn(0, 0, "Operation        ");
			LCD_displayStringRowColumn(1, 0, "Started!         ");
			LCD_displayStringRowColumn(2, 0, "Monitoring       ");
			LCD_displayStringRowColumn(3, 0, "Active..         ");
			/*starting the timer and then waiting 10 sec and then stopping the timer
			 * */
			Timer_init(&timer_configurations);
			while (flag == FALSE) {
			}
			if (flag == TRUE) {
				/*going to main case which it is the main menu
				 * */
				Timer_deInit(TIMER1);
				cases = 0;
				flag = FALSE;
			}

			break;

		case 2:
			/*starting the timer
			 * */

			Timer_init(&timer_configurations);
			/*waiting for the timer to count 10 sec.
			 * */
			while (flag == FALSE) {
				/*display the message
				 * */
				/*Receiving variables from the user with uart
				 * but first receive a flag and then temp, distance, win1,win2
				 * save them to display them in the lcd
				 * */
				while (UART_recieveByte() != HMI_READY)
					;
				temp = UART_recieveByte();
				dis = UART_recieveByte();
				win1_1 = UART_recieveByte();
				win2_2 = UART_recieveByte();

				switch (win1_1) {
				case 1:
					win1 = TRUE;
					break;
				case 0:
					win1 = FALSE;
					break;
				default:

					break;
				}
				switch (win2_2) {
				case 1:
					win2 = TRUE;
					break;
				case 0:
					win2 = FALSE;
					break;
				default:
					break;
				}

				LCD_displayStringRowColumn(0, 0, "Temp:");
				LCD_intgerToString(temp);
				LCD_displayString("C               ");

				LCD_displayStringRowColumn(1, 0, "Distance:");
				LCD_intgerToString(dis + 1);
				LCD_displayString("cm               ");
				//distance
				LCD_displayStringRowColumn(2, 0, "Win1:                  ");
				if (win1 == TRUE) {
					LCD_displayStringRowColumn(2, 5, "open");
				} else if (win1 == FALSE) {
					LCD_displayStringRowColumn(2, 5, "closed");
				}
				//win1
				LCD_displayStringRowColumn(3, 0, "Win2:                 ");
				if (win2 == TRUE) {
					LCD_displayStringRowColumn(3, 5, "open");
				} else if (win2 == FALSE) {
					LCD_displayStringRowColumn(3, 5, "closed");
				}
				UART_sendByte(!HMI_STOP);

			}
			/*the timer finished 10 sec.
			 * */
			if (flag == TRUE) {
				/*stopping the timer and then asking the user to display again or stop and
				 * return to the main menu
				 * */
				Timer_deInit(TIMER1);
				while (flag == TRUE) {
					/*ddisplaying the message
					 * */
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Display again?");
					LCD_displayStringRowColumn(1, 0, "press 2= YES");
					LCD_displayStringRowColumn(2, 0, "other key = Main menu");
					/*taking the decision  from the used
					 * */
					switch (KEYPAD_getPressedKey()) {
					case 2:
						cases = 2;
						flag = FALSE;
						break;
					default:
						cases = 0;
						UART_sendByte(HMI_STOP);
						flag = FALSE;
						break;
					}
				}
			}
			break;

		case 3:

			LCD_clearScreen();
			display = 1; /* or 1 depending on your LCD row indexing*/

			while (1) {
				uint8 incoming = UART_recieveByte(); /* blocking read for the next framing byte*/

				if (incoming == HMI_STOP) {
					break; /* end of list, exit loop*/
				}

				if (incoming == HMI_READY) {
					/*read payload bytes*/
					error_type = UART_recieveByte();
					nummm = UART_recieveByte();

					/* show header once (or every time if you want)*/
					LCD_displayStringRowColumn(0, 0, "Logged faults       ");
					LCD_moveCursor(0, 15);
					LCD_intgerToString(nummm);

					/*show error on current display row*/
					switch (error_type) {
					case 1:
						LCD_displayStringRowColumn(display, 0,
								"P001:DistanceTooClose");
						break;
					case 2:
						LCD_displayStringRowColumn(display, 0, "P002:Overheat");
						break;
					default:
						LCD_displayStringRowColumn(display, 0, "P001:DistanceTooClose");
						break;
					}

					/* show end marker always on last displayed row (or after loop)*/
					LCD_displayStringRowColumn(3, 0, "---End of list---");

					/* prepare next display row (scroll)*/
					display++;
					if (display > 2)
						display = 1; /* keep rows 1..2 (adjust to your LCD indexing)*/

					/* send ack so control can send next error*/
					UART_sendByte(SEND_AGAIN_ERROR);
				}
				/* else ignore unknown framing bytes or handle them*/
			} /* end while(1)*/
			Timer_init(&timer_configurations);
			/*waiting for the timer to count 10 sec.
			 * */
			while (flag == FALSE) {
			}
			/*the timer finished 10 sec.
			 * */
			if (flag == TRUE) {
				/*stopping the timer and then asking the user to display again or stop and
				 * return to the main menu
				 * */
				Timer_deInit(TIMER1);
				while (flag == TRUE) {
					/*ddisplaying the message
					 * */
					LCD_displayStringRowColumn(0, 0, "Display again?       ");
					LCD_displayStringRowColumn(1, 0, "press 3= YES         ");
					LCD_displayStringRowColumn(2, 0, "other key = Main       ");
					LCD_displayStringRowColumn(3, 0, "menu               ");
					/*taking the decision  from the used
					 * */
					switch (KEYPAD_getPressedKey()) {
					case 3:
						cases = 3;
						flag = FALSE;
						break;
					default:
						cases = 0;
						flag = FALSE;
						break;
					}
				}
			}

			break;
		case 4:
			//sending the message with the uart
			/*display the message
			 * */
			LCD_displayStringRowColumn(0, 0, "System          ");
			LCD_displayStringRowColumn(1, 0, "Monitoring         ");
			LCD_displayStringRowColumn(2, 0, "Stopped!            ");
			LCD_displayStringRowColumn(3, 0, "ReturningToMenu          ");
			/*starting the timer and then waiting 10 sec and then stopping the timer
			 * */
			Timer_init(&timer_configurations);
			while (flag == FALSE) {
			}
			if (flag == TRUE) {
				/*going to main case which it is the main menu
				 * */
				Timer_deInit(TIMER1);
				cases = 0;
				flag = FALSE;
			}

			break;
		case 0:
			/*at the beginning to display the main menu
			 * */
			LCD_displayStringRowColumn(0, 0, "1Start Operation    ");
			LCD_displayStringRowColumn(1, 0, "2Display Values     ");
			LCD_displayStringRowColumn(2, 0, "3Retrieve Faults    ");
			LCD_displayStringRowColumn(3, 0, "4stop Monitoring     ");
			cases = KEYPAD_getPressedKey();

			break;
		}
	}

}
