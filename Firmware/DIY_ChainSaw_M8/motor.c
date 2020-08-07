#include "main.h"
#include "motor.h"
#include "adc.h"

// start motor smoothly
uint8_t startMotor(void){
#ifdef COOLER
	sbi(PORTB, 2);
#endif
	//cli();
	OCR1A = 75; // value to test
	//  OCR1B = 255; // value to test
	TCCR1A = (1<<COM1A1) | (1<<COM1A0) | (0<<WGM11) | (1<<WGM10); // Fast PWM mode (inverted) (value 5)
	TCCR1B = (1<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10); // Fast PWM 8bit, Speed (/256)
	//sei();
	
	_delay_ms(30);
	//now motor starts at 50%. Increase the speed to 100%
	for(uint8_t i=80;i<190;i+=6){
		wdt_reset();
		OCR1A = (uint16_t)i;
		_delay_ms(25);
		// check battery and button
		uint16_t rawadc = readADC();
		if(isBatteryEmpty(rawadc)){
			stopMotor();
			return 1; // exit with low bat indication
		}
		if(getButtonState()==1){
			//button is released while starting motor
			stopMotor();
			return 0; // exit
		}
	}

	// at the end run motor at full speed
	//cli();
	TCCR1A = 0; // stop timer
	TCCR1B = 0; // stop timer
	//sei();
	cbi(PORTB, 1);
	run_state=1;
	return 0;
}

void stopMotor(void){
//#ifdef COOLER
//	cbi(PORTB, 2); // don't turn off fan when motor stopped
//#endif
	// make sure that motor is off
	run_state=0;
	// stop timer
	//cli();
	TCCR1A = 0; // stop timer
	TCCR1B = 0; // stop timer
	//sei();
	sbi(PORTB,1);
}

