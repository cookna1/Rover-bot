/*
 * PSerial.h
 *
 * Created: 2/10/2019 5:51:03 PM
 *  Author: Eli
 */ 


#ifndef PSERIAL_H_
#define PSERIAL_H_

#define DATABITS 1
#define STOPBITS 3
#define PARITYBITS 4

#define BAUD2400 416
#define BAUD4800 207
#define BAUD9600 104
#define BAUD14400 69
#define BAUD19200 52
#define BAUD28800 34
#define BAUD38400 26
#define BAUD57600 17
#define BAUD76800 13
#define BAUD115200 8
#define BAUD230400 4
#define BAUD250000 3
#define BAUD500000 1
#define BAUD1000000 0

#define SERIAL_5N1  (0x00 | (0 << DATABITS))
#define SERIAL_6N1  (0x00 | (1 << DATABITS))
#define SERIAL_7N1  (0x00 | (2 << DATABITS))
#define SERIAL_8N1  (0x00 | (3 << DATABITS))     // (the default)
#define SERIAL_5N2  (0x08 | (0 << DATABITS))
#define SERIAL_6N2  (0x08 | (1 << DATABITS))
#define SERIAL_7N2  (0x08 | (2 << DATABITS))
#define SERIAL_8N2  (0x08 | (3 << DATABITS))
#define SERIAL_5E1  (0x20 | (0 << DATABITS))
#define SERIAL_6E1  (0x20 | (1 << DATABITS))
#define SERIAL_7E1  (0x20 | (2 << DATABITS))
#define SERIAL_8E1  (0x20 | (3 << DATABITS))
#define SERIAL_5E2  (0x28 | (0 << DATABITS))
#define SERIAL_6E2  (0x28 | (1 << DATABITS))
#define SERIAL_7E2  (0x28 | (2 << DATABITS))
#define SERIAL_8E2  (0x28 | (3 << DATABITS))
#define SERIAL_5O1  (0x30 | (0 << DATABITS))
#define SERIAL_6O1  (0x30 | (1 << DATABITS))
#define SERIAL_7O1  (0x30 | (2 << DATABITS))
#define SERIAL_8O1  (0x30 | (3 << DATABITS))
#define SERIAL_5O2  (0x38 | (0 << DATABITS))
#define SERIAL_6O2  (0x38 | (1 << DATABITS))
#define SERIAL_7O2  (0x38 | (2 << DATABITS))
#define SERIAL_8O2  (0x38 | (3 << DATABITS))

#define RX_BIT 7
#define TX_BIT 6

void PSerial_open(unsigned char port, long speed, int config);

long ComputeSpeed(long speed);

int PSerial_read(unsigned char port);

char PSerial_readw(unsigned char port);

int PSerial_write(unsigned char port, char data);

void PSerial_writew(unsigned char port, char data);

void PSprint(unsigned char port, char * str);

void PSprintf(unsigned char port, char * format, ...);

#endif /* PSERIAL_H_ */
