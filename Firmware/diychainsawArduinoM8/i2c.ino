void I2C_Write(uint8_t v_i2cData_u8){
  Wire.write(v_i2cData_u8);
}

bool i2cBegin(uint8_t addr, bool bRead){
  //addr <<= 1;
  Wire.beginTransmission(addr);
}

void I2C_Stop(void){
  Wire.endTransmission();
}
