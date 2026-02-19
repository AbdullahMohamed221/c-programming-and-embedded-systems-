/*
 * timer.h
 *
 *  Created on: Oct 25, 2025
 *      Author: Abdullah Said
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"



/*different timers*/
typedef enum{
	TIMER0,TIMER1,TIMER2

}Timer_ID_Type;

/*different prescalers
 * */
typedef enum{
	NO_CLK,CLK,CLK_8,CLK_64,CLK_256,CLK_1024

}Timer_ClockType;

/*different modes
 * */
typedef enum{
	NORMAL,CTC
}Timer_ModeType;

/*struct the contain the configurations of the timer
 * */
typedef struct
{
 uint16 timer_InitialValue;
 uint16 timer_compare_MatchValue;     /*it will be used in compare mode
only*/
 Timer_ID_Type  timer_ID;
 Timer_ClockType timer_clock;
 Timer_ModeType  timer_mode;
}Timer_ConfigType;

/*Description: Function to initialize the Timer driver
 * Inputs: pointer to the configuration structure with type Timer_ConfigType.
 * Return: None
 * */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/*Description: Function to disable the Timer via Timer_ID.
 * Inputs: Timer_ID
 * Return: None
 * */
void Timer_deInit(Timer_ID_Type timer_type);

/* Description: Function to set the Call Back function address to the required Timer.
 * Inputs: pointer to Call Back function and Timer Id you want to set The Callback to it.
 *  Return: None
 * */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );

#endif /* TIMER_H_ */
