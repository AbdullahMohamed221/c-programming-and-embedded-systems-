/*
 * buzzer.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "buzzer.h"
#include "gpio.h"



/*description
 * Initializes the buzzer pin direction
 * and turn off the buzzer.
 * */
void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}


/*description:
 * Activates the buzzer.
 * */
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);

}

/*description:
 * deactivates the buzzer.
 * */
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
