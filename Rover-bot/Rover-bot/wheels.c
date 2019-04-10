/*
 * CFile1.c
 *
 * Created: 4/10/2019 2:56:56 PM
 *  Author: thorpah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "wheels.h"

int L_DIRECTION;
int R_DIRECTION;

volatile int l_setting;
volatile int r_setting;

int offtime = 10;
int r_ontime;
int l_ontime;

void initWheels() {
	DDRA |= 0x0F; 
	
	int l_ontime = 1000; // ONTIME

	int l_period = offtime + l_ontime; //total time

	// set up left timer
	ICR1 = l_period;
	OCR1A = offtime;
	TCCR1A = (1<<COM1A1);
	TCCR1B |= (1 << CS10) | (1 << WGM13);
	TIMSK1 = (1 << OCIE2A) | (1 << TOV1);
	
	l_setting = L_FORWARD;
	
}

void changeDirection(int direction, int wheelNumber) {
	cli();
	if (wheelNumber == L_WHEEL) {
		PORTA &= 0xfC;
		l_setting = (direction == FORWARD) ? L_FORWARD : L_BACKWARD; 
	} else if (wheelNumber == R_WHEEL) {
		PORTA &= 0xf3;
		r_setting = (direction == FORWARD) ? R_FORWARD : R_BACKWARD;
	}
	sei();
}

// setDutyCycle accepts a dutycycle (number between 0.0 and 1.0) and the wheel (L_WHEEL or R_WHEEL)
void setDutyCycle(float dutycycle, int wheel) {
	
}


//----------------------------------------------------------------------
// Timer 1 CTC interrupt service routine (ISR)
// Used for left wheel
//----------------------------------------------------------------------

ISR(TIMER1_COMPA_vect){
	// Send the PWM to output port that drives motor
	if (l_setting == L_BACKWARD) PORTB |= 0x08;
	else PORTB &= 0x78;
	PORTA ^= l_setting; //can change to whatever output port is
}
