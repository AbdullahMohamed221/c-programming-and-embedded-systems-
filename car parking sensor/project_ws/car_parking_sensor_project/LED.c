/*
 * LED.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "LED.h"
#include "gpio.h"

/*description:
 *Initializes all Leds (red, green, blue) pins direction.
 *Initializes Turn off all the Leds
 * */
void LEDS_init(void) {

	GPIO_setupPinDirection(LED_1_PORT_ID, LED_1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_2_PORT_ID, LED_2_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_3_PORT_ID, LED_3_PIN_ID, PIN_OUTPUT);

#if (CONNECTION_LOGICE==1)
	GPIO_writePin(LED_1_PORT_ID, LED_1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LED_2_PORT_ID, LED_2_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LED_3_PORT_ID, LED_3_PIN_ID, LOGIC_LOW);
#elif (CONNECTION_LOGICE==0)
	GPIO_writePin(LED_1_PORT_ID,LED_1_PIN_ID,LOGIC_HIGH);
	GPIO_writePin(LED_2_PORT_ID,LED_2_PIN_ID,LOGIC_HIGH);
	GPIO_writePin(LED_3_PORT_ID,LED_3_PIN_ID,LOGIC_HIGH);
#endif
}

/*description
 * Turns on the specified LED.
 *  */
void LED_on(LED_ID id) {
	switch (id) {
	case 1:
#if (CONNECTION_LOGICE==1)
		GPIO_writePin(LED_1_PORT_ID, LED_1_PIN_ID, LOGIC_HIGH);
#elif (CONNECTION_LOGICE==0)
	 GPIO_writePin(LED_1_PORT_ID, LED_1_PIN_ID, LOGIC_LOW);
#endif
		break;
	case 2:
#if (CONNECTION_LOGICE==1)
		GPIO_writePin(LED_2_PORT_ID, LED_2_PIN_ID, LOGIC_HIGH);
#elif (CONNECTION_LOGICE==0)
	 GPIO_writePin(LED_2_PORT_ID, LED_2_PIN_ID, LOGIC_LOW);
#endif
		break;
	case 3:
#if (CONNECTION_LOGICE==1)
		GPIO_writePin(LED_3_PORT_ID, LED_3_PIN_ID, LOGIC_HIGH);
#elif (CONNECTION_LOGICE==0)
	 GPIO_writePin(LED_3_PORT_ID, LED_3_PIN_ID, LOGIC_LOW);
#endif
		break;
	}
}

/*description:
 * Turns off the specified LED.
 *  */
void LED_off(LED_ID id) {
	switch (id) {
	case 1:
#if (CONNECTION_LOGICE==1)
		GPIO_writePin(LED_1_PORT_ID, LED_1_PIN_ID, LOGIC_LOW);
#elif (CONNECTION_LOGICE==0)
		 GPIO_writePin(LED_1_PORT_ID, LED_1_PIN_ID, LOGIC_HIGH);
	#endif
		break;
	case 2:
#if (CONNECTION_LOGICE==1)
		GPIO_writePin(LED_2_PORT_ID, LED_2_PIN_ID, LOGIC_LOW);
#elif (CONNECTION_LOGICE==0)
		 GPIO_writePin(LED_2_PORT_ID, LED_2_PIN_ID, LOGIC_HIGH);
	#endif
		break;
	case 3:
#if (CONNECTION_LOGICE==1)
		GPIO_writePin(LED_3_PORT_ID, LED_3_PIN_ID, LOGIC_LOW);
#elif (CONNECTION_LOGICE==0)
		 GPIO_writePin(LED_3_PORT_ID, LED_3_PIN_ID, LOGIC_HIGH);
	#endif
		break;
	}

}
