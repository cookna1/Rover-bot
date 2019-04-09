/*
 * TimerTest.c
 *
 * Created: 2/26/2019 2:31:06 PM
 * Author : Eli McGalliard mcgalliarder
 * Author : Andrew Thorp thorpah
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NORMALMODE 0
#define CTCMODE 1
#define PWMMODE 2

volatile unsigned char sigHigh = 1;
int choice = PWMMODE;
 
int main(void)
{
	if (choice == NORMALMODE) {
		/* Make sure power control for Timer 1 is off (enables the timer module) */
		PRR0 = 0x00;
		TCNT1 = 0;
		// period 333.33 ms, on-time = 75 ms
	
	
		TCCR1A = 0x00;
		// configure match register
		OCR1A = 4688;    // 75 msec
		// setup initial output state
		DDRB = 0x80;
		PORTB |= 0x80;
		// enable compare match A interrupt
		TIMSK1 = 0x02;
		// enable global interrupt
		sei();
		// start the timer
		TCCR1B = 0x04;   // clk/256 from prescaler
	}
	
	if (choice == CTCMODE) {
		
		/* Make sure power control for Timer 1 is off (enables the timer module) */
		PRR0 = 0x00;
		TCNT1 = 0;
		
		// period 333.33 ms, on-time = 75 ms
		int TOP1 = 16144; // OFFTIME
		int TOP2 = 4688;  // ONTIME
		
		cli();
		TCCR1A = 0x00;
		TCCR1B = 0x00;
		//TCCR0A = 0x02; //Sets CTC mode of operation?
		
		// configure match register
		ICR1 = TOP1;
		OCR1A = TOP2;    // 75 msec
		TCCR1B = 0x04;   // clk/256 from prescaler
		
		// turn on CTC mode:
		TCCR1B |= (1 << WGM12);

		// Set CS10 and CS12 bits for 1024 prescaler:
		TCCR1B |= (1 << CS10);
		TCCR1B |= (1 << CS12);

		// enable timer compare interrupt:
		TIMSK1 |= (1 << OCIE1A);
		sei();          // enable global interrupts
		
		// setup initial output state
		DDRB = 0x80;
		PORTB |= 0x80;
	}
	
	if (choice == PWMMODE) {

		// period 333.33 ms, on-time = 75 ms
		int offtime= 16144; // OFFTIME
		int ontime = 4688;  // ONTIME    	

		int period = offtime + ontime;

		int top = (ontime / 2) + (offtime / 2);
		int mid = (ontime / 2);

		//set TOP
		ICR1 = period;
	    // set compare value to control duty cycle
        OCR1A = ontime;

        // enable non inverting 8-bit PWM
        TCCR1A = (1<<COM1A1);//|(1<<WGM11)|(1<<WGM10);

        // Timer clock = I/O clock
        // no prescaling
        TCCR1B |=  (1 << CS12) | (1 << WGM13);



        // Enable Timer 2 output compare match interrupt
        TIMSK1 = (1 << OCIE2A) | (1 << TOV1);

        // Set Oc2A pin as output
        DDRB |= 0x80;
        sei();
	}
	
    while (1) 
    {
		// hang here--work done in ISR
    }
}

/*
//----------------------------------------------------------------------
// Timer 1 Compare-Match A interrupt service routine (ISR)
//----------------------------------------------------------------------
ISR(TIMER1_COMPA_vect){
	
	PORTB ^= 0x80;   // THIS IS WHAT I FORGOT--YOU HAVE TO CHANGE THE LED!!!
	
	if(sigHigh){
		OCR1A += 16144;    // 258.3 msec
		sigHigh = 0;
	}
	else {
		OCR1A += 4688;    // 75 msec
		sigHigh = 1;
	}
}
*/


//----------------------------------------------------------------------
// Timer 1 CTC interrupt service routine (ISR)
//----------------------------------------------------------------------
ISR(TIMER1_COMPA_vect){
	// start the timer
	PORTB ^= 0x80;
	//PINB;
	/*
	if (!TCCR1B){
		TCCR1B = 0x04; //start TCCR1B
				   //stop ICR1
		PORTB ^= 0x80;
	}
	else {
		TCCR1B = 0; //stop TCCR1B
					   //start ICR1
		PORTB ^= 0x80;
	}
	*/
}

//ISR_ALIAS(TIMER1_COMPA_vect,TIMER1);
/*
ISR(TIMER2_COMPA_vect){
	PORTB ^= 0x80;
	ICR1 = 0;
	OCR1A = 0;
}
*/
