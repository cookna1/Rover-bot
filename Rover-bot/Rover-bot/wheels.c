/*
 * CFile1.c
 *
 * Created: 4/10/2019 2:56:56 PM
 *  Author: thorpah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "wheels.h"

int L_DIRECTION;
int R_DIRECTION;

volatile int l_setting;
volatile int r_setting;

int offtime = 10;
int r_ontime;
int l_ontime;

void initWheels() {
	DDRC |= 0x0F; 
	DDRL |= (1 << PL3) | (1 << PL4);
	
	int l_ontime = 100; // ONTIME

	int l_period = offtime + l_ontime; //total time

	// set up left timer
	ICR5 = l_period;
	OCR5A = l_ontime;
	OCR5B = l_ontime;
	TCCR5A = (1<<COM5A1) | (1<<COM5B1);
	TCCR5B |= (1 << CS51) | (1 <<WGM53);
	TIMSK5 = (1 << OCIE5A) | (1 << OCIE5B) | (1 << TOV5);
	
	PORTC |= L_BACKWARD;
	PORTC |= R_FORWARD; 
	
}

void changeDirection(int direction, int wheelNumber) {
	//_delay_ms(100);
	if (wheelNumber == L_WHEEL && direction == FORWARD) {
		PORTC &= 0xF3;
		PORTC |=  L_FORWARD;
	} else if (wheelNumber == L_WHEEL && direction == BACKWARD) {
		PORTC &= 0xF3;
		PORTC |=  L_BACKWARD;
	} else if (wheelNumber == R_WHEEL && direction == FORWARD) {
		PORTC &= 0xFC;
		PORTC |=  R_FORWARD;
	} else if (wheelNumber == R_WHEEL && direction == BACKWARD) {
		PORTC &= 0xFC;
		PORTC |=  R_BACKWARD;
	}

}

// setDutyCycle accepts a dutycycle (number between 0.0 and 1.0) and the wheel (L_WHEEL or R_WHEEL)
void setDutyCycle(float dutycycle, int wheel) {
	
}