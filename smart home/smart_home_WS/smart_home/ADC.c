/*
 * ADC.C
 *
 *  Created on: Sep 19, 2025
 *      Author: Abdullah Said
 */
#include "ADC.h"
#include <avr/io.h>
#include "common_macros.h"

void ADC_init(void){
	/*choose 2.56V as a vref
	 * */
	ADMUX=(1<<REFS0)|(1<<REFS1);
	/*enable the adc and choose the prescaler
	 * */
	ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

}
uint16 ADC_readChannel(uint8 ch_num){
	ADMUX=(ADMUX&0xE0)|(ch_num&0x1F);
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF)){}
	SET_BIT(ADCSRA,ADIF);
	return ADC;


}
