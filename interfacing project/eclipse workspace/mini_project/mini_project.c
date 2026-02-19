/*
 * mini_project.c
 *
 *  Created on: Sep 1, 2025
 *      Author: VIP Company
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

char sec_1 = 0;		//for the first seven segment
char sec_2 = 0;		//for the second seven segment
char min_1 = 0;		//for the third seven segment
char min_2 = 0;		//for the fourth seven segment
char hours_1 = 0;	//for the fifth seven segment
char hours_2 = 0;	//for the sixth seven segment
unsigned char flag_1 = 0;		//for pausing and resuming the timer
unsigned char flag_2 = 0;			// for choosing which mode will work
unsigned char flag_3 = 0;			//a flag for the buzzer

void multiplexed(void);	//this function is used to display the time on the 7 segment
void managing_variables(void);//used to manage timer variables for the 7 segment
void pause_resume(unsigned char flag);	//for pausing and resuming the timer
void mode_switcher(void);//this function is responsible for switching between the modes
void editing_time(void);//this function is responsible for editing the variables in the counting down mode
void buzzer(unsigned char flag);//this function check the conditions of the buzzer

ISR(TIMER1_COMPA_vect) {	//for the timer
	if (flag_2 == 0) {	//counting up mode
		sec_1++;	//incrementing the seconds every interrupt (every second)
	} else {	//counting down mode
		sec_1--;

	}
}
ISR(INT0_vect) {	//for reset interrupt
	sec_1 = sec_2 = min_1 = min_2 = hours_1 = hours_2 = 0;//resting the timer variables
}
ISR(INT1_vect) {	//for the pausing the timer
	flag_1 = 1;
}
ISR(INT2_vect) {		//for the resuming the timer
	flag_1 = 0;
}

void timer_1(void) {	//this will make an interrupt every second
	TCCR1A = (1 << FOC1A);// The FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode.
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);//for setting CTC mode and choosing prescaler 1024
	TCNT1 = 0;	//initialization for the register
	OCR1A = 15625;//It is continuously compared with the counter value (TCNT1) and after calculations the counter will reach this value after 1 second
	TIMSK |= (1 << OCIE1A);	//the Timer/Counter1 Output Compare A match interrupt is enabled
	SREG |= (1 << 7);	//enabling all interrupts
}

void INT_0_reset(void) {	//interrupt function for resetting the timer
	MCUCR |= (1 << ISC01);//setting interrupt zero to be triggered on the falling edge
	GICR |= (1 << INT0);	//enabling the external interrupt module
	SREG |= (1 << 7);		//enabling all interrupts
	DDRD &= ~(1 << PIN2);//setting the button into an input for reset interrupt
	PORTD |= (1 << PIN2);		//enabling internal pull-up resistance
}
void INT_1_pause(void) {	//interrupt function for pausing the timer
	MCUCR |= (1 << ISC11) | (1 << ISC10);//setting interrupt for 1 to be triggered on the raising edge
	GICR |= (1 << INT1);			// enabling the external interrupt module
	SREG |= (1 << 7);					//enabling all interrupts
	DDRD &= ~(1 << PIN3);// setting the button into an input for pause interrupt
	PORTD &= ~(1 << PIN3);		//disabling internal pull-up resistance
}
void INT_2_resume(void) {	//interrupt function for resuming the timer
	MCUCSR &= ~(1 << ISC2);		//falling edge on INT2 activates the interrupt.
	GICR |= (1 << INT2);		// enabling the external interrupt module
	SREG |= (1 << 7);			//enabling all interrupts
	DDRB &= ~(1 << PIN2);// setting the button into an input for resume interrupt
	PORTB |= (1 << PIN2);		//enabling internal pull-up resistance
}

int main(void) {
	timer_1();	//for the timer

	DDRA = 0x3F;	//setting the pins as output for the7 segments
	DDRC = 0x0F;	//setting the pins as output for the values of the decoder

	DDRD |= (1 << PIN4) | (1 << PIN5);//for the red led in case of counting up and for the yellow led in case of counting up
	PORTD |= (1 << PIN4);//as the default mode is counting up so, the red led is on
	PORTD &= ~(1 << PIN5);//as the default mode is counting up so, the yellow led is off

	DDRB &= ~(1 << PIN7);	//setting toggle button as an input
	PORTB |= (1 << PIN7);	//enabling internal pull up resistance

	DDRB &= ~(0x7B);//for the buttons that can edit the variables in counting down mode
	PORTB |= 0x7B;		//enabling internal pull up resistance

	DDRD |= (1 << PIN0);	//for the buzzer
	PORTD &= ~(1 << PIN0);	//setting the buzzer into zero

	INT_0_reset();	//reset interrupt
	INT_1_pause();	//pause interrupt
	INT_2_resume();	//resume interrupt

	while (1) {
		multiplexed();//this function is used to display the time on the 7 segment
		pause_resume(flag_1);	//for pausing and resuming the timer
		managing_variables();//used to manage timer variables for the 7 segment
		mode_switcher();//this function is responsible for switching between the modes
		editing_time();	//this function is responsible for editing time
		buzzer(flag_3);	//this function is responsible for operating the buzzer
	}
}

void multiplexed(void) {//this function is used to display the time on the 7 segment
	PORTA |= (1 << PIN0);	//for hour_2
	PORTC &= 0XF0;
	PORTC |= (hours_2 & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PIN0);

	PORTA |= (1 << PIN1);	//for hour_1
	PORTC &= 0XF0;
	PORTC |= (hours_1 & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PIN1);

	PORTA |= (1 << PIN2);	//for min_2
	PORTC &= 0XF0;
	PORTC |= (min_2 & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PIN2);

	PORTA |= (1 << PIN3);	//for min_1
	PORTC &= 0XF0;
	PORTC |= (min_1 & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PIN3);

	PORTA |= (1 << PIN4);	//for sec_2
	PORTC &= 0XF0;
	PORTC |= (sec_2 & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PIN4);

	PORTA |= (1 << PIN5);		//for sec_1
	PORTC &= 0XF0;
	PORTC |= (sec_1 & 0x0F);
	_delay_ms(2);
	PORTA &= ~(1 << PIN5);
}

void managing_variables(void) {
	//in case of counting up
	if (sec_1 == 10) {
		sec_2++;
		sec_1 = 0;
	}
	if (sec_2 == 6) {
		min_1++;
		sec_2 = 0;
	}
	if (min_1 == 10) {
		min_2++;
		min_1 = 0;
	}
	if (min_2 == 6) {
		hours_1++;
		min_2 = 0;
	}

	if (hours_1 == 10) {
		hours_2++;
		hours_1 = 0;
	}
	if (hours_2 == 10) {
		hours_2 = 0;
	}

//counting down

	if (sec_1 == 255) {
		sec_1 = 9;
		sec_2--;
	}
	if (sec_2 == 255) {
		sec_2 = 5;
		min_1--;
	}
	if (min_1 == 255) {
		min_1 = 9;
		min_2--;
	}
	if (min_2 == 255) {
		min_2 = 5;
		hours_1--;
	}
	if (hours_1 == 255) {
		hours_1 = 9;
		hours_2--;
	}
	if (hours_2 == 255) {
		hours_2 = 0;
	}

}

void pause_resume(unsigned char flag) {		//for pausing and resuming the timer
	if (flag == 1) {
		TCCR1B &= ~(1 << CS12) & ~(1 << CS11) & ~(1 << CS10);//closing the timer
	} else {
		TCCR1B |= (1 << CS12) | (1 << CS10);	//opening the timer
	}
}

void mode_switcher(void) {//this function is responsible for switching between the modes
	if ((flag_1 == 1)) {	//checking if the timer is closed or not
		if (!(PINB & (1 << PIN7))) {//checking if the toggle button is pressed
			PORTD ^= (1 << PIN4);	//closing the red lamp
			PORTD ^= (1 << PIN5);	// opening the yellow lamp
			if (PIND & (1 << PIN4)) {	//check if the red lamp is on or not
				flag_2 = 0;	//switching to counting up mode
			}
			if (PIND & (1 << PIN5)) {//checking if  the yellow lamp is on or not
				flag_2 = 1;	//switching to counting down mode
			}
			while (!(PINB & (1 << PIN7))) {	//to avoid continuous changing in the mode
				//to make sure that these functions work throughout the whole code
				multiplexed();
				managing_variables();
			}

		}

	}
}

void editing_time(void) {//this function is responsible for editing the variables in the counting down mode
	if ((flag_2 == 1) && (flag_1 == 1)) {//check if the timer in counting down mode and the timer is not working
		if (!(PINB & (1 << PIN1))) {	//for incrementing the hours
			hours_1++;
			while (!(PINB & (1 << PIN1))) {
				//to make sure that these functions work throughout the whole code
				multiplexed();
				managing_variables();
			}
		}
		if (!(PINB & (1 << PIN0))) {	//for decrementing the hours
			hours_1--;
			while (!(PINB & (1 << PIN0))) {
				//to make sure that these functions work throughout the whole code
				multiplexed();
				managing_variables();
			}
		}
		if (!(PINB & (1 << PIN4))) {	//for incrementing the minutes
			min_1++;
			while (!(PINB & (1 << PIN4))) {
				//to make sure that these functions work throughout the whole code
				multiplexed();
				managing_variables();
			}
		}
		if (!(PINB & (1 << PIN3))) {	//for decrementing the minutes
			min_1--;
			while (!(PINB & (1 << PIN3))) {
				//to make sure that these functions work throughout the whole code
				multiplexed();
				managing_variables();
			}
		}
		if (!(PINB & (1 << PIN6))) {	//for incrementing the seconds
			sec_1++;
			while (!(PINB & (1 << PIN6))) {
				//to make sure that these functions work throughout the whole code
				multiplexed();
				managing_variables();
			}

		}
		if (!(PINB & (1 << PIN5))) {	//for decrementing the seconds
			sec_1--;
			while (!(PINB & (1 << PIN5))) {
				//to make sure that these functions work throughout the whole code
				multiplexed();
				managing_variables();
			}
		}

	}
}

void buzzer(unsigned char flag) {//this function is responsible for operating the buzzer
	if ((flag_2 == 1) && (sec_1 == 0) && (sec_2 == 0) && (min_1 == 0)
			&& (min_2 == 0) && (hours_1 == 0) && (hours_2 == 0)) {
		flag_3 = 1;
		flag_1 = 1;
	}
	else{
		flag_3 = 0;
	}

	if (flag == 1) {	//conditions are true
		PORTD |= (1 << PIN0);	//the buzzer will work
	} else { //conditions are false
		PORTD &= ~(1 << PIN0);	//setting the buzzer into zero
	}
}
