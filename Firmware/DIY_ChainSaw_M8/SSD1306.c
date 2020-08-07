#include "SSD1306.h"
#include "main.h"
#include "I2C.h"


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



