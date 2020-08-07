#ifndef SSD1306_H_
#define SSD1306_H_

#include "main.h"

//#define SSD1306_COLUMNS 128
//#define SSD1306_PAGES 4

#define SSD1306_COMMAND 0x00
#define SSD1306_DATA 0x40


void ssd1306_send_command_start(void);
void ssd1306_send_command(uint8_t cmd);
void ssd1306_write_display_start(void);


#define SSD1306_SETLOWCOLUMN 0x00	// Set Lower Column Start Address for Page Addressing Mode. 
#define SSD1306_SETHIGHCOLUMN 0x10	// Set Higher Column Start Address for Page Addressing Mode. 
#define SSD1306_MEMORYMODE 0x20		// Set Memory Addressing Mode. 
#define SSD1306_SETSTARTLINE 0x40	// Set display RAM display start line register from 0 - 63. 
#define SSD1306_SETCONTRAST 0x81	// Set Display Contrast to one of 256 steps. 
#define SSD1306_CHARGEPUMP 0x8D	// Enable or disable charge pump.  Follow with 0X14 enable, 0X10 disable. 
#define SSD1306_SEGREMAP 0xA0	// Set Segment Re-map between data column and the segment driver. 
#define SSD1306_DISPLAYALLON_RESUME 0xA4	// Resume display from GRAM content. 
#define SSD1306_DISPLAYALLON 0xA5	// Force display on regardless of GRAM content. 
#define SSD1306_NORMALDISPLAY 0xA6	// Set Normal Display. 
#define SSD1306_INVERTDISPLAY 0xA7	// Set Inverse Display. 
#define SSD1306_SETMULTIPLEX 0xA8	// Set Multiplex Ratio from 16 to 63. 
#define SSD1306_DISPLAYOFF 0xAE	// Set Display off. 
#define SSD1306_DISPLAYON 0xAF	// Set Display on. 
#define SSD1306_SETSTARTPAGE 0XB0	//Set GDDRAM Page Start Address. 
#define SSD1306_COMSCANINC 0xC0	// Set COM output scan direction normal. 
#define SSD1306_COMSCANDEC 0xC8	// Set COM output scan direction reversed. 
#define SSD1306_SETDISPLAYOFFSET 0xD3	// Set Display Offset. 
#define SSD1306_SETCOMPINS 0xDA	// Sets COM signals pin configuration to match the OLED panel layout. 
#define SSD1306_SETVCOMDETECT 0xDB	// This command adjusts the VCOMH regulator output. 
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5	// Set Display Clock Divide Ratio/ Oscillator Frequency. 
#define SSD1306_SETPRECHARGE 0xD9	// Set Pre-charge Period 
#define SSD1306_DEACTIVATE_SCROLL 0x2E	// Deactivate scroll 
#define SSD1306_NOP 0XE3	// No Operation Command. 
//------------------------------------------------------------------------------
#define SH1106_SET_PUMP_VOLTAGE 0X30	// Set Pump voltage value: (30H~33H) 6.4, 7.4, 8.0 (POR), 9.0. 
#define SH1106_SET_PUMP_MODE 0XAD	// First byte of set charge pump mode 
#define SH1106_PUMP_ON 0X8B	// Second byte charge pump on. 
#define SH1106_PUMP_OFF 0X8A	// Second byte charge pump off. 
//------------------------------------------------------------------------------

// this section is based on https://github.com/adafruit/Adafruit_SSD1306

static const uint8_t initSSD1306sq[] = {  // Initialization Sequence
    // Init sequence for Adafruit 128x32 OLED module
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
//------------------------------------------------------------------------------


#endif /* SSD1306_H_ */