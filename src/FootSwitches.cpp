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

bool FootSwitches::checkInterupt(){ 
   bool interuptOccured = flag;
   flag = false;
   return interuptOccured;
};