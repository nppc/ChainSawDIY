#ifndef I2C_H_
#define I2C_H_

#include "main.h"
#include <util/twi.h>

#define SCL_CLOCK  100000L
#define I2CADDRESS 0x3C

    void i2c_init(void);
    uint8_t i2c_start();
    uint8_t i2c_write(uint8_t data);
    void i2c_stop(void);

#endif /* I2C_H_ */