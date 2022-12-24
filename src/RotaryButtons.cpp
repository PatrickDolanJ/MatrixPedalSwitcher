#include <RotaryButtons.h>
#include <Arduino.h>
#include <pcf8574.h>
#include <DeviceConfig.h>
#include <Debugger.h>

PCF8574 rotaryExpander(0xFF);

RotaryButtons::RotaryButtons(byte address){
  this->address = address;
};

int RotaryButtons::rotaryHexToID(byte hexVal){
    int id = 8;
    switch (hexVal){
      case(0xFF):
        id = 0;
        break;
      case (0xFE):
        id = 1;
        break;
      case (0xFD):
        id = 2;
        break;
      case (0xFB):
        id = 3;
        break;
      case (0xF7):
        id = 4;
        break;
      case (0xEF):
        id = 5;
        break;
      case (0xDF):
        id = 6;
        break;
      case (0xBF):
        id = 7;
        break;
    }
    return id;
  };

void RotaryButtons::setup(int pin, int interuptPin,void (*userFunc)(void)){
    rotaryExpander.setAddress(address);
    pinMode(rotaryExpander, pin, INPUT_PULLUP);
    pinMode(interuptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interuptPin),*userFunc, FALLING);
};

int RotaryButtons::getRotaryID(){
    return rotaryHexToID(rotaryExpander.read());
};

  void RotaryButtons::setPreviousRotaryButtonValue(int buttonValue){
    setPreviousRotaryButtonValue(rotaryHexToID(buttonValue));
  };

  void RotaryButtons::setLongPressPreviousMillis(long time){
    longPressPreviousMillis = time;
  };




