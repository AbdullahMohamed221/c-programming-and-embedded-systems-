/*
 * flame_sensor.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "flame_sensor.h"
#include "gpio.h"
/*description:
 * Initializes the flame sensor pin direction.
 * */
void FlameSensor_init(void){
	GPIO_setupPinDirection(FLAME_SENSOR_PORT_ID,FLAME_SENSOR_PIN_ID,PIN_OUTPUT);
}

/*description:
 * Reads the value from the flame sensor and returns it.
 * */
uint8 FlameSensor_getValue(void){
	return GPIO_readPin(FLAME_SENSOR_PORT_ID,FLAME_SENSOR_PIN_ID);
}
