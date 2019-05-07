/*
 * ACXSystem.h
 *
 * Created: 4/11/2017 12:24:55 PM
 *  Author: barryef
 */ 


#ifndef ACXSYSTEM_H_
#define ACXSYSTEM_H_


/*
 * System.h
 *
 * Created: 3/2/2015 3:30:29 PM
 *  Author: barryef
 */ 


#ifndef NULL
#define NULL ((void *)0)
#endif

typedef uint8_t byte;



/*
 * Serial.h
 *
 * Created: 2/19/2015 3:48:34 PM
 *  Author: EFB
 */ 


#define DATABITS 1
#define STOPBITS 3
#define PARITYBITS 4

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

typedef struct {
    volatile uint8_t ucsra;
    volatile uint8_t ucsrb;
    volatile uint8_t ucsrc;
    volatile uint8_t reserved;
    volatile uint16_t ubrr;
    volatile uint8_t udr;
}SERIAL_PORT_REGS;

typedef struct {
    uint8_t rx_qid;
    uint8_t tx_qid;
    char *rx_buffer;
    int rx_bufsize;
    char *tx_buffer;
    int tx_bufsize;
}SERIAL_PORT;

#define P0_RX_BUFFER_SIZE   64
#define P0_TX_BUFFER_SIZE   64
#define P1_RX_BUFFER_SIZE   64
#define P1_TX_BUFFER_SIZE   64
#define P2_RX_BUFFER_SIZE   32
#define P2_TX_BUFFER_SIZE   32
#define P3_RX_BUFFER_SIZE   32
#define P3_TX_BUFFER_SIZE   32

int Serial_open(int, long, int );
void Serial_close(int);
void Serial_config(int, long, int);
int Serial_available(int);
int Serial_read(int);
int Serial_write(int, char);
int Serial_puts(int, char *);
void Serial0_config(long,int);
char Serial0_poll_read();
void Serial0_poll_write(char);
void Serial0_poll_print(char *);
void Serial1_config(long,int);
char Serial1_poll_read();
void Serial1_poll_write(char);
void Serial1_poll_print(char *);

// Test functions for software serial
void init_sw_serial_putc_test(long baudrate, int framing);
void init_sw_serial_getc_test(long baudrate, int framing);
void test_sw_serial_putc();
void test_sw_serial_getc();
void init_sw_serial_puts_test(long baudrate, int framing);
void test_sw_serial_puts();

// Debug functions
void debug_init(); // PORTB bit 7 is OUTPUT, initially OFF (main "L" LED on MEGA2560)
void debug_hang(); // hangs and blinks LED at 20 Hz (fast)
 
/*
 * Queues.h
 *	Defines constants, types and function prototypes for general purpose
 *  FIFO (byte-oriented) queue functions.
 *
 * Created: 3/2/2015 3:32:56 PM
 *  Author: barryef
 */ 


//
// Queue Control Block
//
#define		QCB_MAX_COUNT  	4	// defines maximum number of system queues.

#define		Q_FULL	0			// bit position of FULL status bit in QCB flags byte
#define		Q_EMPTY	1			// bit position of EMPTY status bit in QCB flags byte

//
//   Defined System Queues
//
#define		SERIAL0_IN_Q		0    // ID of USART0 serial inbound queue
#define		SERIAL0_OUT_Q		1    // ID of USART0 serial outbound queue

//
//   Queue Control Block Type
//
typedef struct {
    byte in;            // index of next char to be placed in queue (if not full)
    byte out;           // index of next char to be removed from queue (if not empty)
    byte smask;         // mask used to maintain circular queue access (mod size)
    byte flags;         // stores full and empty flags
    int available;      // number of bytes available to be read from queue
    char *pQ;           // pointer to queue data buffer
} QCB;


//
// Function Prototypes
//
byte Q_putc(byte , char);
byte Q_getc(byte , char * );
int8_t Q_create(int , char * );
void Q_delete(byte);
int Q_used(byte);
int Q_unused(byte);
byte Q_full(byte);
byte Q_empty(byte);




#endif /* ACXSYSTEM_H_ */