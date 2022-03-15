#include <CmdMessenger.h>  // CmdMessenger
#include "commands.h"
#include "colorSensor.h"

/*
 * Red (0..) "HUE_RED"
Orange (32..) "HUE_ORANGE"
Yellow (64..) "HUE_YELLOW"
Green (96..) "HUE_GREEN"
Aqua (128..) "HUE_AQUA"
Blue (160..) "HUE_BLUE"
Purple (192..) "HUE_PURPLE"
Pink(224..) "HUE_PINK"
// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5
2  LED Strip #1
14  LED Strip #2
7 LED Strip #3
8 LED Strip #4
6 LED Strip #5
20  LED Strip #6
21  LED Strip #7
5 LED Strip #8
*/

#define STRIP_1_PIN 2
#define STRIP_2_PIN 14
#define STRIP_3_PIN 7
#define STRIP_4_PIN 8
#define STRIP_5_PIN 6
#define STRIP_6_PIN 20
#define STRIP_7_PIN 21
#define STRIP_8_PIN 5

#define MAX_LEDS_PER_STRIP 60
#define LED_UPDATE_PERIOD 10

extern LEDstrip strip1;
extern LEDstrip strip2;
extern LEDstrip strip3;
extern LEDstrip strip4;
extern LEDstrip strip5;
extern LEDstrip strip6;
extern LEDstrip strip7;
extern LEDstrip strip8;

// Attach a new CmdMessenger object to the default Serial port
extern CmdMessenger cmdMessenger;