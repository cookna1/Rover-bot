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
//#include "PSerial.h"

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
	PORTL bit 0 / IPC4 Digital Pin 35 for interrupt
	*/
	
	//Digital Data Register B : Setting Pins 7 for output (w)
	DDRB |= 0x80;
	//Digital Data Register F : Setting Pins 0, 1, 2 for output (w)
	DDRF |= (1<<DDF0)|(1<<DDF1)|(1<<DDF2);
	
	//Timer 4 Interrupt Mask Register
	TIMSK4 |= (1<<ICIE4); // ICIE4: Timer/Counter, Input Capture Interrupt Enable
	
	//Timer 4 Control Register A
	//Table 17-3 Set to Toggle OC4A on compare match (Do we need?)
	//TCCR4A |= (1<<COM4A0)|(1<<COM4B0)|(1<<COM4C0); 
	
	//Timer 4 Control Register B
	TCCR4B |= (1<<ICES4)|(1<<ICNC4); // ICES4: Rising Edge Triggers Capture
	//TIFR4 = (1<<ICF4);
	//TCNT4 = 0;
	//ICR4 = 5;
	
	//Enable Interrupts
	sei();
	
	
	//DDRL |= (1<<DDL0); //Want to read from this (Signal from IR Sensor)
	
	PORTF |= 0x07;
    /* Replace with your application code */
    while (1) 
    {	
		//while(!(TIFR4&(1<<ICF4)));
		while(!((PORTL >> PL0) & 0x01));
		PORTL |= (1<<PL0);
		PORTF ^= 0x07;
		_delay_ms(1000);
    }
}

//Input Capture Mode
ISR(TIMER4_CAPT_vect) {
	//test to see if making it inside
	PORTF &= ~(0x07);
	PORTB |= 0x80;
	TCNT4 = 0;
	TCCR4B &= ~(1<<ICES4); //Set up to capture the falling edge
	/*
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
	*/
}
