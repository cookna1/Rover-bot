/*
 * RangeSensor.c
 *
 * Author : James Wilson
 */ 

#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "rover.h"
#include "wheels.h"
#include "acx.h"
#include "acxserial.h"


static volatile int pulse = 0;
static volatile int i = 0;

void initUS() {
// 	DDRB = 0xFF;
 	DDRD &= 0xFB;
	
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1 << PCINT16) | (1 << PCINT17);
	MCUCR|=(1<<ISC00);
	
	TCCR1A = 0;
}

int USdetect(void)
{
	int distance = 0; //storing digital output

	_delay_ms(70);
	
	while(1)
	{
		if (1) {
			PORTD|=(1<<PIND0); //trigger high
			_delay_us(12);
			PORTD = (0<< PIND0); //trigger low
		
			distance = pulse/58; //distance

			if(distance < 100){
				//setMode(DONE);
				//PORTF |= 0x01;
			} else {
				//PORTF &= ~0x01;
			}
			distance = 0;
		}
		x_yield();
	}
}


ISR(PCINT2_vect) {
	
	PORTF ^= 0x01;

 	if (i==1) // HIGH to LOW
 	{
	 	TCCR1B=0; //stop counter
	 	pulse=TCNT1; //count memory is updated to int
	 	TCNT1=0; //resetting t he counter memory
	 	i=0;
 	}
 	if (i==0) //LOW to HIGH
 	{
		
	 	TCCR1B|=(1<<CS10); //Enable counter
	 	i=1;
 	}
	
}