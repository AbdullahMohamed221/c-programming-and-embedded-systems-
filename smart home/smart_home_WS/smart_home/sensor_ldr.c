/*
 * sensor_ldr.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */
#include "sensor_ldr.h"
#include "ADC.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint16 LDR_getLightIntensity(void) {
	/*initializing the adc
	 * */
	ADC_init();
	uint8 light_intensity = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(LDR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	light_intensity =
			(uint16) (((uint32) adc_value * LDR_MAX_VALUE * ADC_MAX_VOLT)
					/ (ADC_MAX_VALU * LDR_MAX_VOLT));

	return light_intensity;

}


