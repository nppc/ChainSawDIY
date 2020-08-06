#include "SSD1306.h"
#include "main.h"
#include "I2C.h"

void ssd1306_init(void){
	ssd1306_send_command_start();
	for (uint8_t i = 0; i < sizeof(initSSD1306sq); i++) {
		i2c_write(initSSD1306sq[i]);
	}
	i2c_stop();
}


void ssd1306_send_command_start(void){
	i2c_start();
	i2c_write(SSD1306_COMMAND);
}

void ssd1306_send_command(uint8_t cmd){
	i2c_start();
	//i2c_write(0x00);
	i2c_write(cmd);
	i2c_stop();

	
	ssd1306_send_command_start();
	i2c_write(cmd);
	i2c_stop();
}

void ssd1306_write_display_start(void){
	i2c_start();
	i2c_write(SSD1306_DATA);
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
			i2c_write(0);
		}
		i2c_stop();
	}
	setCol(0);
	setRow(0);
}


void ssd1306_bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[]) {
	uint16_t j = 0;
	uint8_t x, y;
	for (y = y0; y < (y0+y1); y++) {
		setCol(x0);
		setRow(y);
		ssd1306_write_display_start();
		for (x = x0; x < (x0+x1); x++) {
			i2c_write(bitmap[j++]);
		}
		i2c_stop();
	}
	setCol(0);
	setRow(0);
}

/*
void SSD1306_invert(uint8_t inverted) {
	if (inverted) {
		sendCommand(SSD1306_INVERTDISPLAY);
		} else {
		sendCommand(SSD1306_NORMALDISPLAY);
	}
}
*/

/*
void SSD1306::sendFramebuffer(uint8_t *buffer) {
	sendCommand(SSD1306_COLUMNADDR);
	sendCommand(0x00);
	sendCommand(0x7F);

	sendCommand(SSD1306_PAGEADDR);
	sendCommand(0x00);
	sendCommand(0x07);

	// We have to send the buffer as 16 bytes packets
	// Our buffer is 1024 bytes long, 1024/16 = 64
	// We have to send 64 packets
	for (uint8_t packet = 0; packet < 64; packet++) {
		i2c.start();
		i2c.write(0x40);
		for (uint8_t packet_byte = 0; packet_byte < 16; ++packet_byte) {
			i2c.write(buffer[packet*16+packet_byte]);
		}
		i2c.stop();
	}	
}
*/
