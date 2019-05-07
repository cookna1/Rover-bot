/*
 * acx.h
 *
 * Created: 3/20/2014 11:08:37 AM
 *  Author: E. Frank Barry
 *
 */


#ifndef ACX_H_
#define ACX_H_

#define		MAX_THREADS			8
#define		NUM_THREADS			8        // This must be a power of two in order to work correctly

#define		STACK_CANARY		0xAA

#define		T0_STACK_SIZE		256
#define		T1_STACK_SIZE		256
#define		T2_STACK_SIZE		256
#define		T3_STACK_SIZE		256
#define		T4_STACK_SIZE		256
#define		T5_STACK_SIZE		256
#define		T6_STACK_SIZE		256
#define		T7_STACK_SIZE		256

#define		STACK_MEM_SIZE		(T0_STACK_SIZE + T1_STACK_SIZE + \
								T2_STACK_SIZE + T3_STACK_SIZE + T4_STACK_SIZE +\
								T5_STACK_SIZE + T6_STACK_SIZE + T7_STACK_SIZE)

#define		T0_STACK_BASE_OFFS	(T0_STACK_SIZE-1)
#define		T1_STACK_BASE_OFFS	(T0_STACK_BASE_OFFS+T1_STACK_SIZE)
#define		T2_STACK_BASE_OFFS	(T1_STACK_BASE_OFFS+T2_STACK_SIZE)
#define		T3_STACK_BASE_OFFS	(T2_STACK_BASE_OFFS+T3_STACK_SIZE)
#define		T4_STACK_BASE_OFFS	(T3_STACK_BASE_OFFS+T4_STACK_SIZE)
#define		T5_STACK_BASE_OFFS	(T4_STACK_BASE_OFFS+T5_STACK_SIZE)
#define		T6_STACK_BASE_OFFS	(T5_STACK_BASE_OFFS+T6_STACK_SIZE)
#define		T7_STACK_BASE_OFFS	(T6_STACK_BASE_OFFS+T7_STACK_SIZE)

#define		T0_CANARY_OFFS		0
#define		T1_CANARY_OFFS		(T0_CANARY_OFFS+T0_STACK_SIZE)
#define		T2_CANARY_OFFS		(T1_CANARY_OFFS+T1_STACK_SIZE)
#define		T3_CANARY_OFFS		(T2_CANARY_OFFS+T2_STACK_SIZE)
#define		T4_CANARY_OFFS		(T3_CANARY_OFFS+T3_STACK_SIZE)
#define		T5_CANARY_OFFS		(T4_CANARY_OFFS+T4_STACK_SIZE)
#define		T6_CANARY_OFFS		(T5_CANARY_OFFS+T5_STACK_SIZE)
#define		T7_CANARY_OFFS		(T6_CANARY_OFFS+T6_STACK_SIZE)

#define		T0_ID	0
#define		T1_ID	1
#define		T2_ID	2
#define		T3_ID	3
#define		T4_ID	4
#define		T5_ID	5
#define		T6_ID	6
#define		T7_ID	7

#define THREAD_CONTEXT_SIZE  18  // Number of bytes (registers) saved during context switch

#ifndef __ASSEMBLER__

// Make sure NULL is defined for pointers
#ifndef NULL
#define NULL ((void *)0)
#endif

// Make sure byte is defined
#ifndef byte
typedef uint8_t byte;
#endif

extern byte x_thread_id;
#define x_getTID()	x_thread_id


//typedef void(* PTHREAD)(int, char * );
//---------------------------------------------------------------------------
// PTHREAD is a type that represents how threads are called--
// It is just a pointer to a function returning void
// that is a passed an int and a char * as parameters.
//---------------------------------------------------------------------------
typedef void (*PTHREAD)(void);
typedef void (*PTHREAD_ARGS)(int argc, void *argv);
//---------------------------------------------------------------------------
// This union is used to provide access to both bytes of a thread address
//---------------------------------------------------------------------------
typedef  union {
	PTHREAD pthread;
	uint8_t addr[3];    // This works for 2560 not UNO -- assumes 3-byte return address
} PTU;

typedef  union {
	PTHREAD_ARGS pthread;
	uint8_t addr[3];    // This works for 2560 not UNO -- assumes 3-byte return address
} PTU_ARGS;

//---------------------------------------------------------------------------
// This type is used for entries in the stack control table
//---------------------------------------------------------------------------
typedef	struct {
		uint8_t *sp;
		uint8_t *spBase;
}STACK_CONTROL;

// ACX Function prototypes
void	x_init(void);
void	x_delay(unsigned int);
unsigned long x_gtime();
void	x_schedule(void);
void x_new(uint8_t, PTHREAD , bool);
void x_new_args(uint8_t, PTHREAD_ARGS , int, char **, bool);
void x_yield(void);
uint8_t bit2mask8(uint8_t);
void x_suspend(uint8_t);
void x_resume(uint8_t);
void x_disable(uint8_t);
void x_enable(uint8_t);
void x_stack_overflow(int);

#endif


#endif /* ACX_H_ */
