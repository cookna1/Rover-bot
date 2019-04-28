/*
 * RangeSensor.c
 *
 * Created: 4/11/2019 2:09:01 PM
 * Author : James Wilson
 */ 

#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
    DDRB |= 0x0; //config for input
	DDRB |= (1 << PB7);
	PORTB = 0;
	
	//Trigger Port
	DDRK |= 0xf;

	//Trigger Port and Echo Pin
	DDRK |=  (1 << PK1); //config for output
	DDRK = (0 << PK0); //config for input
    while (1) 
    {
		PORTB = (0 << PB7);
				
		//Send 5V high signal to Trig pin for at least 10 Us
		PORTK = (1 << PK1);
		_delay_us(10);
		PORTK = 0xc0;
		_delay_ms(100);
		
		//Get the echo
	
		if(!(PINK & (1 << PK0))){
			PORTB = (1 << PB6);		//Flash an LED if there is an echo	
		}
		
}

}

