//#include <U8x8lib.h>
#include <Tiny4kOLED.h> //https://github.com/datacute/Tiny4kOLED

//U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(U8X8_PIN_NONE);
//U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(2,0,U8X8_PIN_NONE);

uint8_t buf[8];

static const uint8_t PROGMEM bat0[32] = {254,255,3,251,251,251,251,251,  251,251,251,251,3,251,251,251,  251,251,251,251,251,251,3,251,  251,251,251,251,251,251,251,251};
static const uint8_t PROGMEM bat1[32] = {255,255,0,255,255,255,255,255,  255,255,255,255,0,255,255,255,  255,255,255,255,255,255,0,255,  255,255,255,255,255,255,255,255};
static const uint8_t PROGMEM bat2[32] = {127,255,192,223,223,223,223,223,  223,223,223,223,192,223,223,223,  223,223,223,223,223,223,192,223,  223,223,223,223,223,223,223,223};

void setup() {
  
  
  //u8x8.begin();
  oled.begin();
  oled.clear();
  oled.on();
}

void drawTileF(uint8_t x, uint8_t y, uint8_t len, const uint8_t * bufF){
  for(uint8_t i=0;i<len;i++){
    for(uint8_t i1=0;i1<8;i1++)buf[i1]=pgm_read_byte(bufF+(i*8+i1));
    //u8x8.drawTile(x+i, y, 1, buf);  
  }  
}


void loop() {
  uint8_t tiles[16] = { 0x0f,0x0f,0x0f,0x0f,0xf0,0xf0,0xf0,0xf0, 1, 3, 7, 15, 31, 63, 127, 255};
  //uint8_t bat0[32] = {254,255,3,251,251,251,251,251,  251,251,251,251,3,251,251,251,  251,251,251,251,251,251,3,251,  251,251,251,251,251,251,251,251};
  //uint8_t bat1[32] = {255,255,0,255,255,255,255,255,  255,255,255,255,0,255,255,255,  255,255,255,255,255,255,0,255,  255,255,255,255,255,255,255,255};
  //uint8_t bat2[32] = {127,255,192,223,223,223,223,223,  223,223,223,223,192,223,223,223,  223,223,223,223,223,223,192,223,  223,223,223,223,223,223,223,223};

/*
  u8x8.drawTile(6, 0, 2, tiles);
  drawTileF(0, 0, 4, bat0);
  drawTileF(0, 1, 4, bat1);
  drawTileF(0, 2, 4, bat1);
  drawTileF(0, 3, 4, bat2);
  */
  
  oled.clear();
  oled.bitmap(0,0,32,1,bat0);
  oled.bitmap(0,1,32,1,bat1);
  oled.bitmap(0,2,32,1,bat1);
  oled.bitmap(0,3,32,1,bat2);
  oled.switchFrame();
}


