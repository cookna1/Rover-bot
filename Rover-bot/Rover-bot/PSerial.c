/*
 * PSerial.c
 *
 * Created: 2/10/2019 5:50:36 PM
 *  Author: Eli
 *  Author: Andrew
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


#include "PSerial.h"

void PSerial_open(unsigned char port, long speed, int config){
    switch (port) {
        case 0: 
			UCSR0B |= 0x18;
            UCSR0C = config;
			UBRR0 = speed;
            break;
        case 1:
            UCSR1C = config;
			UCSR1B |= 0x18;
            UBRR1 = speed;
            break;
        case 2:
            UCSR2C = config;
			UCSR2B |= 0x18;
            UBRR2 = speed;
            break;
        case 3:
            UCSR3C = config;
			UCSR3B |= 0x18;
            UBRR3 = speed;
            break;
        default:
            break;
    }
	PSerial_read(port);
}

long ComputeSpeed(long speed) {
	if (speed == 2400l) return 416l;
	if (speed == 4800l) return 207l;
	if (speed == 9600l) return 104l;
	if (speed == 14400l) return ((1.0f/14400.0f) * 1000000); //68l;
	if (speed == 19200l) return 51l;
	if (speed == 28800l) return 34l;
	if (speed == 38400l) return 25l;
	if (speed == 57600l) return 16l;
	if (speed == 76800l) return 12l;
	if (speed == 115200l) return 8l;
	if (speed == 230400l) return 3l;
	if (speed == 250000l) return 3l;
	return 103l;
}

int PSerial_read(unsigned char port){
    int data = -1;

    switch (port) {
        case 0: 
           if (UCSR0A & (1<<RXC0))
                data = UDR0;
           break;
        case 1:
            if (UCSR1A & (1<<RXC1))
                data = UDR1;
            break;
        case 2:
            if (UCSR2A & (1<<RXC2))
                data = UDR2;
            break;
        case 3:
             if (UCSR3A & (1<<RXC3))
                data = UDR3;
            break;
        default :
            break;
    }
    return data;
}

char PSerial_readw(unsigned char port){
    char data = -1;
    switch (port) {
        case 0: 
           while (!(UCSR0A & (1<<RXC0)));
           data = UDR0;
           break;
        case 1:
           while (!(UCSR1A & (1<<RXC1)));
           data = UDR1;
           break;
        case 2:
           while (!(UCSR2A & (1<<RXC2)));
           data = UDR2;
           break;
        case 3:
           while (!(UCSR3A & (1<<RXC3)));
           data = UDR3;
           break;
        default :
            break;
    }
    return data;

}

int PSerial_write(unsigned char port, char data){
	switch (port) {
		case 0:
			if (!((UCSR0A & (1<<UDRE0)))) {
				//write to the port
				UDR0 = data;
				return 0;
			}
			else {
				return -1;
			}
		case 1:
			if (!((UCSR1A & (1<<UDRE1)))) {
				//write to the port
				UDR1 = data;
			return 0;
			}
			else {
				return -1;
			}
		case 2:
			if (!((UCSR2A & (1<<UDRE2)))) {
				//write to the port
				UDR2 = data;
				return 0;
			}
			else {
				return -1;
			}
		case 3:
			if (!((UCSR3A & (1<<UDRE3)))) {
				//write to the port
				UDR3 = data;
				return 0;
			}
			else {
				return -1;
			}
		default:
			return -1;
	}
	
}

void PSerial_writew(unsigned char port, char data){
	switch (port) {
		case 0:
			while(!((UCSR0A & (1<<UDRE0))));
			UDR0 = data;
			break;
		case 1:
			while(!((UCSR1A & (1<<UDRE1))));
			UDR1 = data;
			break;
		case 2:
			while(!((UCSR2A & (1<<UDRE2))));
			UDR2 = data;
			break;
		case 3:
			while(!((UCSR3A & (1<<UDRE3))));
			UDR3 = data;
			break;
		default:
			break;
	}
	
}

void PSprint(unsigned char port, char * str) {
	for (int i = 0; str[i] != '\0'; i++) {
		PSerial_writew(port, str[i]);
	}
	
}

/*
 * PSprintf prints a formatted string to into a serial TX.
 *  wrapper for printf(format, ...) for serial port output
 * 
 * @param port : port number
 * @param format : string to be formatted
 * @param ... arguments for printf
 */
void PSprintf(unsigned char port, char * format, ...) {
	va_list args;
	va_start(args, format);
	
	char * str = "ERROR";

	vsprintf(str, format, args);
	PSprint(port, str);
	
	va_end(args);
}
