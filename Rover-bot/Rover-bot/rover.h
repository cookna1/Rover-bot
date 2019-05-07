/*
 * rover.h
 *
 * Created: 5/6/2019 8:37:50 PM
 *  Author: thorpah
 */ 


#ifndef ROVER_H_
#define ROVER_H_

#define STRAIGHT 1
#define STOPPED 0
#define TURNING 2
#define DONE -1

int getMode();
void setMode();

#endif /* ROVER_H_ */