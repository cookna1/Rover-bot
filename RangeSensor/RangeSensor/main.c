/*
 * RangeSensor.c
 *
 * Author : James Wilson
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


static volatile int pulse = 0;
static volatile int i = 0;

int main(void)
{
	
	DDRB = 0xFF;
	DDRD = 0xFB;
		
	PCICR = 4;
	PCMSK2 = (1 << PCINT16) | (1 << PCINT17);
	MCUCR|=(1<<ISC00);
	
	TCCR1A = 0;
	
	int distance = 0; //storing digital output
	
	sei();
	_delay_ms(70);
	
	while(1)
	{
		PORTD|=(1<<PIND0); //trigger high
		_delay_us(12); 
		PORTD = (0<< PIND0); //trigger low
		
		distance = pulse/58; //distance

		if(distance < 100){
			//turn right or left b/c object is in the way
			PORTB = (1 << PB7);
		}
		else{
			PORTB = (0 << PB7);
		}
		distance = 0;

	}
}


ISR(PCINT2_vect) {
	
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


