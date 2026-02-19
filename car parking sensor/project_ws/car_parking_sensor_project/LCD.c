/*
 * LCD.c
 *
 *  Created on: Sep 28, 2025
 *      Author: Abdullah Said
 */

#include "LCD.h"
#include "gpio.h"
#include <util/delay.h>
#include"common_macros.h"

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_sendCommand(uint8 command) {
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
#if(LCD_MODE==8)
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#elif (LCD_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D4_PIN_ID, GET_BIT(command, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D5_PIN_ID, GET_BIT(command, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D6_PIN_ID, GET_BIT(command, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D7_PIN_ID, GET_BIT(command, 7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);


	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D4_PIN_ID, GET_BIT(command, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D5_PIN_ID, GET_BIT(command, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D6_PIN_ID, GET_BIT(command, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D7_PIN_ID, GET_BIT(command, 3));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#endif

}
/*Description:
 *Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 *
 * */
void LCD_init(void) {
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	_delay_ms(20);
	#if(LCD_MODE==8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#elif (LCD_MODE==4)
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_D4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_D5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_D6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_D7_PIN_ID,PIN_OUTPUT);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}
/*
 * Description :
 * Display the required character on the screen
 */
void LCD_sendChar(uint8 data) {
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
#if(LCD_MODE==8)
	GPIO_writePort(LCD_DATA_PORT_ID, data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#elif (LCD_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D4_PIN_ID, GET_BIT(data, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D5_PIN_ID, GET_BIT(data, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D6_PIN_ID, GET_BIT(data, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D7_PIN_ID, GET_BIT(data, 7));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D4_PIN_ID, GET_BIT(data, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D5_PIN_ID, GET_BIT(data, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D6_PIN_ID, GET_BIT(data, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_D7_PIN_ID, GET_BIT(data, 3));
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#endif
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str) {
	uint8 counter = 0;
	while (Str[counter] != '\0') {
		LCD_sendChar(Str[counter]);
		counter++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row, uint8 col) {
	uint8 final_position = 0;
	switch (row) {
	case 0:
		final_position = 0x00 + col;
		break;
	case 1:
		final_position = 0x40 + col;
		break;
	case 2:
		final_position = 0x10 + col;
		break;
	case 3:
		final_position = 0x50 + col;
		break;
	}
	LCD_sendCommand(final_position + LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str) {
	LCD_moveCursor(row, col);
	LCD_displayString(Str);

}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void) {
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(uint16 data) {
	char buffer[16];
	itoa(data, buffer, 10);
	LCD_displayString(buffer);

}
