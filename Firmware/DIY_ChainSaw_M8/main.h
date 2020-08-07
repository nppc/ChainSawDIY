#ifndef MAIN_H_
#define MAIN_H_

//#define DEBUGI2C
//#define NOHANG
//#define ENABLEFONT

#define F_CPU 8000000UL

#define CELLS 5	// define LiIon cells count

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// some macros
#define sbi(port, bit) (port) |= (1 << (bit))
#define cbi(port, bit) (port) &= ~(1 << (bit))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

uint8_t run_state = 0; // 0 - stopped; 1 - running
uint8_t prev_batInd = 0;

#endif /* MAIN_H_ */