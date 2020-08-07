#include "oled.h"
#include "main.h"
#include "SSD1306.h"
#include "i2c.h"

void oled_init(void){
	ssd1306_send_command_start();
	for (uint8_t i = 0; i < sizeof(initSSD1306sq); i++) {
		i2c_write(initSSD1306sq[i]);
	}
	i2c_stop();
}

void oled_enable_display(void){
	ssd1306_send_command(0xAF); //SSD1306_DISPLAYON
}

void oled_setCol(uint8_t col) {
	ssd1306_send_command(SSD1306_SETLOWCOLUMN | (col & 0XF));
	ssd1306_send_command(SSD1306_SETHIGHCOLUMN | (col >> 4));
}


void oled_setRow(uint8_t row) {
	ssd1306_send_command(SSD1306_SETSTARTPAGE | row);
}

void oled_clear_display(void){
	uint8_t i,i1;
	for(i1=0;i1<4;i1++){
		oled_setCol(0);
		oled_setRow(i1);
		ssd1306_write_display_start();
		for(i=0;i<128;i++){
			i2c_write(0);
		}
		i2c_stop();
	}
	oled_setCol(0);
	oled_setRow(0);
}


void oled_bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[]) {
	uint16_t j = 0;
	uint8_t x, y;
	for (y = y0; y < (y0+y1); y++) {
		oled_setCol(x0);
		oled_setRow(y);
		ssd1306_write_display_start();
		for (x = x0; x < (x0+x1); x++) {
			i2c_write(bitmap[j++]);
		}
		i2c_stop();
	}
	oled_setCol(0);
	oled_setRow(0);
}

void oled_clear(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	uint8_t x,y;
 	for (y = y0; y < y0 + y1; y++) {
		oled_setCol(x0);
		oled_setRow(y);
		ssd1306_write_display_start();
		for(x=0;x<x0+x1;x++){
			i2c_write(0);
		}
		i2c_stop();
	}
}


void oled_draw_Bat(uint8_t val){
	if(val==0){oled_bitmap(0,0,13,4,oled_batBot0);} else {oled_bitmap(0,0,13,4,oled_batBot1);}
	for(uint8_t ix=2;ix<=6;ix++){if(ix<=val){oled_bitmap(13+(ix-2)*10,0,10,4,oled_bat1);}else{oled_bitmap(13+(ix-2)*10,0,10,4,oled_bat0);}}
	oled_bitmap(13+50,0,7,4,oled_batEnd);
}



/*
void oled_invert(uint8_t inverted) {
	if (inverted) {
		sendCommand(SSD1306_INVERTDISPLAY);
		} else {
		sendCommand(SSD1306_NORMALDISPLAY);
	}
}
*/
