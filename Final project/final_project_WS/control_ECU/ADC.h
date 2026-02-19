/*
 * ADC.h
 *
 *  Created on: Sep 19, 2025
 *      Author: Abdullah Said
 */

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"


#define ADC_MAX_VALU 1023

/*the different cases of the reference volt  and they are arranged depending on
 *there value in the data sheet
 * */
typedef enum{
	ADC_AREF,AVCC,INTERNAL_VREF=3
} ADC_ReferenceVolatge;

/*the different cases of the prescaler  and they are arranged depending on
 *there value in the data sheet
 * */
typedef enum{
	 F_2=1,F_4,F_8,F_16,F_32,F_64,F_128
} ADC_Prescaler;
/*struct that contain the settings of the adc
 * */
typedef struct{
      ADC_ReferenceVolatge ref_volt;
      ADC_Prescaler prescaler;
}ADC_ConfigType;

/*description:
 * Initializes the ADC by setting
 * the reference voltage and prescaler
 * Reference Voltage: Internal reference voltage 2.56V.
 * Prescaler: F_CPU/128
 * */
void ADC_init(const ADC_ConfigType* Confi_Ptr);

/*Description:
 * this function take which channel we want to read it and then convert it
 * and return the converted value
 *
 * */
uint16 ADC_readChannel(uint8 ch_num);

/*this function displays the adc by clearing the adc enable bit
 * */
void ADC_deinit();
#endif /* ADC_H_ */
