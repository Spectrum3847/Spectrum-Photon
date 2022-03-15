#include <i2c_driver_wire.h>
#include <Adafruit_NeoPixel.h>

void i2cWrite0(uint8_t reg, uint8_t val);
void i2cRead0(uint8_t reg,uint8_t *val,uint16_t len);
void i2cWrite1(uint8_t reg, uint8_t val);
void i2cRead1(uint8_t reg,uint8_t *val,uint16_t len);
void colorSensorSetup();
void colorSensorLoop();