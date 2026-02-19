/*
 * ADC.C
 *
 *  Created on: Sep 19, 2025
 *      Author: Abdullah Said
 */
#include "ADC.h"
#include <avr/io.h>
#include "common_macros.h"

void ADC_init(const ADC_ConfigType* Confi_Ptr){
	/*choosing Vref
	 * */
	ADMUX=(((Confi_Ptr->ref_volt)&0X03)<<6);
	/*enable the adc and choose the prescaler
	 * */
	ADCSRA=(1<<ADEN)|((Confi_Ptr->prescaler)&0x07);

}
uint16 ADC_readChannel(uint8 ch_num){
	/*insert the number of the channel in the ADMIX register
	 * */
	ADMUX=(ADMUX&0xE0)|(ch_num&0x1F);
	/*starts the conversion
	 * */
	SET_BIT(ADCSRA,ADSC);
	/*polling till the conversion ends
	 *  */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)){}
	/*clearing the flag
	 * */
	SET_BIT(ADCSRA,ADIF);
	/*reading the converted number
	 * */
	return ADC;


}
/*this function displays the adc by clearing the adc enable bit
 * */
void ADC_deinit(){
	ADCSRA &= ~(1<<ADEN);
}
