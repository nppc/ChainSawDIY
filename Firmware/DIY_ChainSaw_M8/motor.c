#include "main.h"
#include "motor.h"
#include "adc.h"

// start motor smoothly
uint8_t startMotor(void){
	cbi(PORTB, 2);
	cli();
	OCR1A = 95; // value to test
	//  OCR1B = 255; // value to test
	TCCR1A = (1<<WGM11) | (1<<WGM10);// | (1<<CS13) | (1<<CS11) ; // Fast PWM mode (value 3)
	TCCR1B = (1<<COM1A1) | (0<<COM1A0) | (1<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS01) | (1<<CS10); // Speed (/1024)
	//TIMSK |= (1<<OCIE1A) | (1<<OCIE1B) ;//(1<<TOIE1); // enable compare match and overflow interrupts
	sei();
	_delay_ms(30);
	//now motor starts at 50%. Increase the speed to 100%
	for(uint8_t i=100;i<190;i+=5){
		wdt_reset();
		OCR1A = i;
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
	cli();
	TCCR1A = 0; // stop timer
	TCCR1B = 0; // stop timer
	sei();
	sbi(PORTB, 1);
	//  _delay_ms(5);
	//  sbi(PORTB, 1); // make sure motor is on. can be done with resetting interrupts flags.
	run_state=1;
	return 0;
}

void stopMotor(void){
	sbi(PORTB, 2);
	// make sure that motor is off
	run_state=0;
	// stop timer
	cli();
	TCCR1A = 0; // stop timer
	TCCR1B = 0; // stop timer
	sei();
	cbi(PORTB,1);
	//	_delay_ms(5);
	//    cbi(PORTB,1);
}

