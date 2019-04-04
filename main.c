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

volatile unsigned char sigHigh = 1;

int main(void)
{
	// period 333.33 ms, on-time = 75 ms
	int offtime= 2500;//16144; // OFFTIME
	int ontime = 2500;//4688;  // ONTIME

	int period = offtime + ontime; //total time

	int top = (ontime / 2) + (offtime / 2); //half total time
	int mid = (ontime / 2); //half ontime

	//set TOP
	ICR1 = period;
	// set compare value to control duty cycle
	OCR1A = ontime;

	// enable non inverting 8-bit PWM
	TCCR1A = (1<<COM1A1);//|(1<<WGM11)|(1<<WGM10);

	// Timer clock = I/O clock
	// no prescaling
	TCCR1B |= (1 << CS10) | (1 << WGM13);



	// Enable Timer 2 output compare match interrupt
	TIMSK1 = (1 << OCIE2A) | (1 << TOV1);

	// Set Oc2A pin as output
	DDRB |= 0x80;
	sei();
	
    /* Replace with your application code */
	
    while (1) 
    {
		
    }
}

//----------------------------------------------------------------------
// Timer 1 CTC interrupt service routine (ISR)
//----------------------------------------------------------------------
ISR(TIMER1_COMPA_vect){
	// Send the PWM to output port that drives motor
	PORTB ^= 0x80; //can change to whatever output port is
}



