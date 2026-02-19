/*
 * sensor_lm35.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "sensor_lm35.h"
#include "ADC.h"
#include <avr/io.h>
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemperature(void) {
	/*initializing the adc
		 * */
	ADC_ConfigType ADC_configuration={INTERNAL_VREF,F_8};
	ADC_init(&ADC_configuration);

	uint16 adc_max_volt;

	if((ADC_configuration.ref_volt== ADC_AREF)||(ADC_configuration.ref_volt== AVCC)){
		adc_max_volt=5000;
	}
	else if (ADC_configuration.ref_volt == INTERNAL_VREF ){
		adc_max_volt=2560;
	}
	uint8 temp_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(LM35_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value =
			(uint8) (((uint32) adc_value * LM35_MAX_TEMP * (adc_max_volt/1000.0))
					/ (ADC_MAX_VALU * LM35_MAX_VOLT));

	return temp_value;

}

/*this function displays the adc by clearing the adc enable bit
 * */
void LM55_deinit(){
	ADC_deinit();
}

