/*
 * ADC.h
 *
 *  Created on: Sep 19, 2025
 *      Author: Abdullah Said
 */

#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"

#define ADC_MAX_VOLT 2.56
#define ADC_MAX_VALU 1023

/*description:
 * Initializes the ADC by setting
 * the reference voltage and prescaler
 * Reference Voltage: Internal reference voltage 2.56V.
 * Prescaler: F_CPU/128
 * */
void ADC_init(void);

/*Description:
 * this function take which channel we want to read it and then convert it
 * and return the converted value
 *
 * */
uint16 ADC_readChannel(uint8 ch_num);

#endif /* ADC_H_ */
