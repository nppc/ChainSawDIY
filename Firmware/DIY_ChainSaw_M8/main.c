#include <avr/io.h>
#include <avr/wdt.h>
#include "main.h"
#include "i2c.h"
#include "oled.h"

bool getButtonState(){
	bool tmp = bitRead(PIND, 2);
	_delay_ms(10);
	if(tmp == bitRead(PIND, 2)){return tmp;}else{return !tmp;}
}


int main(void)
{
	// ****** initialization ******
	//stop motor
	bitClear(PORTB, 1);
	bitSet(DDRB, 1);
	// button
	bitClear(DDRD, 2); // Input
	bitSet(PORTD, 2); // Enable pullup
	//FAN
	bitSet(PORTB, 2);
	bitSet(DDRB, 2);

	wdt_disable();

	adc_init();
	i2c_init();
	oled_init();

	oled_clear_display();
	oled_enable_display();
	oled_setCol(0);
	oled_setRow(0);
	
	oled_draw_Bat(0); // prefill bufer with empty battery bitmap
	_delay_ms(50);

	//if switch is ON then show warning
	if(getButtonState()==0){
		oled_bitmap(128-32,0,32,4,stateDANGER);
		_delay_ms(500);
	}
	//wait until button is released
	while(getButtonState()==0){
		// button is pressed
		_delay_ms(100);
	}  

	// enable 1s watchdog with reset
	cli();
	WDTCR = (1<<WDCE);
	WDTCR = (1<<WDE) | (1<<WDP1) | (1<<WDP2); // 1s
	sei();

	//oled_bitmap(128-32,0,32,4,stateDANGER);

    // ******* endless loop ******
	while (1){
		wdt_reset();
		uint16_t rawadc = readADC();
		uint8_t batInd = getbatIndicatorVal(rawadc);
		bool batEmpty = isBatteryEmpty(rawadc);

		// redraw screen only when needed (to avoid unnecesarry i2c traffic)
		if(batInd!=prev_batInd || batEmpty){
			prev_batInd = batInd;
			oled_draw_Bat(batInd);

			if(batEmpty){
				oled_bitmap(128-32,0,32,4,stateDANGER);
			}else{
				oled_bitmap(128-32,0,32,4,stateOK);
			}
			//oled.switchFrame();
			_delay_ms(50); // make sure, that page switch doesn't occur too often
		}
		// check button and start/stop motor
		if(getButtonState()==1){
			// button is not pressed
			stopMotor();
		} else {
			// button is pressed
			// shuld we initiate start process?
			if(run_state!=1){
				batEmpty = startMotor();
			}
		}
		// If battery empty - stop the motor and hang the firmware
		if(batEmpty){
			stopMotor();
			wdt_disable();
			#ifndef NOHANG
			while(1){
				bitClear(PORTB,1); // just to be 100% sure that motor will not start
				oled_draw_Bat(0);
				oled_bitmap(128-32,0,32,4,stateDANGER);
				_delay_ms(300);
				ssd1306_clear(0,0,70,4);
				//oled_bitmap(128-32,0,32,4,stateDANGER);
				_delay_ms(600);
			}
			#endif
		}
	}		
}


// start motor smoothly
bool startMotor(void){
  bitClear(PORTB, 2);
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
	    return HIGH; // exit with low bat indication
  	}
	if(getButtonState()==1){
		//button is released while starting motor
		stopMotor();
	    return LOW; // exit
	}
  }
  // at the end run motor at full speed
  cli();
  TCCR1A = 0; // stop timer
  TCCR1B = 0; // stop timer
  sei();
  bitSet(PORTB, 1);
//  _delay_ms(5);
//  bitSet(PORTB, 1); // make sure motor is on. can be done with resetting interrupts flags.
  run_state=1;
  return LOW;
}

void stopMotor(){
    bitSet(PORTB, 2);
    // make sure that motor is off
    run_state=0;
    // stop timer
	cli();
  TCCR1A = 0; // stop timer
  TCCR1B = 0; // stop timer
	sei();
    bitClear(PORTB,1);
//	_delay_ms(5);
//    bitClear(PORTB,1);  
}



