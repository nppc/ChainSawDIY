#ifndef MAIN_H_
#define MAIN_H_

#define COOLER
//#define DEBUGSIM
//#define NOHANG
//#define NOLOWBAT

#define F_CPU 8000000UL

#define CELLS 5	// define LiIon cells count

#include <avr/io.h>
#include <avr/wdt.h>
#include <stdint.h>
#ifndef DEBUGSIM
#include <util/delay.h>
#endif
#include <avr/interrupt.h>

// some macros
#define sbi(port, bit) (port) |= (1 << (bit))
#define cbi(port, bit) (port) &= ~(1 << (bit))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#ifdef DEBUGSIM
void _delay_ms(uint16_t ms);
#endif

uint8_t getButtonState(void);

// global variables
extern uint8_t run_state; // = 0; // 0 - stopped; 1 - running
extern uint8_t prev_batInd; // = 0;

#endif /* MAIN_H_ */