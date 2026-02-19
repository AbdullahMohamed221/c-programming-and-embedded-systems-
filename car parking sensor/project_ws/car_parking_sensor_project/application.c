/*
 * application.c
 *
 *  Created on: Oct 2, 2025
 *      Author: Abdullah Said
 */
/*used library for each module
 * */
#include "LED.h"
#include "LCD.h"
#include "buzzer.h"
#include "ultrasonic_sensor.h"
#include <util/delay.h>
#include <avr/io.h>
int main(void){
	/*initializing the modules
	 * */
	LCD_init();
	LEDS_init();
	Buzzer_init();
	Ultrasonic_init();
	/* enabling the global interrupt */
		SREG |= (1 << 7);


while(1){

	/*Continuous display for the distance
	 * */
	LCD_displayStringRowColumn(0,1,"Distance=");
	LCD_intgerToString((Ultrasonic_readDistance()+1));
	LCD_displayString("cm ");

	/*checks if the it is smaller than 5 or equal
	 * */
	if((Ultrasonic_readDistance()+1)<=5){
		/*
		 * blinking of the leds and the buzzer
		 * displaying stop on the lcd
		 */
			LED_on(red);
			LED_on(green);
			LED_on(blue);
			Buzzer_on();
			_delay_ms(500);
			LED_off(red);
			LED_off(green);
			LED_off(blue);
			Buzzer_off();
			_delay_ms(500);
			LCD_displayStringRowColumn(1,6,"STOP");
		}
	else{
		/*clearing stop from the lcd
		 * */
		LCD_displayStringRowColumn(1,4,"                   ");
		/*
		 * checking the distance ranges of the distance
		 */
		if(((Ultrasonic_readDistance()+1)>=6)&&((Ultrasonic_readDistance()+1)<=10)){
			/*opening all leds and close the buzzer
			 * */
			LED_on(red);
			LED_on(green);
			LED_on(blue);
			Buzzer_off();

		}
		else if(((Ultrasonic_readDistance()+1)>=11)&&((Ultrasonic_readDistance()+1)<=15)){
			/*closes the blue led and the buzzer and open the red and the green led
			 * */
			LED_on(red);
			LED_on(green);
			LED_off(blue);
			Buzzer_off();
		}

		else if(((Ultrasonic_readDistance()+1)>=16)&&((Ultrasonic_readDistance()+1)<=20)){
			/*closes the blue led, the green and the buzzer and open the red
			 * */
			LED_on(red);
			LED_off(green);
			LED_off(blue);
			Buzzer_off();
		}

		else if(((Ultrasonic_readDistance()+1)>20)){
			/*closes everything
			 * */
					LED_off(red);
					LED_off(green);
					LED_off(blue);
					Buzzer_off();
				}

	}
	}
}
