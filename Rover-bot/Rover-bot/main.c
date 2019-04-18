/*
* Robot_Project.c
*
* Created: 4/4/2019 2:12:16 PM
* Author : Eli McGalliard
* Author : Andrew Thorp
* Author : James Wilson
* Author : Nathan Cook
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "wheels.h"


int main(void)
{
//PORTB |= 0x80;
	initWheels();
	DDRB = 0x80;
	PORTJ &= ~(1 << PJ1);
	sei();

/* Replace with your application code */
	_delay_ms(1000);
	//changeDirection(FORWARD, L_WHEEL);
	
	//setDutyCycle(1, L_WHEEL);
	//setDutyCycle(1, R_WHEEL);

	//PORTL = 0x18;
	//PORTC = 0;
	//PORTC = L_FORWARD|R_FORWARD;
	
	while (1)
	{
		//PORTL = 0x18;
		int on = PINJ & (1<<PJ0);
		if (on) {
			PORTB |= 0x80;
		}
		else {
			PORTB &= ~0x80;
		}
	}
}

