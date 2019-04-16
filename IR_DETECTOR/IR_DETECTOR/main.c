/*
 * IR_DETECTOR.c
 *
 * Created: 4/9/2019 2:13:42 PM
 * Author : cookna1
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int saved = 3;

int main(void)
{
	
	 
	DDRF = 0x03;
	//DDRF = (1 << DDF0) | (1 << DDF1);
	PCICR = 4;
	PCMSK2 = (1 << PCINT16) | (1 << PCINT17);

	
	//PORTB = 0;
	sei();
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

//LEFT SENSOR and RIGHT 
/
ISR(PCINT2_vect) {
	
	if(PINK & (1 << PK0)){ //LEFT SENSOR
		PORTF |= (1 << PF0);  //TODO This part should change based on what needs to be done if left sensor get high
		_delay_ms(100);
		PORTF &= 2;
	}
	else if(PINK & (1 << PK1)) { //RIGHT SENSOR
		PORTF |= (1 << PF1); //TODO This part should change based on what needs to be done if right sensor get high
		_delay_ms(100);
		PORTF &= 1;
	}
}




