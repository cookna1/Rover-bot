/*
 * wheels.h
 *
 * Wheels offers a control interface for wheel control
 *
 * Wheels reserve Digital Pins 22-25 (PORTA 0x0F) for PWM signals.
 *
 * Created: 4/10/2019 2:33:49 PM
 *  Author: thorpah
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define R_WHEEL 0
#define L_WHEEL 1

#define FORWARD 0
#define BACKWARD 1

#define L_FORWARD	 0x01
#define L_BACKWARD	 0x02
#define R_FORWARD	 0x04
#define R_BACKWARD	 0x08

void initWheels();

void changeDirection(int direction, int wheelNumber);

// setDutyCycle accepts a dutycycle (number between 0.0 and 1.0) and the wheel (L_WHEEL or R_WHEEL)
void setDutyCycle(float dutycycle, int wheel);

#endif /* INCFILE1_H_ */