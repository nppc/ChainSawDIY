#define SSD1306_COLUMNS 128
#define SSD1306_PAGES 4

#define SSD1306_COMMAND 0x00
#define SSD1306_DATA 0x40

/*
extern void ssd1306_init(void);
void ssd1306_send_command_start(void);
void ssd1306_send_command(uint8_t cmd);
void ssd1306_write_display_start(void);
void ssd1306_clear_display(void);
void setCol(uint8_t col);
void setRow(uint8_t row);
void ssd1306_printNumber(uint8_t num);
void ssd1306_print_uSv(void);
void ssd1306_printBars(void);
*/

/** Set Lower Column Start Address for Page Addressing Mode. */
#define SSD1306_SETLOWCOLUMN 0x00
/** Set Higher Column Start Address for Page Addressing Mode. */
#define SSD1306_SETHIGHCOLUMN 0x10
/** Set Memory Addressing Mode. */
#define SSD1306_MEMORYMODE 0x20
/** Set display RAM display start line register from 0 - 63. */
#define SSD1306_SETSTARTLINE 0x40
/** Set Display Contrast to one of 256 steps. */
#define SSD1306_SETCONTRAST 0x81
/** Enable or disable charge pump.  Follow with 0X14 enable, 0X10 disable. */
#define SSD1306_CHARGEPUMP 0x8D
/** Set Segment Re-map between data column and the segment driver. */
#define SSD1306_SEGREMAP 0xA0
/** Resume display from GRAM content. */
#define SSD1306_DISPLAYALLON_RESUME 0xA4
/** Force display on regardless of GRAM content. */
#define SSD1306_DISPLAYALLON 0xA5
/** Set Normal Display. */
#define SSD1306_NORMALDISPLAY 0xA6
/** Set Inverse Display. */
#define SSD1306_INVERTDISPLAY 0xA7
/** Set Multiplex Ratio from 16 to 63. */
#define SSD1306_SETMULTIPLEX 0xA8
/** Set Display off. */
#define SSD1306_DISPLAYOFF 0xAE
/** Set Display on. */
#define SSD1306_DISPLAYON 0xAF
/**Set GDDRAM Page Start Address. */
#define SSD1306_SETSTARTPAGE 0XB0
/** Set COM output scan direction normal. */
#define SSD1306_COMSCANINC 0xC0
/** Set COM output scan direction reversed. */
#define SSD1306_COMSCANDEC 0xC8
/** Set Display Offset. */
#define SSD1306_SETDISPLAYOFFSET 0xD3
/** Sets COM signals pin configuration to match the OLED panel layout. */
#define SSD1306_SETCOMPINS 0xDA
/** This command adjusts the VCOMH regulator output. */
#define SSD1306_SETVCOMDETECT 0xDB
/** Set Display Clock Divide Ratio/ Oscillator Frequency. */
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
/** Set Pre-charge Period */
#define SSD1306_SETPRECHARGE 0xD9
/** Deactivate scroll */
#define SSD1306_DEACTIVATE_SCROLL 0x2E
/** No Operation Command. */
#define SSD1306_NOP 0XE3
//------------------------------------------------------------------------------
/** Set Pump voltage value: (30H~33H) 6.4, 7.4, 8.0 (POR), 9.0. */
#define SH1106_SET_PUMP_VOLTAGE 0X30
/** First byte of set charge pump mode */
#define SH1106_SET_PUMP_MODE 0XAD
/** Second byte charge pump on. */
#define SH1106_PUMP_ON 0X8B
/** Second byte charge pump off. */
#define SH1106_PUMP_OFF 0X8A
//------------------------------------------------------------------------------

// this section is based on https://github.com/adafruit/Adafruit_SSD1306

static const uint8_t PROGMEM initSSD1306sq[] = {  // Initialization Sequence
    // Init sequence for Adafruit 128x32 OLED module
/*
    SSD1306_DISPLAYOFF,
    SSD1306_SETDISPLAYCLOCKDIV, 0x80,  // the suggested ratio 0x80
    SSD1306_SETMULTIPLEX, 0x1F,        // ratio 32 (0x3F)
    SSD1306_SETDISPLAYOFFSET, 0x0,     // no offset
    SSD1306_SETSTARTLINE | 0x0,        // line #0
    SSD1306_CHARGEPUMP, 0x14,          // internal vcc
    SSD1306_MEMORYMODE, 0x02,          // page mode (0x00)
    SSD1306_SEGREMAP | 0x1,            // column 127 mapped to SEG0
    SSD1306_COMSCANDEC,                // column scan direction reversed
    SSD1306_SETCOMPINS, 0x02,          // sequential COM pins, disable remap (0x12)
    SSD1306_SETCONTRAST, 0x7F,         // contrast level 127 (0xCF)
    SSD1306_SETPRECHARGE, 0xF1,        // pre-charge period (1, 15)
    SSD1306_SETVCOMDETECT, 0x40,       // vcomh regulator level
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_NORMALDISPLAY,
*/
    SSD1306_DISPLAYOFF,
    SSD1306_SETDISPLAYCLOCKDIV, 0x80,  // the suggested ratio 0x80
    SSD1306_SETMULTIPLEX, 0x1F,        // ratio 32 (0x3F)
    SSD1306_SETDISPLAYOFFSET, 0x0,     // no offset
    SSD1306_SETSTARTLINE | 0x0,        // line #0
    SSD1306_CHARGEPUMP, 0x14,          // internal vcc
    SSD1306_MEMORYMODE, 0x00,          // page mode (0x00)
    SSD1306_SEGREMAP | 0x1,            // column 127 mapped to SEG0
    SSD1306_COMSCANDEC,                // column scan direction reversed
    SSD1306_SETCOMPINS, 0x02,          // sequential COM pins, disable remap (0x12)
    SSD1306_SETCONTRAST, 0xCF,         // contrast level 127 (0xCF)
    SSD1306_SETPRECHARGE, 0xF1,        // pre-charge period (1, 15)
    SSD1306_SETVCOMDETECT, 0x40,       // vcomh regulator level
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_NORMALDISPLAY,

    //SSD1306_DISPLAYON
};

//static uint8_t renderingFrame = 0xB0, drawingFrame = 0x40;

void ssd1306_init(void){
  ssd1306_send_command_start();
  for (uint8_t i = 0; i < sizeof(initSSD1306sq); i++) {
    Wire.write(pgm_read_byte(&initSSD1306sq[i]));
  }
  Wire.endTransmission();
}


void ssd1306_send_command_start(void){
  i2cBegin(0x3C, 0); // address of SSD1306
  Wire.write(SSD1306_COMMAND);
}

void ssd1306_send_command(uint8_t cmd){
  ssd1306_send_command_start();
  Wire.write(cmd);
  Wire.endTransmission();
}

void ssd1306_write_display_start(void){
  i2cBegin(0x3C, 0); // address of SSD1306
  I2C_Write(SSD1306_DATA);
}


void setCol(uint8_t col) {
  ssd1306_send_command(SSD1306_SETLOWCOLUMN | (col & 0XF));
  ssd1306_send_command(SSD1306_SETHIGHCOLUMN | (col >> 4));
}


void setRow(uint8_t row) {
  ssd1306_send_command(SSD1306_SETSTARTPAGE | row);
}

void ssd1306_clear_display(void){
uint8_t i,i1;
  for(i1=0;i1<4;i1++){
    setCol(0);
    setRow(i1);
    ssd1306_write_display_start();
    for(i=0;i<128;i++){
      Wire.write(0);
    }
    Wire.endTransmission();
  }
  setCol(0);
  setRow(0);
}


void ssd1306_bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[]) {
  uint16_t j = 0;
  for (uint8_t y = y0; y < y1; y++) {
    setCol(x0);
    setRow(y);
    ssd1306_write_display_start();
    for (uint8_t x = x0; x < x1; x++) {
      Wire.write(pgm_read_byte(&bitmap[j++]));
    }
    Wire.endTransmission();
  }
  setCol(0);
  setRow(0);
}
