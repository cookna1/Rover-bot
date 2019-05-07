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
#include "rover.h"
#include "wheels.h"
//#include "PSerial.h"
#include "IRdetector.h"
#include "USsensor.h"
#include "acx.h"
#include "acxserial.h"

volatile int mode;

int getMode() {
	return mode;
}

void setMode(int newMode) {
	mode = newMode;
}

void init() {
	//setTime();
	//PSerial_open(0, BAUD9600, SERIAL_8N1);
	mode = STRAIGHT;

	initIRDet();
	initWheels();
	//initUS();
	sei();
	
}


int main(void)
{
	init();
	
	x_init();
	x_delay(1000);
	

	x_new(2, wheelControl, 1);
	x_new(1, irControl, 1);
	//x_new(3, USdetect, 1);

/* Replace with your application code */
	
	while (1)
	{		//turn(90);		//_delay_ms(2000); 		x_yield();
	}
}

