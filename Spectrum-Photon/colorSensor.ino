#include <i2c_driver_wire.h>
#include <Adafruit_NeoPixel.h>

//These values are the readings of the whitepoint of the led. Take the back of vinyl sticker and put it againts face of sensor
#define LED_RED 7614.0f
#define LED_GREEN 14000.0f
#define LED_BLUE 6500.0f

//Calculate the balancing factors
#define BAL_RED (LED_GREEN/LED_RED)
#define BAL_GREEN (LED_GREEN/LED_GREEN) 
#define BAL_BLUE (LED_GREEN/LED_BLUE)

#define I2C_ADDR 0x52
#define PIXELNUM 8

uint8_t readBuff0[9];
uint8_t readBuff1[9];
uint16_t ir=0;
uint16_t red=0;
uint16_t green=0;
uint16_t blue=0;
uint16_t ir1=0;
uint16_t red1=0;
uint16_t green1=0;
uint16_t blue1=0;

void colorSensorSetup() {
  Wire.begin();
  Wire1.begin();
  Serial.begin(115200);
  i2cWrite0(0x00,0b0110);  //enable light sensor and activate rgb mode
  i2cWrite0(0x04,0b01000000); //set to 16 bit resolution for 25ms response time and set measurement rate to 25ms
  i2cWrite1(0x00,0b0110);  //enable light sensor and activate rgb mode
  i2cWrite1(0x04,0b01000000); //set to 16 bit resolution for 25ms response time and set measurement rate to 25ms
}

void colorSensorLoop() {
  i2cRead0(0x0A,readBuff0,12);

  ir=(readBuff0[1]<<8)|readBuff0[0];
  green=(readBuff0[4]<<8)|readBuff0[3];
  blue=(readBuff0[7]<<8)|readBuff0[6];
  red=(readBuff0[10]<<8)|readBuff0[9];

  red*=BAL_RED;
  green*=BAL_GREEN;
  blue*=BAL_BLUE;

  Serial.print("Sensor 1:");
  Serial.print(ir);
  Serial.print(" ");
  Serial.print(red);
  Serial.print(" ");
  Serial.print(green);
  Serial.print(" ");
  Serial.print(blue);
  Serial.println(" ");

  i2cRead1(0x0A,readBuff1,12);

  ir1=(readBuff1[1]<<8)|readBuff1[0];
  green1=(readBuff1[4]<<8)|readBuff1[3];
  blue1=(readBuff1[7]<<8)|readBuff1[6];
  red1=(readBuff1[10]<<8)|readBuff1[9];

  red1*=BAL_RED;
  green1*=BAL_GREEN;
  blue1*=BAL_BLUE;

  Serial.print("Sensor 2:");
  Serial.print(ir1);
  Serial.print(" ");
  Serial.print(red1);
  Serial.print(" ");
  Serial.print(green1);
  Serial.print(" ");
  Serial.print(blue1);
  Serial.println(" ");

  delay(25);
}


void i2cWrite0(uint8_t reg, uint8_t val){
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

void i2cRead0(uint8_t reg,uint8_t *val,uint16_t len){
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDR, len);
    for(uint8_t i=0;i<len;i++){
      val[i]=Wire.read();
    }
}

void i2cWrite1(uint8_t reg, uint8_t val){
    Wire1.beginTransmission(I2C_ADDR);
    Wire1.write(reg);
    Wire1.write(val);
    Wire1.endTransmission();
}

void i2cRead1(uint8_t reg,uint8_t *val,uint16_t len){
    Wire1.beginTransmission(I2C_ADDR);
    Wire1.write(reg);
    Wire1.endTransmission();
    Wire1.requestFrom(I2C_ADDR, len);
    for(uint8_t i=0;i<len;i++){
      val[i]=Wire1.read();
    }
}
