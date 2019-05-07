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
#include "IRRemote.h"



void initIRRemote();
void displayCount(int count);

//ICR4H and ICR4L - Input Capture Register 4
volatile unsigned int tcnt;
volatile unsigned char sreg;
volatile unsigned int th, tl;
int ON;
int cycle;

unsigned int timeset;
unsigned int previousPeriod, previousPulseWidth, startTime, stopTime;
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

	
	//Enable Interrupts
	sei();

	ON = 0;	

	timeset = 1;
    
	initIRRemote();
	
	PORTF = 0x07;
    while (1) 
    {
/*
		if (timeset) {
			displayCount(previousPeriod);
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
		}*/
    } 
}
