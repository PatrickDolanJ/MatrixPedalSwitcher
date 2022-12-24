#include <common.h>

RotaryButtons rotaryButtons(ROTARY_BUTTONS_ADDRESS);
FootSwitches footSwitches(FOOTSWITCH_ADDRESS);
EasyRotary easyRotaryEncoders(ROTARY_ENCODER_INTERUPT_PIN);
Debugger* debugger; //Computer
Menu menu;

const byte NO_BUTTON_VALUE = 0xFF;
volatile bool rotaryFlag = false;
volatile bool footFlag = false;
bool areTwoButtonsPressed = false;
int previousButtonValue = NO_BUTTON_VALUE;
int previousFootValue = NO_BUTTON_VALUE;
long previousMillis = 0;

void ROTARY_BUTTON_INTERUPT(){
  rotaryFlag = true;
};
void FOOT_INTERUPT(){
  footFlag = true;
}

void ROTARY_INTERUPT(bool isClockwise, int id){
  menu.doRotaryEnoderSpin(isClockwise,id);
};

bool checkLongPress(int duration){
  long interval = duration * 1000;
  unsigned long currenTime = millis();
  long intervalActual = currenTime - previousMillis;
  bool isLongPress = intervalActual >= interval;
  return isLongPress;
}

void handleRotaryButtonPress(){
  int rotaryButtonValue = rotaryButtons.getRotaryID();
  Debugger::log(String(rotaryButtonValue));
  if(rotaryButtonValue!=NO_BUTTON_VALUE && rotaryButtonValue!= previousButtonValue){
    previousMillis = millis();
    }

  if(rotaryButtonValue == NO_BUTTON_VALUE && rotaryButtonValue!=previousButtonValue){
    checkLongPress(LONG_PRESS_INTERVAL_S) ? menu.doLongPress(previousButtonValue) : menu.doButton(previousButtonValue);
  }
  previousButtonValue = rotaryButtonValue;
};

void handleFootButtonPress(){
  int footID = footSwitches.getFootID();
  if(footID != previousFootValue){
    if(footID == -2){
      areTwoButtonsPressed = true;
    }
    if(footID == -1){
      if(areTwoButtonsPressed){
        menu.doDoubleFootPress();
      } else {
        menu.doFoot(previousFootValue);
        }
      }
    }
    previousFootValue = footID;
}


void setup(){
  debugger = &debugger->Instance();
  debugger->setup(115200);
  Debugger::log(DEVICE_NAME + " is booting.");

  menu.setup();

  rotaryButtons.setup(0,ROTARY_INTERUPT_PIN,ROTARY_BUTTON_INTERUPT);
  footSwitches.setup(1,FOOT_INTERUPT_PIN,FOOT_INTERUPT);
  easyRotaryEncoders.startup(*ROTARY_INTERUPT);
  
  Debugger::log(DEVICE_NAME + " ready.");
};

void loop(){
  easyRotaryEncoders.checkInterrupt(); //calls menu.doRotaryEndoderSpin()

  if(rotaryFlag){
    rotaryFlag = false;
    Debugger::log("rotary pressed?");
    handleRotaryButtonPress(); //value is read directly from expander
  }

  if(footFlag){
    footFlag = false;
    handleFootButtonPress(); //value is read directly from expander
  }

  if(previousButtonValue != NO_BUTTON_VALUE && checkLongPress(LONG_PRESS_INTERVAL_S)){
    Debugger::log(String(previousButtonValue));
    Debugger::log(String(NO_BUTTON_VALUE));
    menu.duringLongPress(previousButtonValue);
  }
};