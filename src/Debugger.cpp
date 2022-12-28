#include <Arduino.h>
#include <Debugger.h>
#include <I2CScanner.h>

Debugger* Debugger::instance;
Debugger::Debugger(){
  hasSetup = false;
};

Debugger& Debugger::Instance(){
    if (instance == NULL){
      instance = new Debugger();
    }
    return *instance;
}

void Debugger::setup(unsigned long baudRate){
  if(!hasSetup){
    this->BAUD_RATE = baudRate;
    Serial.begin(BAUD_RATE);
    while(!Serial){};
    hasSetup = true;
  } else {
    Debugger::log("Debugger instance already exists.");
  }
}

void Debugger::log(String message){
  Serial.println(message);
}

void Debugger::log(int number, int base){
  Serial.println(number,HEX);
};

