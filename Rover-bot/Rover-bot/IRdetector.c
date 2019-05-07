/*
 * IRdetector.c
 *
 * Created: 5/6/2019 6:28:01 PM
 *  Author: thorpah
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "rover.h"
#include "IRdetector.h"
#include "wheels.h"
#include "acx.h"
#include "acxserial.h"

void initIRDet() {
	DDRF &= ~((1<<PF7) | (1<<PF6));
	DDRF |= 0x03;
}

int turnedOn = 0;

void irControl() {
	while(1) {
		if (getMode() == DONE) {
			// do nothing
		} else if(PINF & (1 << PD6) && !(PINF & (1 << PD7))){ //LEFT SENSOR
			//PORTF |= (1 << PF0);  //TODO This part should change based on what needs to be done if left sensor get high
			//_delay_ms(100);
			//PORTF &= 1;
			turn(-5);
		}
		else if(PINF & (1 << PD7) && !(PINF & (1 << PD6))) { //RIGHT SENSOR
			//PORTF |= (1 << PF1); //TODO This part should change based on what needs to be done if right sensor get high
			//_delay_ms(100);
			//PORTF &= 2;
			turn(5);
		} else if (!(PINF & (1 << PD6) && (PINF & (1 << PD7)))) {// both sensors
			stop();
			if (turnedOn) setMode(DONE);
			
		} else {
			turnedOn = 1;
		}
		x_yield();
	}
}

void disableIRDet() {
	
}