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
#include "PSerial.h"

uint64_t timer;

int L_DIRECTION;
int R_DIRECTION;

volatile int l_setting;
volatile int r_setting;

int l_ds = 0; // ONTIME
int r_ds = 0;

int offtime = 10;

// right wheel is master 
// left wheel is slave
int lastPJ = 0;
int32_t leftCount = 0;
int32_t rightcount = 0;
int RwasOn;
int LwasOn;

// pin 15 reads the right wheel, functions as the master 
ISR(PCINT1_vect) {
		PSprintf(0, "%d\n\r", leftCount);
		PORTB ^= 0x80;	
		
		int RisON = (PINJ | (1<<PJ1));
		int LisON = (PINJ | (1<<PJ0));
		
		// If master
		if(!RwasOn && RisON) {
			//	update interval time
			rightcount++;
		// else if slave
		} 
		if(!LwasOn && LisON) {
			//	compare interval time to master and adjust duty cycle accordingly. 
			leftCount++;
			PSprintf(0, "Left entered\n\r");
			double ratio = leftCount / rightcount;
			if (leftCount < rightcount) {
				l_ds += 0.1;
				setDutyCycle(l_ds, L_WHEEL);
			} else if (leftCount > rightcount) {
				l_ds -= 0.1;
				setDutyCycle(l_ds, L_WHEEL);
			} else {
				
			}
			
		}
		RwasOn = RisON;
		LwasOn = LisON;
}

void initWheels() {
	DDRC |= 0x0F; 
	DDRL |= 0x18;
	
	timer = 0;

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

