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

//sei();

/* Replace with your application code */
	//_delay_ms(1);
	//changeDirection(FORWARD, L_WHEEL);
	
	DDRC = 0x0F;
	DDRL = 0x0F;
	while (1)
	{
		changeDirection(FORWARD, R_WHEEL);
		//PORTL = 0x08;
		_delay_ms(5000);
		changeDirection(BACKWARD, R_WHEEL);
		_delay_ms(5000);
		//_delay_ms(5000);
		//changeDirection(FORWARD, L_WHEEL);
		//_delay_ms(5000);
		//changeDirection(BACKWARD, L_WHEEL);
		
	}
}

