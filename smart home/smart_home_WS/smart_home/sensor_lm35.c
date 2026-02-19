/*
 * sensor_lm35.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "sensor_lm35.h"
#include "ADC.h"
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void) {
	/*initializing the adc
		 * */
		ADC_init();
	uint8 temp_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(LM35_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value =
			(uint8) (((uint32) adc_value * LM35_MAX_TEMP * ADC_MAX_VOLT)
					/ (ADC_MAX_VALU * LM35_MAX_VOLT));

	return temp_value;

}
