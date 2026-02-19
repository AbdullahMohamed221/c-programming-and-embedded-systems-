/*
 * keypad_me.h
 *
 *  Created on: Sep 25, 2025
 *      Author: Abdullah Said
 */

#ifndef KEYPAD_ME_H_
#define KEYPAD_ME_H_
#include "std_types.h"
/* important defines */
#define NUMBER_OF_ROWS 4
#define NUMBER_OF_COLUMNS 4

#define ROW_START_PORT PORTA_ID
#define ROW_START_PIN PIN0_ID

#define COLUMN_START_PORT PORTA_ID
#define COLUMN_START_PIN PIN4_ID

#define KEY_PRESSED LOGIC_LOW
#define KEY_NOT_PRESSED LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);


#endif /* KEYPAD_ME_H_ */
