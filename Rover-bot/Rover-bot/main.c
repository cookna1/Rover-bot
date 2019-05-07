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
#include "time.h"

//ICR4H and ICR4L - Input Capture Register 4
volatile unsigned int tcnt;
volatile unsigned char sreg;
volatile unsigned int th, tl;
volatile int RISING_EDGE;

int timeset;

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
	
	//Timer 4 Control Register B
	TCCR4B |= (1<<ICES4)|(1<<ICNC4); // ICES4: Rising Edge Triggers Capture
	//TIFR4 = (1<<ICF4);
	//TCNT4 = 0;
	//ICR4 = 5;
	RISING_EDGE = 1;
	//Enable Interrupts
	sei();
	
	setTime();
	 timeset = 0;
    /* Replace with your application code */
    while (1) 
    {	
		//Used to display timeset value - for testing purposes
		if (timeset) {
			PORTF = 0x07;
			int count = timeset / 100;
			for(int i = 0; i < count; i+=1) {
				PORTF = 0x04;
				_delay_ms(200);
				PORTF = 0x00;
				_delay_ms(200);
			}
			count = (timeset - (count * 100)) / 10;
			for(int i = 0; i < count; i++) {
				PORTF = 0x02;
				_delay_ms(200);
				PORTF = 0x00;
				_delay_ms(200);
			}	
			count = timeset % 10;
			PORTF = 0x00;
			for(int i = 0; i < count; i++) {
				PORTF = 0x01;
				_delay_ms(200);
				PORTF = 0x00;
				_delay_ms(200);
			}
		}
    }
}

//Input Capture Mode
ISR(TIMER4_CAPT_vect) {
	//test to see if making it inside
	PORTF ^= 0x07;
	//TCNT4 = 0;
	//TCCR4B &= ~(1<<ICES4); //Set up to capture the falling edge
	timeset = 101;
	//check rising edge
	if (RISING_EDGE) {
		RISING_EDGE = 0;
		TCCR4B &= ~(1<<ICES4); //Set up to capture the falling edge
		TCNT4 = 0;
		//clearTime();
	} 
	//check falling edge
	else {
		RISING_EDGE = 1;
		TCCR4B |= (1<<ICES4); //Set up to capture the rising edge
		_delay_ms(1000);
		th = TCNT4H - th;
		tl = TCNT4H - tl;
		//timeset = TCNT4 - timeset;
		timeset = ICR4;
		TIMSK4 &= ~(1<<ICIE4);
	}
}
