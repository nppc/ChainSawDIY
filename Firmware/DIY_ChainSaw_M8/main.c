#include "main.h"
#include "i2c.h"
#include "adc.h"
#include "oled.h"
#include "motor.h"

uint8_t run_state = 0; // 0 - stopped; 1 - running
uint8_t prev_batInd = 0;

uint8_t getButtonState(void){
	uint8_t tmp = bitRead(PIND, 2);
	_delay_ms(10);
	if(tmp == bitRead(PIND, 2)){return tmp;}else{return (tmp==0 ? 1 : 0);}
}


int main(void)
{
	// ****** initialization ******
	//stop motor
	sbi(PORTB, 1);
	sbi(DDRB, 1);
	// button  with internal pull up
	cbi(DDRD, 2);
	sbi(PORTD, 2);
	//FAN
	cbi(PORTB, 2);
	sbi(DDRB, 2);

	cli();

	wdt_disable();

	adc_init();
	i2c_init();
	oled_init();

	oled_clear_display();
	oled_enable_display();
	oled_setCol(0);
	oled_setRow(0);
	
	oled_draw_Bat(0); // empty battery bitmap
	_delay_ms(50);

	//if switch is ON then show warning
	if(getButtonState()==0){
		oled_bitmap(128-32,0,32,4,oled_stateDANGER);
		_delay_ms(500);
	}
	//wait until button is released
	while(getButtonState()==0){
		// button is pressed
		_delay_ms(100);
	}  

	// enable 1s watchdog with reset
	//cli();
	wdt_reset();
	WDTCR = (1<<WDCE) | (1<<WDE); // enable config
	WDTCR = (1<<WDE) | (1<<WDP1) | (1<<WDP2); // 1s
	//sei();

	//oled_bitmap(128-32,0,32,4,oled_stateDANGER);

    // ******* endless loop ******
	while (1){
		wdt_reset();
		uint16_t rawadc = readADC();
		uint8_t batInd = getbatIndicatorVal(rawadc);
		uint8_t batEmpty = isBatteryEmpty(rawadc);

		// redraw screen only when needed (to avoid unnecessary i2c traffic)
		if(batInd!=prev_batInd || batEmpty){
			prev_batInd = batInd;
			oled_draw_Bat(batInd);

			if(batEmpty){
				oled_bitmap(128-32,0,32,4,oled_stateDANGER);
			}else{
				oled_bitmap(128-32,0,32,4,oled_stateOK);
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
			// should we initiate start process?
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
				sbi(PORTB,1); // just to be 100% sure that motor will not start
				oled_draw_Bat(0);
				oled_bitmap(128-32,0,32,4,oled_stateDANGER);
				_delay_ms(300);
				oled_clear(0,0,70,4);
				//oled_bitmap(128-32,0,32,4,oled_stateDANGER);
				_delay_ms(600);
			}
			#endif
		}
	}		
}

#ifdef DEBUGSIM
void _delay_ms(uint16_t ms){
	
}
#endif


