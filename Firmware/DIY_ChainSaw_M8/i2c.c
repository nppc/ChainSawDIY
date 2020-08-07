#include "I2C.h"
#include "main.h"


void i2c_init(void) {
	TWSR = 0;
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
}

uint8_t i2c_start() {
	uint8_t twi_status_register;
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
#ifndef DEBUGSIM
	while(!(TWCR & (1<<TWINT)));
#endif
	twi_status_register = TW_STATUS & 0xF8;
	if ((twi_status_register != TW_START) && (twi_status_register != TW_REP_START)) {
		return 1;
	}
	TWDR = I2CADDRESS << 1;
	TWCR = (1<<TWINT) | (1<<TWEN);

#ifndef DEBUGSIM
	while(!(TWCR & (1<<TWINT)));
#endif
	twi_status_register = TW_STATUS & 0xF8;
	if ((twi_status_register != TW_MT_SLA_ACK) && (twi_status_register != TW_MR_SLA_ACK)) {
		return 1;
	}

	return 0;
}

uint8_t i2c_write(uint8_t data) {
	//uint8_t twi_status_register;
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
#ifndef DEBUGSIM
	while(!(TWCR & (1<<TWINT)));
#endif
/*
	twi_status_register = TW_STATUS & 0xF8;
	if (twi_status_register != TW_MT_DATA_ACK) {
		return 1;
		} else {
		return 0;
	}
*/
	return 0;
}

void i2c_stop(void) {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
#ifndef DEBUGSIM
	while(TWCR & (1<<TWSTO));
#endif
}