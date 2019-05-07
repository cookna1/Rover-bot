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
#include "time.h"
#include "wheels.h"
//#include "PSerial.h"
#include "IRdetector.h"

void init() {
	//setTime();
	//PSerial_open(0, BAUD9600, SERIAL_8N1);
	initIRDet();
	initWheels();
}


int main(void)
{
//PORTB |= 0x80;
	//PSerial_open(0, BAUD9600, SERIAL_8N1);
	DDRB = 0x80;
	//DDRF |= (1<<DDF0)|(1<<DDF1)|(DDF2);
	init();
	//PORTJ &= ~(1 << PJ1);
	sei();

/* Replace with your application code */
	_delay_ms(1000);
	//changeDirection(FORWARD, L_WHEEL);
	
	setDutyCycle(0, L_WHEEL);
	setDutyCycle(0, R_WHEEL);

	//PORTL = 0x18;
	//PORTC = 0;
	//PORTC = L_FORWARD|R_FORWARD;
	

	
	while (1)
	{
		//unsigned long t = getTime();
		//PSprintf(0, "Time: %X\n\r", t);
		_delay_ms(3000);
		straight(0.5);
		//PORTF |= (1<<PF2);
// 		if (which++ % 2) {
// 			ds = (ds >= 0.5) ? 0.1 : (ds + 0.05);
// 			_delay_ms(2000);
// 			setDutyCycle(ds, L_WHEEL);
// 			setDutyCycle(ds, R_WHEEL);
// 		} else {
// 			ds = (ds >= .05) ? 0.1 : (ds + 0.05);
// 			_delay_ms(2000);
// 			setDutyCycle(ds, R_WHEEL);
// 			setDutyCycle(ds, L_WHEEL);
// 		}
// 		int on = PINJ & (1<<PJ0);
// 		if (on) {
// 			PORTB |= 0x80;
// 		}
// 		else {
// 			PORTB &= ~0x80;
// 		}
		
	}
}

