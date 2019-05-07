/*
 * IRRemote.h
 *
 * Created: 5/7/2019 1:26:35 PM
 *  Author: mcgalliarder
 */ 


#ifndef IRREMOTE_H_
#define IRREMOTE_H_

#define HIGH_START 100 //or whatever the 9ms high time count is
#define LOW_START (HIGH_START/2) //or whatever the 4.5ms low time count is
#define LOGICAL_ONE (LOW_START/2)
#define LOGICAL_ZERO (LOGICAL_ONE/2)
#define RISING_EDGE ((TCCR4B >> ICES4) & 0x01)

void initIRRemote();
void displayCount();

#endif /* IRREMOTE_H_ */