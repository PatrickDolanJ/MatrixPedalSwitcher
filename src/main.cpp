#include <Arduino.h>
#include <common.h>

volatile bool rotaryFlag = false;
volatile bool footFlag = false;

RotaryButtons rotaryButtons(ROTARY_BUTTONS_ADDRESS);
void ROTARY_INTERUPT(){
  rotaryFlag = true;
};

void FOOT_INTERUPT(){
  footFlag = true;
}


Display display; /// Nextion
Debugger* debugger;

void setup(){
  debugger = &debugger->Instance();
  debugger->setup(115200);
  Debugger::log(DEVICE_NAME + " is booting.");

  display.setup(NEXTION_BAUD_RATE);
  rotaryButtons.setup(0,ROTARY_ENCODER_INTERUPT_PIN,*ROTARY_INTERUPT);
  

  Debugger::log(DEVICE_NAME + " ready.");
};

void loop(){
  if(rotaryFlag){
    //do buttons
  }

  if(footFlag){
    //doFoot
  }


};