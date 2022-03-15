#ifndef LEDstip_H
#define LEDstip_H
#include<FastLED.h>

#define DEFAULT_COLOR 0
#define ERROR_COLOR 0
#define DEFAULT_FADE 150
#define DEFAULT_RATE 2

class LEDstrip
{
  boolean state = false;
  boolean state2 = false;
  int numberLEDs;
  int kPattern;
  int kColor1;
  int kColor2;
  int kFade;
  int kRate;
   
  public:
  LEDstrip(int n);
  void setNumLEDS(int n);
  void setLEDPattern(int p);
  int getLEDPattern();
  void setColor1(int c);
  int getColor1();
  void setColor2(int c);
  void setFade(int f);
  void setLEDRate(int r);

  void ResetValues();
  void Update(int counter, CRGB l[]);

  //counter is an increment 
  void Update( int counter, CRGB l[], int pattern, 
  int color1, int color2, int rate, 
  int fade);
};

#endif