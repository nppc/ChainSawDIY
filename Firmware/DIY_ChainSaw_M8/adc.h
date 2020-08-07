#ifndef ADC_H_
#define ADC_H_

#include "main.h"

// If voltage divisor for ADC is changed, or vref, then need to recalculate this constant
// with current resistor divider (100K/10K) we can measure max 28.16 volts
// so, the formula is: V = 28.16 * RAWADC / 1024
// or RAWADC = V * 1024 / 28.16
// for 4S: fully charged is 631 (4.2v per cell); 451 - fully discharged (3v per cell)
#define MAXMEASUREDVOLT 28160 //(mV)

// 3.0v - 0%
// 3.5v - 15%
// 3.6v - 33%
// 3.7v - 50%
// 3.85v - 66%
// 4.0v - 83%
// 4.2v - 100%
// formula: 1SVolt * 1024 * 128 / MAXMEASUREDVOLT
#define V1S6 (uint32_t)4150 * 1024 * 128 / MAXMEASUREDVOLT * CELLS //4.15V
#define V1S5 (uint32_t)4000 * 1024 * 128 / MAXMEASUREDVOLT * CELLS //4.00V
#define V1S4 (uint32_t)3850 * 1024 * 128 / MAXMEASUREDVOLT * CELLS //3.85V
#define V1S3 (uint32_t)3700 * 1024 * 128 / MAXMEASUREDVOLT * CELLS //3.70V
#define V1S2 (uint32_t)3600 * 1024 * 128 / MAXMEASUREDVOLT * CELLS //3.60V
#define V1S1 (uint32_t)3500 * 1024 * 128 / MAXMEASUREDVOLT * CELLS //3.50V
#define V1S0 (uint32_t)3000 * 1024 * 128 / MAXMEASUREDVOLT * CELLS //3.00V


void adc_init(void);
uint16_t readADC(void);
uint8_t isBatteryEmpty(uint16_t rawadc);
uint8_t getbatIndicatorVal(uint16_t rawadc);

#endif /* ADC_H_ */