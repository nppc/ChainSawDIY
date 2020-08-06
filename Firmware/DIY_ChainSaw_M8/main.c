#include <avr/io.h>
#include "main.h"
#include "SSD1306.h"
#include "i2c.h"

int main(void)
{
	i2c_init();
	ssd1306_init();

	ssd1306_clear_display();
	ssd1306_send_command(0xAF); //SSD1306_DISPLAYON
	setCol(0);
	setRow(0);

	ssd1306_bitmap(128-32,0,32,4,stateDANGER);

    while (1); 
}

