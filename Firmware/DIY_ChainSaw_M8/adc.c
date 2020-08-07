#include "adc.h"
#include "main.h"

void adc_init(void){  
	// configure ADC
	ADMUX =
		   (0 << ADLAR) |     // do not left shift result (for 10-bit values)
		   (1 << REFS1) |     // Sets ref. voltage to VCC
		   (1 << REFS0) |     // Sets ref. voltage to VCC
		   (0 << MUX3)  |     // use ADC0 for input (PC0)
		   (0 << MUX2)  |     // use ADC0 for input (PC0)
		   (0 << MUX1)  |     // use ADC0 for input (PC0)
		   (0 << MUX0);       // use ADC0 for input (PC0)
	ADCSRA = 
		   (1 << ADEN)  |     // Enable ADC 
		   (1 << ADPS2) |     // set prescaler to 64, bit 2 
		   (1 << ADPS1) |     // set prescaler to 64, bit 1 
		   (0 << ADPS0);      // set prescaler to 64, bit 0 


	ADCSRA |= (1 << ADSC); // start first conversion
}

uint16_t readADC(void){
	while (bit_is_set(ADCSRA,ADSC)); // wait for any previous conversion
	uint16_t res32=0;
	for(uint8_t i=0;i<32;i++){
		ADCSRA |= (1 << ADSC); // start new conversion
		while (bit_is_set(ADCSRA,ADSC)); // wait for current conversion to complete
		uint8_t low  = ADCL; // must read ADCL first
		uint8_t high = ADCH;
		res32+=(uint16_t)((high<<8) | low);
	}
	return res32 /32;
}


bool isBatteryEmpty(uint16_t rawadc){
  return ((uint32_t)rawadc*128 >= V1S0 ? LOW : HIGH);
}

uint8_t getbatIndicatorVal(uint16_t rawadc){
  uint32_t adc128 = (uint32_t)rawadc * 128;
  if(adc128>=V1S6) return 6;
  if(adc128>=V1S5) return 5;
  if(adc128>=V1S4) return 4;
  if(adc128>=V1S3) return 3;
  if(adc128>=V1S2) return 2;
  if(adc128>=V1S1) return 1;
  if(adc128<V1S0) return 0;
  return 0;
}
