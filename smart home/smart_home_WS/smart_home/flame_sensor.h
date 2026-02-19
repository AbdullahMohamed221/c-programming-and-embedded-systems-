/*
 * flame_sensor.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_
#include "std_types.h"

/*port and pin id for the sensor
 * */
#define FLAME_SENSOR_PORT_ID PORTD_ID
#define FLAME_SENSOR_PIN_ID PIN2_ID

/*description:
 * Initializes the flame sensor pin direction.
 * */
void FlameSensor_init(void);

/*description:
 * Reads the value from the flame sensor and returns it.
 * */
uint8 FlameSensor_getValue(void);

#endif /* FLAME_SENSOR_H_ */
