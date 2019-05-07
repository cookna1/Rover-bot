/*
 * IRRemote.c
 *
 * Created: 5/7/2019 1:26:24 PM
 *  Author: mcgalliarder
 */ 


//Input Capture Mode
ISR(TIMER4_CAPT_vect) {
	
	TIMSK4 &= ~(1<<ICIE4); //Disable interrupt
	PORTF ^= 0x07;
	_delay_ms(5000);
	TIFR4 = ~(1<<ICF4);
	TIMSK4 = (1<<ICIE4); //Enable interrupt 
}


void initIRRemote() {
	/*Timer 4 Interrupt Mask Register
	  ICIE4: Timer/Counter, Input Capture Interrupt Enable
	*/
	TIMSK4 = (1<<ICIE4); // 
	
	/*Timer 4 Control Register B
	  ICES4: Rising Edge Triggers Capture
	  CS10: No Prescaler (Timer Clock = System Clock)
	*/
	TCCR4B = (1<<ICES4)|(CS10);
	
	//Clear input capture flag
	TIFR4 = (1<<ICF1);
	
	//Set Initial Timer Value
	TCNT4 = 0;
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