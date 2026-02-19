/*
 * application.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Abdullah Said
 */

#include "buzzer.h"
#include "dc_motor.h"
#include "flame_sensor.h"
#include "LCD.h"
#include "LED.h"
#include "sensor_ldr.h"
#include "sensor_lm35.h"

int main(void) {
	/*initializing all modules
	 * */
	Buzzer_init();
	DcMotor_Init();
	FlameSensor_init();
	LCD_init();
	LEDS_init();
	boolean fan_state = FALSE;
	while (1) {

		/*checking on the flame sensor */

		if (FlameSensor_getValue()) {
			/*if the flame sensor is on ,it will put the cursor in the beginning and
			 * clear the letters around the message
			 * and then
			 * print critical alert and turn the buzzer on  */
			LCD_moveCursor(0, 0);
			LCD_displayString("Critical alert!!");
			LCD_displayStringRowColumn(1, 0, "                      ");
			Buzzer_on();
		} else {
			/*turns of the buzzer and keep displaying the data of the sensors
			 * */
			Buzzer_off();
			LCD_moveCursor(0, 0);
			LCD_displayString("   ");
			LCD_displayStringRowColumn(0, 3, "FAN IS ");
			/*checks the state of the fan depending on the motor
			 * */
			if (fan_state) {
				LCD_displayString("ON ");
			} else {
				LCD_displayString("OFF");
			}
			LCD_displayString("       ");
			LCD_displayStringRowColumn(1, 0, "Temp=");
			LCD_moveCursor(1, 5);
			LCD_intgerToString(LM35_getTemperature());
			LCD_displayString("C LDR=");
			LCD_intgerToString(LDR_getLightIntensity());
			LCD_displayString("%");
		}


		/*fan speed depending  on the temp. and updating the flag of the fan state
		 * */
		if (LM35_getTemperature() >= 40) {
			DcMotor_Rotate(CLOCKWISE, 100);
			fan_state = TRUE;
		} else if ((LM35_getTemperature() >= 35)
				&& (LM35_getTemperature() < 40)) {
			DcMotor_Rotate(CLOCKWISE, 75);
			fan_state = TRUE;
		} else if ((LM35_getTemperature() >= 30)
				&& (LM35_getTemperature() < 35)) {
			DcMotor_Rotate(CLOCKWISE, 50);
			fan_state = TRUE;
		} else if ((LM35_getTemperature() >= 25)
				&& (LM35_getTemperature() < 30)) {
			DcMotor_Rotate(CLOCKWISE, 25);
			fan_state = TRUE;
		} else {
			DcMotor_Rotate(STOP, 0);
			fan_state = FALSE;
		}

		/*checking on the light intensity and controlling the leds */

		if (LDR_getLightIntensity() < 15) {
			LED_on(red);
			LED_on(blue);
			LED_on(green);
		} else if (LDR_getLightIntensity() >= 15
				&& LDR_getLightIntensity() <= 50) {
			LED_on(red);
			LED_off(blue);
			LED_on(green);
		} else if (LDR_getLightIntensity() > 50
				&& LDR_getLightIntensity() <= 70) {
			LED_on(red);
			LED_off(blue);
			LED_off(green);
		} else {
			LED_off(red);
			LED_off(blue);
			LED_off(green);
		}

	}
}
