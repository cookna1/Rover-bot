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
PORTB |= 0x80;
initWheels();

sei();

/* Replace with your application code */

	while (1)
	{
		
		_delay_ms(1000);
		changeDirection(FORWARD, L_WHEEL);
		_delay_ms(1000);
		changeDirection(BACKWARD, L_WHEEL);
	}
}

