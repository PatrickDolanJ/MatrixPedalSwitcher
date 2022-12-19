#include <RotaryButtons.h>
#include <Arduino.h>
#include <pcf8574.h>
#include <DeviceConfig.h>

PCF8574 rotaryExpander(0xFF);

RotaryButtons::RotaryButtons(byte address){
    rotaryExpander = PCF8574(address);
};

void RotaryButtons::setup(int pin, int interuptPin,void (*userFunc)(void)){
    pinMode(rotaryExpander, pin, INPUT_PULLUP);
    pinMode(interuptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interuptPin),userFunc, FALLING);
};

bool RotaryButtons::checkInterupt(){ 
   bool interuptOccured = flag;
   flag = false;
   return interuptOccured;
};