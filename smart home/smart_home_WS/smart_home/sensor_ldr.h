/*
 * sensor_ldr.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#ifndef SENSOR_LDR_H_
#define SENSOR_LDR_H_
#include "std_types.h"

/*some defines needed for the calculations
 * */
#define LDR_MAX_VALUE 100
#define LDR_MAX_VOLT 2.56
#define LDR_CHANNEL_ID 0

/*
 * Description :
 * Function responsible for calculate the light intensity
 *  from the ADC digital value.
 */
uint16 LDR_getLightIntensity(void);


#endif /* SENSOR_LDR_H_ */
