#include <common.h>

RotaryButtons rotaryButtons(ROTARY_BUTTONS_ADDRESS);
FootSwitches footSwitches(FOOTSWITCH_ADDRESS);
EasyRotary easyRotaryEncoders(ROTARY_ENCODER_INTERUPT_PIN);
Debugger* debugger; //Computer
Menu menu;

//----------------Interupts--------------------
//cannot use member functions here so is included in main
volatile bool rotaryFlag = false;
volatile bool footFlag = false;

void ROTARY_BUTTON_INTERUPT(){
  rotaryFlag = true;
};
void FOOT_INTERUPT(){
  footFlag = true;
}

void ROTARY_INTERUPT(bool clockwise, int id){
};
//----------------------------------------------

void setup(){
  debugger = &debugger->Instance();
  debugger->setup(115200);
  Debugger::log(DEVICE_NAME + " is booting.");

  rotaryButtons.setup(0,ROTARY_ENCODER_INTERUPT_PIN,*ROTARY_BUTTON_INTERUPT);
  footSwitches.setup(1,FOOT_INTERUPT_PIN,*FOOT_INTERUPT);
  easyRotaryEncoders.startup(*ROTARY_INTERUPT);
  

  Debugger::log(DEVICE_NAME + " ready.");
};

void loop(){
  easyRotaryEncoders.checkInterrupt(); //

  if(rotaryFlag){
  }

  if(footFlag){
    //doFoot
  }
};