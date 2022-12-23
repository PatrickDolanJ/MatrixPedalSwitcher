#include <FootSwitches.h>
#include <Arduino.h>
#include <pcf8574.h>
#include <DeviceConfig.h>

PCF8574 footExpander(0xFF);

FootSwitches::FootSwitches(byte address){
    footExpander = PCF8574(address);
};

void FootSwitches::setup(int pin, int interuptPin,void (*userFunc)(void)){
    pinMode(footExpander, pin, INPUT_PULLUP);
    pinMode(interuptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interuptPin),userFunc, FALLING);
};

int FootSwitches::getFootID(){
    return footHextoID(footExpander.read());
}


int FootSwitches::footHextoID(byte hex){
  // Anything that isnt FF and isnt a single button returns -2 to indicate that multiple buttons are pressed
  String currentBank = "Two Pressed";
  int footID = -2;
  switch(hex)
  {
    case(0xfe):
      footID = 0;
      break;
    case(0xfd):
      footID = 1;
      break;
    case(0xfb):
      footID = 2;
      break;
    case(0xf7):
      footID = 3;
      break;
    case(0xef):
      footID = 4;
      break;
    case(0Xff):
      footID = -1;
      break;
  }
  return footID;
}