#include <Tiny4kOLED.h> //https://github.com/datacute/Tiny4kOLED

#define CELLS 4	// define LiIon cells count

// with current resistor divider (120K/27K) we can measure max 27.22 volts
// so, the formula is: V = 27.22 * RAWADC / 1023
// or RAWADC = V * 1023 / 27.22
// for 4S: fully charged is 631 (4.2v per cell); 451 - fully discharged (3v per cell)


static const uint8_t PROGMEM stateOK[32*4] = {
  252,254,7,3,3,3,3,3,3,3,3,3,131,195,227,131,3,3,3,3,3,3,3,3,3,3,3,3,3,,7,254,252,
  255,255,0,0,0,0,4,14,30,62,63,127,119,227,227,193,128,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,
  255,255,0,0,0,0,0,0,0,0,0,0,0,0,1,1,3,7,15,14,28,56,112,192,128,0,0,0,0,0,255,255,
  63,127,224,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,1,5,4,0,0,224,127,63,
};

static const uint8_t PROGMEM stateDANGER[32*4] = {
  0,0,128,192,240,240,248,252,  252,126,60,62,63,31,31,31,31, 31,31,31,31,63,190,254,252,  252,248,240,240,192,128,0,0,
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
	for(ix=2;ix<=6;ix++){if(ix<=val){oled.bitmap(13+ix*10,0,10,4,bat1);}else{oled.bitmap(13+ix*10,0,10,4,bat0);}}
	oled.bitmap(13+50,0,7,4,batEnd);
}

void draw_clear()(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	uint16_t j = 0;
 	for (uint8_t y = y0; y < y0 + y1; y++) {
		oled.setCursor(x0,y);
		oled.fillLength(0,x1);
	}
}

void setup() {
  // set the timer
  cli();
  TCCR0A = (0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (1<<WGM01) | (1<<WGM00) ; // Fast PWM mode (value 3)
  TCCR0B = (0<<WGM02) | (0<<CS02) | (1<<CS01) | (1<<CS00); // Speed (value 3)
  TIMSK |= (1<<OCIE0A) | (1<<TOIE0); // enable compare match and overflow interrupts
  sei();

  OCR0A = 20; // value to test
  
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

  oled.begin();
  oled.clear();
  draw_Bat(0); // prefill byffer with empty battery bitmap
  oled.switchFrame();
  oled.on();
  
}

ISR(TIMER0_OVF_vect){
  // set pin
  bitSet(PORTB, 3);
}

ISR(TIMER0_COMPA_vect){
  //clear pin
  bitClear(PORTB, 3);
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
  for(uint8_t i=0;i<7;i++){
	oled.bitmap(127-32,0,32,4,stateOK);
	draw_Bat(i);
	oled.switchFrame();
	delay(1000);
	readADC();
  }
  for(uint8_t i=6;i>=0;i--){
	oled.bitmap(127-32,0,32,4,stateDANGER);
	draw_Bat(i);
	oled.switchFrame();
	delay(1000);
	readADC();
  }
}


