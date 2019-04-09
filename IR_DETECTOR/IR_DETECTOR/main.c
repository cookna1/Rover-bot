/*
 * IR_DETECTOR.c
 *
 * Created: 4/9/2019 2:13:42 PM
 * Author : cookna1
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



int main(void)
{
	
	
	DDRF |= 0x00;
	DDRB |= (1 << PB5);
	
	PCMSK2 = 0x80;
	PORTB = 0;
	sei();
    /* Replace with your application code */
    while (1) 
    {
		if((PINF & (1 << PF0))) {
			PORTB |= (1 << PB5);
		}
		else
			PORTB = 0;
    }
}

ISR(PCINT2_vect) {
	
}








