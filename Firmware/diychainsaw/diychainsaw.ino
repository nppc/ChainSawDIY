#include <Tiny4kOLED.h> //https://github.com/datacute/Tiny4kOLED

#define CELLS 4	// define LiIon cells count

// PB1 is ON/OFF switch

#define MAXMEASUREDVOLT 27.22
#define CELLMINVOLT 3.0
#define CELLMAXVOLT 4.2


// with current resistor divider (120K/27K) we can measure max 27.22 volts
// so, the formula is: V = 27.22 * RAWADC / 1024
// or RAWADC = V * 1023 / 27.22
// for 4S: fully charged is 631 (4.2v per cell); 451 - fully discharged (3v per cell)

uint8_t run_state = 0; // 0 - stopped; 1 - running

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

uint8_t getbatIndicatorVal(uint16_t rawadc){
  uint16_t adcmaxcharge = (uint16_t)((CELLS * (CELLMAXVOLT * 1000 * 1024 / MAXMEASUREDVOLT)) / 1000);
  uint16_t adcmincharge = (uint16_t)((CELLS * (CELLMINVOLT * 1000 * 1024 / MAXMEASUREDVOLT)) / 1000);
  uint16_t adc1mark = (uint16_t)((adcmaxcharge-adcmincharge) / 6);
  if(rawadc>adcmaxcharge) return 6;
  if(rawadc<adcmincharge) return 0;
  return   (rawadc - adcmincharge) / adc1mark;
}

bool getButtonState(){
  bool tmp = bitRead(PINB, 1);
  delay(10);
  if(tmp == bitRead(PINB, 1)){return tmp;}else{return !tmp;}
}

void setup() {
  //disable mosfet
  bitClear(PORTB, 3);
  bitSet(DDRB, 3);

  bitClear(DDRB, 1); // Input
  bitSet(PORTB, 1); // Enable pullup

  // set the timer

  cli();
  TCCR1 = (1<<CS13) | (1<<CS11) ; // Fast PWM mode (value 3)
  //TCCR0B = (0<<WGM02) | (1<<CS02) | (0<<CS01) | (0<<CS00); // Speed (value 3)
  TIMSK |= (1<<OCIE1A) | (1<<OCIE1B) ;//(1<<TOIE1); // enable compare match and overflow interrupts
  sei();
  
  OCR1A = 128; // value to test
  OCR1B = 255; // value to test

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

  oled.setFont(FONT8X16);
  oled.begin();
  oled.clear();
  draw_Bat(0); // prefill byffer with empty battery bitmap
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
	ADCSRA |= (1 << ADSC); // start new conversion
	while (bit_is_set(ADCSRA,ADSC)); // wait for current conversion to complete
	uint8_t low  = ADCL; // must read ADCL first
	uint8_t high = ADCH;
	return (high<<8) | low;
}

void loop() {  
  uint16_t rawadc = readADC();
  draw_Bat(getbatIndicatorVal(rawadc));
  oled.bitmap(128-32,0,32,4,stateOK);
  oled.switchFrame();
  delay(50); // make sure, that page switch doesn't occur too often
  // check button and start/stop motor
  if(getButtonState()==1){
    // button is not pressed
    // make sure that motor is off?
    run_state=0;
    // stop timer
    TCCR1 = 0;
    bitClear(PORTB,3);
  } else {
    // button is pressed
    // shuld we initiate start process?
  }

  // check battery and stop if battery empty
/*
  for(uint8_t i=0;i<7;i++){
	oled.bitmap(128-32,0,32,4,stateOK);
  //delay(10);
	oled.switchFrame();
	delay(300);
  }

  while(1){

    uint16_t rawadc = readADC();
    //draw_Bat(getbatIndicatorVal(rawadc));
    oled.clear();
    //oled.print(tmrval);
    oled.setCursor(0,2);
    //oled.print(tmrval1);
    //tmrval=0;
    //tmrval1=0;
    //draw_Bat(getbatIndicatorVal(rawadc));
    oled.switchFrame();
  // Write text to oled RAM (which is not currently being displayed).
    delay(500);
  }
*/
}

