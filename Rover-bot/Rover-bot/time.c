/*
 * time.c
 *
 * A simple time library for synchronization. 
 *
 * Created: 4/30/2019 7:17:44 AM
 *  Author: thorpah
 */ 

#include <avr/interrupt.h>
#include "time.h"

int tickTime = 15625;
short initialized = 0;
unsigned long timeCounter;

int timerInitialized(void) {
	return initialized;
}

unsigned long getTime(void) {
	return timeCounter;
}

void clearTime(void) {
	timeCounter = 0;
}

void setTime() {
	initialized = 1;
	timeCounter = 0;
	TCCR2A |= (1 << COM2A1);
	TCCR2B |= (1 << CS20) | (1 << CS22) | (1 << WGM22);
	TIMSK2 |= (1 << OCIE2A);
	
	OCR2A = tickTime;
}

ISR(TIMER2_COMPA_vect) {
	timeCounter++;
	/*if (timeCounter % 1000 == 0)*/ //PORTB ^= 0x80;
}