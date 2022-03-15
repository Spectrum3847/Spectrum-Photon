#ifndef COMMANDS_H
#define COMMANDS_H
#include <CmdMessenger.h>  // CmdMessenger
#include "LEDstrip.h"
#include "Spectrum-Photon.h"


// This is the list of recognized commands. These can be commands that can either be sent or received. 
// In order to receive, attach a callback function to these events
enum
{
  // Commands
  kAcknowledge         , // 0 Command to acknowledge that cmd was received
  kError               , // 1 Command to report errors
  kSetStrip            , // 2 Command to set a strip
  kSetNumLEDSstrip     , // 3 Command to set num of leds on a strip
};

void attachCommandCallbacks();
void OnUnknownCommand();
void OnArduinoReady();
void OnSetStrip();
void OnSetNumLEDStrip();

#endif