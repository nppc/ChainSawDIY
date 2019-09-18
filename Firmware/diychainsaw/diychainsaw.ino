#include <avr/wdt.h>
#include <Tiny4kOLED.h> //https://github.com/datacute/Tiny4kOLED

//#define NOHANG
//#define ENABLEFONT

#define CELLS 5	// define LiIon cells count

// PB1 is ON/OFF switch

#define MAXMEASUREDVOLT 27.22

// formula: 1SVolt * 1024 * 128 / MAXMEASUREDVOLT
#define V1S6 (uint32_t)19725 * CELLS //4.15
#define V1S5 (uint32_t)19012 * CELLS //4.00
#define V1S4 (uint32_t)18299 * CELLS //3.85
#define V1S3 (uint32_t)17586 * CELLS //3.70
#define V1S2 (uint32_t)17111 * CELLS //3.60
#define V1S1 (uint32_t)16635 * CELLS //3.50
#define V1S0 (uint32_t)14259 * CELLS //3.00


// with current resistor divider (120K/27K) we can measure max 27.22 volts
// so, the formula is: V = 27.22 * RAWADC / 1024
// or RAWADC = V * 1024 / 27.22
// for 4S: fully charged is 631 (4.2v per cell); 451 - fully discharged (3v per cell)

uint8_t run_state = 0; // 0 - stopped; 1 - running
uint8_t prev_batInd = 0;

static const uint8_t PROGMEM stateOK[32*4] = {
  252,254,7,3,3,3,3,3,3,3,3,3,131,195,227,131,3,3,3,3,3,3,3,3,3,3,3,3,3,7,254,252,
  255,255,0,0,0,0,4,14,30,62,63,127,119,227,227,193,128,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,
  255,255,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3,7,15,14,28,56,112,192,128,0,0,0,0,0,255,255,
  63,127,224,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,193,197,196,192,192,224,127,63,
};

static const uint8_t PROGMEM stateDANGER[32*4] = {
  0,0,128,192,240,240,248,252,  252,126,62,63,31,31,31,31, 31,31,31,31,63,190,254,252,  252,248,240,240,192,128,0,0,
  248,254,255,255,255,15,3,1,   0,0,0,0,0,128,192,224,    240,248,252,254,127,63,31,15,    7,3,15,255,255,255,254,248,
  31,127,255,255,255,240,192,224,  240,248,252,254,127,63,31,15,  7,3,1,0,0,0,0,0,   128,192,240,255,255,255,127,31,
  0,0,1,3,15,15,31,63,  63,127,125,252,248,248,248,248,  248,248,248,248,252,124,126,63,  63,31,15,15,3,1,0,0,
};

static const uint8_t PROGMEM batBot1[13*4] = {
  254,255,3,251,251,251,251,251,251,251,251,251,3,
  255,255,0,255,255,255,255,255,255,255,255,255,0,
  255,255,0,255,255,255,255,255,255,255,255,255,0,
  127,255,192,223,223,223,223,223,223,223,223,223,192,
};

static const uint8_t PROGMEM batBot0[13*4] = {
  254,255,3,3,3,3,3,3,3,3,3,3,3,
  255,255,0,0,0,0,0,0,0,0,0,0,0,
  255,255,0,0,0,0,0,0,0,0,0,0,0,
  127,255,192,192,192,192,192,192,192,192,192,192,192,
};

static const uint8_t PROGMEM bat1[10*4] = {
  251,251,251,251,251,251,251,251,251,3,
  255,255,255,255,255,255,255,255,255,0,
  255,255,255,255,255,255,255,255,255,0,
  223,223,223,223,223,223,223,223,223,192,
};

static const uint8_t PROGMEM bat0[10*4] = {
  3,3,3,3,3,3,3,3,3,3,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  192,192,192,192,192,192,192,192,192,192,
};

static const uint8_t PROGMEM batEnd[7*4] = {
  255,254,0,0,0,0,0,
  255,255,254,254,254,254,252,
  255,255,127,127,127,127,63,
  255,127,0,0,0,0,0,
};

void draw_Bat(uint8_t val){
	if(val==0){oled.bitmap(0,0,13,4,batBot0);} else {oled.bitmap(0,0,13,4,batBot1);}
	for(uint8_t ix=2;ix<=6;ix++){if(ix<=val){oled.bitmap(13+(ix-2)*10,0,10,4,bat1);}else{oled.bitmap(13+(ix-2)*10,0,10,4,bat0);}}
	oled.bitmap(13+50,0,7,4,batEnd);
}

void draw_clear(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	uint16_t j = 0;
 	for (uint8_t y = y0; y < y0 + y1; y++) {
		oled.setCursor(x0,y);
		oled.fillLength(0,x1);
	}
}

bool isBatteryEmpty(uint16_t rawadc){
  return ((uint32_t)rawadc*128 >= V1S0 ? LOW : HIGH);
}

// 3.0v - 0%
// 3.5v - 15%
// 3.6v - 33%
// 3.7v - 50%
// 3.85v - 66%
// 4.0v - 83%
// 4.2v - 100%

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

bool getButtonState(){
  bool tmp = bitRead(PINB, 1);
  delay(10);
  if(tmp == bitRead(PINB, 1)){return tmp;}else{return !tmp;}
}

void disableWatchdog(){
  wdt_disable();
}

void setup() {
  //stop motor
  bitClear(PORTB, 3);
  bitSet(DDRB, 3);

  bitClear(DDRB, 1); // Input
  bitSet(PORTB, 1); // Enable pullup

  disableWatchdog();
  
  // configure ADC
  ADMUX =
           (0 << ADLAR) |     // do not left shift result (for 10-bit values)
           (0 << REFS2) |     // Sets ref. voltage to VCC
           (0 << REFS1) |     // Sets ref. voltage to VCC
           (0 << REFS0) |     // Sets ref. voltage to VCC
           (0 << MUX3)  |     // use ADC2 for input (PB4)
           (0 << MUX2)  |     // use ADC2 for input (PB4)
           (1 << MUX1)  |     // use ADC2 for input (PB4)
           (0 << MUX0);       // use ADC2 for input (PB4)
 ADCSRA = 
           (1 << ADEN)  |     // Enable ADC 
           (1 << ADPS2) |     // set prescaler to 64, bit 2 
           (1 << ADPS1) |     // set prescaler to 64, bit 1 
           (1 << ADPS0);      // set prescaler to 64, bit 0 


  ADCSRA |= (1 << ADSC); // start first conversion
  
  #ifdef ENABLEFONT
  oled.setFont(FONT8X16);
  #endif
  oled.begin();
  oled.clear();
  draw_Bat(0); // prefill bufer with empty battery bitmap
  oled.on();
  oled.switchRenderFrame();
  delay(50);
  oled.clear(); //clear invisible frame

  //if switch is ON then show warning
  if(getButtonState()==0){
    oled.bitmap(128-32,0,32,4,stateDANGER);
    oled.switchFrame();
    delay(500);
  }
  //wait until button is released
  while(getButtonState()==0){
    // button is pressed
    delay(100);
  }  

  // enable 1s watchdog with reset
  cli();
  WDTCR = (1<<WDCE);
  WDTCR = (1<<WDE) | (1<<WDP1) | (1<<WDP2); // 1s
  sei();
}


ISR(TIMER1_COMPA_vect){
  // set pin
  bitClear(PORTB, 3);
  //tmrval1 = TCNT1;
}

//ISR(TIMER1_OVF_vect){
ISR(TIMER1_COMPB_vect){
  //clear pin
  bitSet(PORTB, 3);
  //tmrval = TCNT1;
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

// start motor smoothly
void startMotor(){
  cli();
  OCR1A = 95; // value to test
  OCR1B = 255; // value to test	
  TCCR1 = (1<<CS13) | (1<<CS11) ; // Fast PWM mode (value 3)
  //TCCR0B = (0<<WGM02) | (1<<CS02) | (0<<CS01) | (0<<CS00); // Speed (value 3)
  TIMSK |= (1<<OCIE1A) | (1<<OCIE1B) ;//(1<<TOIE1); // enable compare match and overflow interrupts
  sei();
  delay(30);
  //now motor starts at 50%. Increase the speed to 100%
  for(uint8_t i=100;i<190;i+=5){
    wdt_reset();
    OCR1A = i;
  	delay(25);
  	// check battery and button
  	uint16_t rawadc = readADC();
	bool isBemp = isBatteryEmpty(rawadc);
    if(isBemp || getButtonState()==1){
      stopMotor();
	    return HIGH; // exit with low bat indication
  	} 
  }
  // at the end run motor at full speed
  cli();
  TCCR1 = 0; // stop timer
  sei();
  bitSet(PORTB, 3);
  delay(5);
  bitSet(PORTB, 3); // make sure motor is on. can be done with resetting interrupts flags.
  run_state=1;
  return LOW;
}

void stopMotor(){
    // make sure that motor is off
    run_state=0;
    // stop timer
	cli();
    TCCR1 = 0;
	sei();
    bitClear(PORTB,3);
	delay(5);
    bitClear(PORTB,3);  
}

void loop() {  
  wdt_reset();
  uint16_t rawadc = readADC();
  uint8_t batInd = getbatIndicatorVal(rawadc);
  bool batEmpty = isBatteryEmpty(rawadc);
  // redraw screen only when needed (to avoid unnecesarry i2c traffic)
  if(batInd!=prev_batInd || batEmpty){
    prev_batInd = batInd;
	draw_Bat(batInd);
    
    if(batEmpty){
      oled.bitmap(128-32,0,32,4,stateDANGER);
    }else{
      oled.bitmap(128-32,0,32,4,stateOK);
    }
    oled.switchFrame();
    delay(50); // make sure, that page switch doesn't occur too often
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
    disableWatchdog();
#ifndef NOHANG
	while(1==1){
		bitClear(PORTB,3); // just to be 100% sure that motor will not start
		draw_Bat(0);
		oled.bitmap(128-32,0,32,4,stateDANGER);
		oled.switchFrame();
		delay(300);
		draw_clear(0,0,70,4);
		oled.bitmap(128-32,0,32,4,stateDANGER);
		oled.switchFrame();
		delay(600);
	}
#endif
  }

}

