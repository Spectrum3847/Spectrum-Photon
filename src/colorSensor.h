#include <i2c_driver_wire.h>

void i2cWrite0(uint8_t reg, uint8_t val);
boolean i2cRead0(uint8_t reg,uint8_t *val,uint16_t len);
void i2cWrite1(uint8_t reg, uint8_t val);
boolean i2cRead1(uint8_t reg,uint8_t *val,uint16_t len);
void colorSensorSetup();
void colorSensorLoop();