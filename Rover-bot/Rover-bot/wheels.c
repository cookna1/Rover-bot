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

// right wheel is master 
// left wheel is slave
int r_time;
int l_time;

// pin 15 reads the right wheel, functions as the master 
ISR(PCINT1_vect) {
	
		PORTB ^= 0x80;	
		// If master
		//	update interval time
		// else if slave
		//	compare interval time to master and adjust duty cycle accordingly. 
}


void initWheels() {
	DDRC |= 0x0F; 
	DDRL |= 0x18;
	
	int l_ontime = 0; // ONTIME
	int r_ontime = 0;

	int period = 1000; //total time

	// set up left timer
	ICR5 = period;
	setDutyCycle(0, L_WHEEL);
	setDutyCycle(0, R_WHEEL);

	TCCR5A |= (1 <<COM5A1) | (1 << COM5B1);
	TCCR5B |= (1 << WGM53) | (1 << CS51);
	
	
	PORTC |= L_FORWARD;
	PORTC |= R_FORWARD; 
	
	// setup photoregister slit detection.
	PORTJ &= ~((1 << PJ1) | (1 << PJ0));
	
	PCMSK1 |= (1 << PCINT9);
	PCMSK1 |= (1 << PCINT10);
	
	PCICR |= (1<<PCIE1);
	
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
	
	if (dutycycle == 0) {
		if (wheel == L_WHEEL) OCR5A = 0;
		else if (wheel == R_WHEEL) OCR5B = 0;
	} else {
		int ontime = ((int)(dutycycle * 400.0) + 400) ;
		
		if (wheel == L_WHEEL) OCR5A = ontime;
		else if (wheel == R_WHEEL) OCR5B = ontime;
	}
}

