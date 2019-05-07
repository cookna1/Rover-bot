/*
 * CFile1.c
 *
 * Created: 4/10/2019 2:56:56 PM
 *  Author: thorpah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "rover.h"
#include "wheels.h"
#include "acx.h"
#include "acxserial.h"

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
int leftCount = 0;
volatile unsigned int rightcount = 0;
volatile unsigned int RwasOn;
int LwasOn;
int oldJ = 0;

void wheelControl(){
	while(1) {
		if (getMode() == STRAIGHT) {
			if(l_ds == 0) {
				straight(0.2);
			}
		}
		x_yield();
	}
}

void go1foot() {
	leftCount = 0;
	rightcount = 0;
	straight(0.7);
	float inches = 0;
	while(leftCount < 150) {
		 //PORTF ^= (1<<PF2);
	}
	straight(0);
}

void straight(float ds) {
	cli();
	setDutyCycle(ds, L_WHEEL);
	setDutyCycle(ds, R_WHEEL);
	sei();
}

void stop() {
	
	setMode(STOPPED);
	changeDirection(FORWARD, L_WHEEL);
	changeDirection(FORWARD, R_WHEEL);
	straight(0);
}

void setTurnLeft() {
	
	changeDirection(FORWARD, L_WHEEL);
	changeDirection(BACKWARD, R_WHEEL);
	setDutyCycle(0.5, L_WHEEL);
	setDutyCycle(0.5, R_WHEEL);
}


void setTurnRight() {
	
	changeDirection(BACKWARD, L_WHEEL);
	changeDirection(FORWARD, R_WHEEL);
	setDutyCycle(0.5, L_WHEEL);
	setDutyCycle(0.5, R_WHEEL);
}

void turn(int d) {
	int oldMode = getMode();
	stop();
	setMode(TURNING);
	//_delay_ms(100);
	cli();
	
	if (d > 0) setTurnLeft();
	else  {
		d *= -1;
		setTurnRight();
	}
	leftCount = 0;
	rightcount = 0;
	
	sei();
	
	int count = (d * 25) / 90;

	while(leftCount < count) {
		 PORTF ^= (1<<PF2);
	}
	stop();
	setMode(oldMode);
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
	cli();
	if (dutycycle == 0) {
		if (wheel == L_WHEEL) OCR5A = 0;
		else if (wheel == R_WHEEL) OCR5B = 0;
	} else {
		int ontime = ((int)(dutycycle * 400.0) + 400) ;
		
		if (wheel == L_WHEEL) {
			for (int i = 0; i < ontime; i += 1) {
				OCR5A = i;
			}
		} else if (wheel == R_WHEEL) {
			for (int i = 0; i < ontime; i += 1) {
				OCR5B = i;
			}
		}
	}
	TCNT5 = 0;
	sei();
}


// pin 15 reads the right wheel, functions as the master
ISR(PCINT1_vect) {
	//cli();
	//PSprintf(0, "%d\n\r", leftCount);
	//PORTB ^= 0x80;
	//PORTF ^= (1 << PF2);
	
	int J = PINJ;
	
	int change = J ^ oldJ;
	
	//PORTF = change;
	
	int RisON = (PINJ | (1<<PJ1));
	int LisON = (PINJ | (1<<PJ0));
	
	// If master
	if(change | (1 << PJ1)) {
		//	update interval time
		rightcount = rightcount + 1;
		// else if slave
	}
	if(change | (1 << PJ0)) {
		//	compare interval time to master and adjust duty cycle accordingly.
		leftCount = leftCount + 1;
	}
	
	RwasOn = RisON;
	LwasOn = LisON;
	oldJ = J;
	//sei();
}

