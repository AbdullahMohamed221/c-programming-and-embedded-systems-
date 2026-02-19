/*
 * sensor_lm35.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#ifndef SENSOR_LM35_H_
#define SENSOR_LM35_H_
#include "std_types.h"

/*some defines needed for the calculations
 * */
#define LM35_MAX_TEMP 150
#define LM35_MAX_VOLT 1.5
#define LM35_CHANNEL_ID 1


/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void);


#endif /* SENSOR_LM35_H_ */
