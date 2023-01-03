#include <common.h>

RotaryButtons rotaryButtons(ROTARY_BUTTONS_ADDRESS);
FootSwitches footSwitches(FOOTSWITCH_ADDRESS);
EasyRotary easyRotaryEncoders(ROTARY_ENCODER_INTERUPT_PIN);
Debugger *debugger; // Computer
Menu menu;          //

const int NO_BUTTON_VALUE = 0;
const int DOUBLE_BUTTON_PRESS_VALUE = -2;

volatile bool rotaryFlag = false;
volatile bool footFlag = false;
bool areTwoButtonsPressed = false;

int previousButtonValue = NO_BUTTON_VALUE;
int previousFootValue = NO_BUTTON_VALUE;
long previousMillis = 0;

void ROTARY_BUTTON_INTERUPT() { rotaryFlag = true; };
void FOOT_INTERUPT() { footFlag = true; };
int idToArray(int id) { return id - 1; };

void ROTARY_INTERUPT(bool isClockwise, int id)
{
  int arrayId = idToArray(id);
  menu.doRotaryEnoderSpin(isClockwise, arrayId);
};

bool checkLongPress(int duration)
{
  long interval = duration * 1000;
  unsigned long currenTime = millis();
  long intervalActual = currenTime - previousMillis;
  bool isLongPress = intervalActual >= interval;
  return isLongPress;
}

void handleRotaryButtonPress()
{
  int rotaryButtonValue = rotaryButtons.getRotaryID();
  if (rotaryButtonValue != NO_BUTTON_VALUE && rotaryButtonValue != previousButtonValue)
  {
    previousMillis = millis();
  }

  if (rotaryButtonValue == NO_BUTTON_VALUE && rotaryButtonValue != previousButtonValue)
  {
    int arrayId = idToArray(previousButtonValue);
    checkLongPress(LONG_PRESS_INTERVAL_S) ? menu.doLongPress(arrayId) : menu.doButton(arrayId);
  }
  previousButtonValue = rotaryButtonValue;
};

void handleFootButtonPress()
{
  int footID = footSwitches.getFootID();
  if (footID != previousFootValue)
  {
    if (footID == DOUBLE_BUTTON_PRESS_VALUE)
    {
      areTwoButtonsPressed = true;
    }
    if (footID == NO_BUTTON_VALUE)
    {
      if (areTwoButtonsPressed)
      {
        areTwoButtonsPressed = false;
        menu.doDoubleFootPress();
      }
      else
      {
        int arrayId = idToArray(previousFootValue);
        menu.doFoot(arrayId);
      }
    }
    previousFootValue = footID;
  }
}

//--------------------------------------MAIN------------------------------------------
//------------------------------------------------------------------------------------

void setup()
{
  debugger = &debugger->Instance();
  debugger->setup(115200);
  Debugger::log(DEVICE_NAME + " is booting.");

  SPI.begin();
  menu.setup();

  rotaryButtons.setup(0, ROTARY_INTERUPT_PIN, ROTARY_BUTTON_INTERUPT);
  footSwitches.setup(1, FOOT_INTERUPT_PIN, FOOT_INTERUPT);
  easyRotaryEncoders.startup(*ROTARY_INTERUPT);

  Debugger::log(DEVICE_NAME + " ready.");
};

void loop()
{
  easyRotaryEncoders.checkInterrupt(); // calls menu.doRotaryEndoderSpin()

  if (rotaryFlag)
  {
    rotaryFlag = false;
    handleRotaryButtonPress(); // value is read directly from expander
  }

  if (footFlag)
  {
    footFlag = false;
    handleFootButtonPress(); // value is read directly from expander
  }

  if (previousButtonValue != NO_BUTTON_VALUE && checkLongPress(LONG_PRESS_INTERVAL_S))
  {
    menu.duringLongPress(previousButtonValue);
  }

  
};