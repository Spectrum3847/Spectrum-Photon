#include "Spectrum-Photon.h"

CRGB leds1[MAX_LEDS_PER_STRIP];
CRGB leds2[MAX_LEDS_PER_STRIP];
CRGB leds3[MAX_LEDS_PER_STRIP];
CRGB leds4[MAX_LEDS_PER_STRIP];
CRGB leds5[MAX_LEDS_PER_STRIP];
CRGB leds6[MAX_LEDS_PER_STRIP];
CRGB leds7[MAX_LEDS_PER_STRIP];
CRGB leds8[MAX_LEDS_PER_STRIP];

LEDstrip strip1(MAX_LEDS_PER_STRIP);
LEDstrip strip2(MAX_LEDS_PER_STRIP);
LEDstrip strip3(MAX_LEDS_PER_STRIP);
LEDstrip strip4(MAX_LEDS_PER_STRIP);
LEDstrip strip5(MAX_LEDS_PER_STRIP);
LEDstrip strip6(MAX_LEDS_PER_STRIP);
LEDstrip strip7(MAX_LEDS_PER_STRIP);
LEDstrip strip8(MAX_LEDS_PER_STRIP);

CmdMessenger cmdMessenger = CmdMessenger(Serial);

///////////////////////////////////////////////////////////////////////////
/// REST OF THE COMMANDS ARE DEFINED IN THE commands TAB //////////////////
///////////////////////////////////////////////////////////////////////////

//Variables for cycling the LEDs
unsigned long time;
unsigned long oldTime;
unsigned long counter = 0;

//Runs once at startup
void setup() {
  //Setup your LED strips here, up to 8 can be used, maybe more.
  LEDS.addLeds<WS2812,STRIP_1_PIN,GRB>(leds1,MAX_LEDS_PER_STRIP);
  LEDS.addLeds<WS2812,STRIP_2_PIN,GRB>(leds2,MAX_LEDS_PER_STRIP);
  LEDS.addLeds<WS2812,STRIP_3_PIN,GRB>(leds3,MAX_LEDS_PER_STRIP);
  LEDS.addLeds<WS2812,STRIP_4_PIN,GRB>(leds4,MAX_LEDS_PER_STRIP);
  LEDS.addLeds<WS2812,STRIP_5_PIN,GRB>(leds5,MAX_LEDS_PER_STRIP);
  LEDS.addLeds<WS2812,STRIP_6_PIN,GRB>(leds6,MAX_LEDS_PER_STRIP);
  LEDS.addLeds<WS2812,STRIP_7_PIN,GRB>(leds7,MAX_LEDS_PER_STRIP);
  LEDS.addLeds<WS2812,STRIP_8_PIN,GRB>(leds8,MAX_LEDS_PER_STRIP);
  LEDS.setBrightness(255);

  Serial.begin(115200);
  // Adds newline to every command
  cmdMessenger.printLfCr();  
  
  // Attach my application's user-defined callback methods
  attachCommandCallbacks();

  // Send the status to the PC that says the Arduino has booted
  cmdMessenger.sendCmd(kAcknowledge,"Arduino has started!");

  time = millis();
  oldTime = time;
  colorSensorSetup();
}

void loop() {
  // Process incoming serial data, and perform callbacks
  cmdMessenger.feedinSerialData();
  
  time = millis();
  if(time - oldTime > LED_UPDATE_PERIOD){ 
    oldTime = time;
    strip1.Update(counter, leds1);
    strip2.Update(counter, leds2);
    strip3.Update(counter, leds3);
    strip4.Update(counter, leds4);
    strip5.Update(counter, leds5);
    strip6.Update(counter, leds6);
    strip7.Update(counter, leds7);
    strip8.Update(counter, leds8);
    FastLED.show(); 
    counter++;
  }

  //Handle the crazy rollover case
  if (time > 4200967295){
    time = 0;
    oldTime = 0;
    counter = 0;
  }

  colorSensorLoop();
}


