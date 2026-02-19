/*
 * LED.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#ifndef LED_H_
#define LED_H_
#include "std_types.h"
/*to make the connection configurable
 * 1->positive / 0->negative
 * */
#define CONNECTION_LOGICE 1

/*port and pin id for each led
 * */
#define LED_1_PORT_ID PORTB_ID
#define LED_1_PIN_ID PIN5_ID

#define LED_2_PORT_ID PORTB_ID
#define LED_2_PIN_ID PIN6_ID

#define LED_3_PORT_ID PORTB_ID
#define LED_3_PIN_ID PIN7_ID
/*ID for each lead
 * */
typedef enum{
	red=1,green,blue
}LED_ID;

/*description:
 *Initializes all Leds (red, green, blue) pins direction.
 *Initializes Turn off all the Leds
 * */
void LEDS_init(void);

/*description
 * Turns on the specified LED.
 *  */
void LED_on(LED_ID id);


/*description:
 * Turns off the specified LED.
 *  */
void LED_off(LED_ID id);


#endif /* LED_H_ */
