/*
 * buzzer.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"

/*port and pin id for the pin
 * */
#define BUZZER_PORT_ID PORTC_ID
#define BUZZER_PIN_ID PIN5_ID

/*description
 * Initializes the buzzer pin direction
 * and turn off the buzzer.
 * */
void Buzzer_init(void);

/*description:
 * Activates the buzzer.
 * */
void Buzzer_on(void);

/*description:
 * deactivates the buzzer.
 * */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
