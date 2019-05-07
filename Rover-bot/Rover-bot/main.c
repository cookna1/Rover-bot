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

#define HIGH_START 100 //or whatever the 9ms high time count is
#define LOW_START (HIGH_START/2) //or whatever the 4.5ms low time count is
#define LOGICAL_ONE (LOW_START/2)
#define LOGICAL_ZERO (LOGICAL_ONE/2)

void displayCount(int count);

//ICR4H and ICR4L - Input Capture Register 4
volatile unsigned int tcnt;
volatile unsigned char sreg;
volatile unsigned int th, tl;
volatile int RISING_EDGE;


unsigned int timeset;

/*
	Code for the IR Remote Controller
*/
int main(void)
{
	/*
	Use Timer4 input capture mode to capture and time pulses for IR command.
	PORTL bit 0 / IPC4 Digital Pin 35 for interrupt
	*/
	
	/*Digital Data Register B : Setting Pins 7 for output (w)*/
	DDRB |= 0x80;
	
	/*Digital Data Register F : Setting Pins 0, 1, 2 for output (w)*/
	DDRF |= (1<<DDF0)|(1<<DDF1)|(1<<DDF2);
	
	/*Timer 4 Interrupt Mask Register
	  ICIE4: Timer/Counter, Input Capture Interrupt Enable
	*/
	TIMSK4 = (1<<ICIE4); // 
	
	/*Timer 4 Control Register B
	  ICES4: Rising Edge Triggers Capture
	  CS10: No Prescaler (Timer Clock = System Clock)
	*/
	TCCR4B = (1<<ICES4)|(CS10); 
	
	//Set Initial Timer Value
	TCNT4 = 0;
	
    // Sets the ISR up to first handle rising edges
	RISING_EDGE = 1; 
	
	//Enable Interrupts
	sei();
	
	timeset = 0;
    
	//
	PORTF = 0x07;
    while (1) 
    {	
		if (timeset) {
			displayCount(timeset);
		}
		//Check to see if high beginning of transmission
		if (timeset == HIGH_START) {
			timeset = 0;
			while(!timeset)
				;
			//Check to see if low beginning of transmission
			if (timeset == LOW_START) {
				int bitCount = 0;
				
			}	
		}
    }
}

//Input Capture Mode
ISR(TIMER4_CAPT_vect) {
	PORTF ^= 0x07;
	//check rising edge
	if (RISING_EDGE) {
		RISING_EDGE = 0;
		timeset = ICR4;
		TCCR4B &= ~(1<<ICES4); //Set up to capture the falling edge
		TCNT4 = 0;
	} 
	//check falling edge
	else {
		RISING_EDGE = 1;
		TCCR4B |= (1<<ICES4); //Set up to capture the rising edge
		timeset = ICR4 - timeset;
		TIMSK4 &= ~(1<<ICIE4); //Disable interrupt to allow for count display
		th = TCNT4H - th;
		tl = TCNT4H - tl;
	}
}

/*
* Used for displaying count on Port 7 - Testing purposes
*/
void displayCount(int count) {
	PORTF = 0x00;
	count = timeset / 100;
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
