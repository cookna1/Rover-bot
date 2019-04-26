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
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#include "PSerial.h"

//ICR4H and ICR4L - Input Capture Register 4
volatile unsigned int tcnt;
volatile unsigned char sreg;

volatile int RISING_EDGE;

/*
	Code for the IR Remote Controller
*/
int main(void)
{
	/*
	Use Timer4 input capture mode to capture and time pulses for IR command.
	PORTL bit 0 / IPC4 Digital Pin 49 for interrupt
	*/
	DDRB = 0x80;
	
	//Digital Data Register F : Setting Pins 0, 1, 2 for output (w)
	DDRF |= (1<<DDF0)|(1<<DDF1)|(1<<DDF2);
	
	//Timer 4 Interrupt Mask Register
	TIMSK4 |= (1<<ICIE5);
	//Timer 4 Controller Register : Rising edge triggers capture
	TCCR4B |= (1<<ICES4);
	
	TCNT4 = 0;
	ICR4 = 0;
	//Enable Interrupts
	sei();
	
	//DDRL |= (1<<DDL0); //Want to read from this
	
    /* Replace with your application code */
    while (1) 
    {	
		
    }
}

//Input Capture Mode
ISR(TIMER4_CAPT_vect) {
	//test to see if making it inside
	PORTF |= 0x01;
	PORTB |= 0x80;
	
	//check rising edge
	if (RISING_EDGE) {
		RISING_EDGE = 0;
		TCNT4 = 0; //clear counter
		TCCR4B &= ~(1<<ICES4); //Set up to capture the falling edge
	} 
	//check falling edge
	else {
		RISING_EDGE = 1;
		TCCR4B |= (1<<ICES4); //Set up to capture the rising edge
		tcnt = TCNT4; //read counter - maybe print it off?
	}
}
