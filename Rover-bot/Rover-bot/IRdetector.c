/*
 * IRdetector.c
 *
 * Created: 5/6/2019 6:28:01 PM
 *  Author: thorpah
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "IRdetector.h"
#include "wheels.h"

void initIRDet() {
	DDRK &= ~0x03;
	DDRF |= 0x03;
	PCICR = 4;
	DDRF = 0x03;
	PCMSK2 = (1 << PCINT16) | (1 << PCINT17);

}

void disableIRDet() {
	
}

ISR(PCINT2_vect) {
	
	if(PINK & (1 << PK0) && !(PINK & (1 << PK1))){ //LEFT SENSOR
		//PORTF |= (1 << PF0);  //TODO This part should change based on what needs to be done if left sensor get high
		//_delay_ms(100);
		//PORTF &= 1;
		turn(-5);
	}
	else if(PINK & (1 << PK1) && !(PINK & (1 << PK0))) { //RIGHT SENSOR
		//PORTF |= (1 << PF1); //TODO This part should change based on what needs to be done if right sensor get high
		//_delay_ms(100);
		//PORTF &= 2;
		turn(5);
	} else if (PINK & (1 << PK0) && (PINK & (1 << PK1))) {// both sensors
		stop();
	}
}