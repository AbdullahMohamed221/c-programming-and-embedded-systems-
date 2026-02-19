 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

typedef enum
{
	BIT_5,BIT_6,BIT_7,BIT_8,BIT_9=7
}UART_BitDataType;

typedef enum
{
	NO_PARITY,EVEN_PARRITY=2,ODD_PARITY
}UART_ParityType;

typedef enum
{
	ONE_BIT,TWO_BIT
}UART_StopBitType;

typedef enum
{
	BAUD_RATE_600=600,BAUD_RATE_1200=1200,BAUD_RATE_2400=2400,BAUD_RATE_4800=4800,BAUD_RATE_9600=9600
}UART_BaudRateType;

typedef struct {
 UART_BitDataType bit_data;
 UART_ParityType parity;
 UART_StopBitType stop_bit;
 UART_BaudRateType baud_rate;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType* Confi_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
