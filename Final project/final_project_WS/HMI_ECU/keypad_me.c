/*
 * keypad_me.c
 *
 *  Created on: Sep 25, 2025
 *      Author: Abdullah Said
 */
#include "keypad_me.h"
#include "gpio.h"
#include <util/delay.h>

/* function to differentiate between types of keypad*/

#if (NUMBER_OF_COLUMNS==4)
/*this function is for keypad adjustment in case 4*4 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#elif (NUMBER_OF_COLUMNS==3)
	/*this function is for keypad adjustment in case 4*3 */
	static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#endif

/*this function is responsible for returning the key that is pressed  */
uint8 KEYPAD_getPressedKey(void) {
	uint8 row, col; /*these variables are for the key detection*/
	/*setting the row into inputs*/
	GPIO_setupPinDirection(ROW_START_PORT, ROW_START_PIN, PIN_INPUT);
	GPIO_setupPinDirection(ROW_START_PORT, ROW_START_PIN + 1, PIN_INPUT);
	GPIO_setupPinDirection(ROW_START_PORT, ROW_START_PIN + 2, PIN_INPUT);
	GPIO_setupPinDirection(ROW_START_PORT, ROW_START_PIN + 3, PIN_INPUT);

	/*setting the column into inputs*/
	GPIO_setupPinDirection(COLUMN_START_PORT, COLUMN_START_PIN, PIN_INPUT);
	GPIO_setupPinDirection(COLUMN_START_PORT, COLUMN_START_PIN + 1, PIN_INPUT);
	GPIO_setupPinDirection(COLUMN_START_PORT,COLUMN_START_PIN + 2, PIN_INPUT);
#if (NUMBER_OF_COLUMNS==4)
	/*if the keypad is 4*4 then we will adjust the last column */
	GPIO_setupPinDirection(COLUMN_START_PORT, COLUMN_START_PIN + 3, PIN_INPUT);
#endif

	while(1)
	{

		for (row = 0; row < NUMBER_OF_ROWS; row++) {
			/*setting the row pin into output and then set it with key_pressed */
			GPIO_setupPinDirection(ROW_START_PORT, ROW_START_PIN + row,
					PIN_OUTPUT);
			GPIO_writePin(ROW_START_PORT, ROW_START_PIN + row,
			KEY_PRESSED);
			for (col = 0; col <NUMBER_OF_COLUMNS; col++) {
				/* looping along all columns and check if the key is pressed or not*/
				if (GPIO_readPin(COLUMN_START_PORT,COLUMN_START_PIN+col)==KEY_PRESSED) {
					#if (NUMBER_OF_COLUMNS==4)
					/* adjusting the output depending on the type of the keypad */
					return KEYPAD_4x4_adjustKeyNumber(
							(row * NUMBER_OF_COLUMNS) + col + 1);
					#elif (NUMBER_OF_COLUMNS==3)
					/* adjusting the output depending on the type of the keypad */
						return KEYPAD_4x3_adjustKeyNumber((row*NUMBER_OF_COLUMNS)+col+1);
					#endif
				}

			}
			/* if the key is not in this row so, it will change this row into input and then go to the next row  */
			GPIO_setupPinDirection(ROW_START_PORT, ROW_START_PIN + row,
					PIN_INPUT);
			_delay_ms(10); /*delaying for Proutues error */
		}

	}
}

#if (NUMBER_OF_COLUMNS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 10: keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: keypad_button = 0;
				 break;
		case 12: keypad_button = '#'; // ASCII Code of #
				 break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#elif (NUMBER_OF_COLUMNS == 4)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%'; // ASCII Code of %
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = 13;  /* ASCII of Enter */
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#endif
