#include "colorSensor.h"

//These values are the readings of the whitepoint of the led. Take the back of vinyl sticker and put it againts face of sensor
#define LED_RED1 7480.0f // 7480,6993,13659,144,255
#define LED_BLUE1 6993.0f
#define LED_GREEN1 13659.0f

#define LED_RED2 8166.0f // 8166,6927,15037,123,255,
#define LED_BLUE2 6927.0f
#define LED_GREEN2 15037.0f

//Calculate the balancing factors
#define BAL_RED1 (LED_GREEN1/LED_RED1)
#define BAL_GREEN1 (LED_GREEN1/LED_GREEN1) 
#define BAL_BLUE1 (LED_GREEN1/LED_BLUE1)

#define BAL_RED2 (LED_GREEN2/LED_RED2)
#define BAL_GREEN2 (LED_GREEN2/LED_GREEN2) 
#define BAL_BLUE2 (LED_GREEN2/LED_BLUE2)

#define I2C_ADDR 0x52
#define PIXELNUM 8

enum class GainFactor
{
    k1x = 0,
    k3x = 1,
    k6x = 2,
    k9x = 3,
    k18x = 4
};

enum class LEDPulseFrequency
{
    k60kHz = 0x18,
    k70kHz = 0x40,
    k80kHz = 0x28,
    k90kHz = 0x30,
    k100kHz = 0x38,
};

enum class LEDCurrent
{
    kPulse2mA = 0,
    kPulse5mA = 1,
    kPulse10mA = 2,
    kPulse25mA = 3,
    kPulse50mA = 4,
    kPulse75mA = 5,
    kPulse100mA = 6,
    kPulse125mA = 7,
};

enum class ProximityResolution
{
    k8bit = 0x00,
    k9bit = 0x08,
    k10bit = 0x10,
    k11bit = 0x18,
};

enum class ProximityMeasurementRate
{
    k6ms = 1,
    k12ms = 2,
    k25ms = 3,
    k50ms = 4,
    k100ms = 5,
    k200ms = 6,
    k400ms = 7,
};

enum class ColorResolution
{
    k20bit = 0x00,
    k19bit = 0x10,
    k18bit = 0x20,
    k17bit = 0x30,
    k16bit = 0x40,
    k13bit = 0x50,
};

enum class ColorMeasurementRate
{
    k25ms = 0,
    k50ms = 1,
    k100ms = 2,
    k200ms = 3,
    k500ms = 4,
    k1000ms = 5,
    k2000ms = 7,
};

enum class Register
{
    kMainCtrl = 0x00,
    kProximitySensorLED = 0x01,
    kProximitySensorPulses = 0x02,
    kProximitySensorRate = 0x03,
    kLightSensorMeasurementRate = 0x04,
    kLightSensorGain = 0x05,
    kPartID = 0x06,
    kMainStatus = 0x07,
    kProximityData = 0x08,
    kDataInfrared = 0x0A,
    kDataGreen = 0x0D,
    kDataBlue = 0x10,
    kDataRed = 0x13
};

enum class MainCtrlFields
{
    kProximitySensorEnable = 0x01,
    kLightSensorEnable = 0x02,
    kRGBMode = 0x04
};

static constexpr int kAddress = 0x52;
static constexpr int kExpectedPartID = 0xC2;

uint8_t readBuff0[15];
uint16_t prox = 0;
uint16_t ir=0;
uint16_t red=0;
uint16_t green=0;
uint16_t blue=0;

uint16_t prox1 = 0;
uint16_t ir1=0;
uint16_t red1=0;
uint16_t green1=0;
uint16_t blue1=0;

void colorSensorSetup() {
  Wire.begin();
  Wire1.begin();
  //Serial.begin(115200);
  i2cWrite0(0x00,0b0111);  //enable light sensor and activate rgb mode and proximity sensor
  i2cWrite0(0x04,0b01000000); //set to 16 bit resolution for 25ms response time and set measurement rate to 25ms
  i2cWrite1(0x00,0b0111);  //enable light sensor and activate rgb mode and proximity sensor
  i2cWrite1(0x04,0b01000000); //set to 16 bit resolution for 25ms response time and set measurement rate to 25ms
}

void colorSensorLoop() {
  boolean sensor1 = i2cRead0(0x07,readBuff0,15);

  prox=((readBuff0[1] & 0xFF) | ((readBuff0[2] & 0xFF) << 8)) & 0x7FF;
  ir=((readBuff0[3] & 0xFF) | ((readBuff0[4] & 0xFF) << 8) | ((readBuff0[5] & 0xFF) << 16)) & 0x03FFFF;
  green=((readBuff0[6] & 0xFF) | ((readBuff0[7] & 0xFF) << 8) | ((readBuff0[8] & 0xFF) << 16)) & 0x03FFFF;
  blue=((readBuff0[9] & 0xFF) | ((readBuff0[10] & 0xFF) << 8) | ((readBuff0[11] & 0xFF) << 16)) & 0x03FFFF;
  red=((readBuff0[12] & 0xFF) | ((readBuff0[13] & 0xFF) << 8) | ((readBuff0[14] & 0xFF) << 16)) & 0x03FFFF;

  red*=BAL_RED1;
  green*=BAL_GREEN1;
  blue*=BAL_BLUE1;

  boolean sensor2 = i2cRead1(0x07,readBuff0,15);
  prox1=((readBuff0[1] & 0xFF) | ((readBuff0[2] & 0xFF) << 8)) & 0x7FF;
  ir1=((readBuff0[3] & 0xFF) | ((readBuff0[4] & 0xFF) << 8) | ((readBuff0[5] & 0xFF) << 16)) & 0x03FFFF;
  green1=((readBuff0[6] & 0xFF) | ((readBuff0[7] & 0xFF) << 8) | ((readBuff0[8] & 0xFF) << 16)) & 0x03FFFF;
  blue1=((readBuff0[9] & 0xFF) | ((readBuff0[10] & 0xFF) << 8) | ((readBuff0[11] & 0xFF) << 16)) & 0x03FFFF;
  red1=((readBuff0[12] & 0xFF) | ((readBuff0[13] & 0xFF) << 8) | ((readBuff0[14] & 0xFF) << 16)) & 0x03FFFF;

  red1*=BAL_RED1;
  green1*=BAL_GREEN1;
  blue1*=BAL_BLUE1;

  Serial.print(sensor1);
  Serial.print(",");
  Serial.print(sensor2);
  Serial.print(",");
  Serial.print(red);
  Serial.print(",");
  Serial.print(blue);
  Serial.print(","); 
  Serial.print(green);
  Serial.print(","); 
  Serial.print(ir);
  Serial.print(",");
  Serial.print(prox);
  Serial.print(",");
  Serial.print(red1);
  Serial.print(",");
  Serial.print(blue1);
  Serial.print(","); 
  Serial.print(green1);
  Serial.print(","); 
  Serial.print(ir1);
  Serial.print(",");
  Serial.print(prox1);
  Serial.println(",");

  delay(25);
}

//Use "Wire" for the first sensor and "Wire1" for the second sensor
void i2cWrite0(uint8_t reg, uint8_t val){
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

boolean i2cRead0(uint8_t reg,uint8_t *val,uint16_t len){
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    int result =  Wire.requestFrom(I2C_ADDR, len);
    if (result < 1){
      return false;
    }
    for(uint8_t i=0;i<len;i++){
      val[i]=Wire.read();
    }
    return true;
}

void i2cWrite1(uint8_t reg, uint8_t val){
    Wire1.beginTransmission(I2C_ADDR);
    Wire1.write(reg);
    Wire1.write(val);
    Wire1.endTransmission();
}

boolean i2cRead1(uint8_t reg,uint8_t *val,uint16_t len){
    Wire1.beginTransmission(I2C_ADDR);
    int result = Wire1.write(reg);
    if (result != 1){
      return false;
    }
    Wire1.endTransmission();
    Wire1.requestFrom(I2C_ADDR, len);
    for(uint8_t i=0;i<len;i++){
      val[i]=Wire1.read();
    }
    return true;
}


