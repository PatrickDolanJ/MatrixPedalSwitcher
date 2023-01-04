#include <Arduino.h>
#include <Menu.h>
#include <Debugger.h>
#include <I2Cscanner.h>
#include <DeviceConfig.h>
#include <LoopArray.h>
#include <MatrixLibrary.h>
#include <MemoryFree.h>

Menu::Menu(){};

void Menu::setup()
{
  // May want to switch back to custom animation(w/black background) to ensure this stays coherent
  display.setup(NEXTION_BAUD_RATE);
  display.bootScreen();
  //------------------HardWare Setup----------------
  bank.setCurrentPreset(0);
  digitalPots.setup();

  sendAllHardware(bank.getCurrentPreset());
  //------------------------------------------------
  delay(4000);
  menuState = LOOPS;
  display.setHomeScreen();
  display.highlightMenu(true, menuState);
  updateAllValuesDisplay(bank.getCurrentPreset());
};

void Menu::doButton(int id)
{
  Debugger::log("Button pressed: " + String(id));
  changeMenuState(id);
};

void Menu::doFoot(int id)
{
  Debugger::log("Foot pressed: " + String(id));
  bank.setCurrentPreset(id);
  updateAllValuesDisplay(bank.getCurrentPreset());
  sendAllHardware(bank.getCurrentPreset());
};

void Menu::doDoubleFootPress()
{
  // ENTER BANK MENU
  Debugger::log("Double Foot Button detected.");
};

void Menu::duringLongPress(int id)
{
  if (!returnHighlighted)
  {
    display.highlightReturn(true, id);
    returnHighlighted = true;
  }
};

void Menu::doLongPress(int id)
{
  Debugger::log("Long press finished: " + String(id));
  display.highlightReturn(false, id);
  bool isStereo = !bank.getCurrentReturn(id);
  bank.setCurrentPreset(isStereo);
  returnRelays.sendState(id,bank.getCurrentReturn(id));
  returnHighlighted = false;
};

void Menu::doRotaryEnoderSpin(bool isClockwise, int id)
{
  Debugger::log("Encoder spin: " + String(id));

  switch (menuState)
  {
  case (MenuState::LOOPS):
  {
    if (id != 7)
    {
      int curLoopPosition = incrementLoops(isClockwise, id);
      display.sendLoopPosition(curLoopPosition, id);
      LoopArray la = bank.getCurrentLoopArray();
      sendArrayMatrixData(la.loopArray, la.arraySize);
    }
  }
  break;

  case (MenuState::PAN):
  {
    Debugger::log("From inside doRotary Pan");
    int curPan = incrementPan(isClockwise, id);
    display.sendPan(curPan, id);
    sendOutputVolumes(bank.getCurrentLeftOutputVolume(id), bank.getCurrentRightOutputVolume(id), id);
  }
  break;

  case (MenuState::INPUT_VOLUMES):
  {
    Debugger::log("Spin InputVolumes");
    int curInputVolume = incrementInputVolume(isClockwise, id);
    display.sendInputVolume(curInputVolume, id);
    sendInputVolumes(curInputVolume, id);
  }
  break;

  case (MenuState::OUTPUT_VOLUMES):
  {
    Debugger::log("Spin OutputVolumes");
    int curInputVolume = incrementOutputVolume(isClockwise, id);
    display.sendOutputVolume(curInputVolume, id);
    sendOutputVolumes(bank.getCurrentLeftOutputVolume(id), bank.getCurrentRightOutputVolume(id), id);
  }
  break;

  case (MenuState::PHASE):
  {
    if (id != 7)
    {
      Debugger::log("Spin Phase");
      int curPhase = incrementPhase(isClockwise, id);
      display.sendPhase(curPhase, id);
      Debugger::log(String(curPhase));
    }
  }
  break;
  }
};

void Menu::changeMenuState(int id)
{
  if (id == DOWN_ARROW_ID)
  {
    display.highlightMenu(false, menuState);
    int newMenuState = (menuState + 1) % (NUM_MENU_OPTIONS);
    menuState = static_cast<MenuState>(newMenuState);
    Serial.println("MenuState = " + String(menuState));
    display.highlightMenu(true, menuState);
  }
  else if (id == UP_ARROW_ID)
  {
    display.highlightMenu(false, menuState);
    int newMenuState = (menuState + NUM_MENU_OPTIONS - 1) % (NUM_MENU_OPTIONS);
    menuState = static_cast<MenuState>(newMenuState);
    Serial.println("MenuState = " + String(menuState));
    display.highlightMenu(true, menuState);
  }
};

//-------------------------------------------------------------------------
//------------------------------------helpers------------------------------
void Menu::updateAllValuesDisplay(Preset preset)
{
  display.updateBankPresetInfo(bank.getBankID(), preset.getPresetID());

  for (int i = 0; i < 8; i++)
  {

    display.sendPan(bank.getCurrentPan(i), i);
    display.sendReturn(bank.getCurrentReturn(i), i);
    Debugger::log("Index:" + String(i));
    Debugger::log("Free memory: " + String(freeMemory()));
    display.sendInputVolume(bank.getCurrentInputVolume(i), i);
    display.sendOutputVolume(bank.getCurrentOutputVolume(i), i);
    // display.sendDelayTrail(bank.getCurrentIsDelayTrail(i), i);
    // display.sendDrySend(bank.getSendDry());
  }
  // Split up because unpredictable behavior when all in same scope??
  for (size_t i = 0; i < 7; i++)
  {
    display.sendLoopPosition(bank.getCurrentLoopPosition(i), i);
    display.sendPhase(bank.getCurrentPhase(i), i);
  }
}

int Menu::incrementLoops(bool isClockwise, int id)
{
  int curLoop = bank.getCurrentLoopPosition(id);
  curLoop = isClockwise ? curLoop + 1 : curLoop - 1;
  bank.setCurrentLoopPosition(curLoop, id);
  return bank.getCurrentLoopPosition(id);
};

int Menu::incrementPan(bool isClockwise, int id)
{
  int curPan = bank.getCurrentPan(id);
  curPan = isClockwise ? curPan + PAN_SCROLL_AMOUNT : curPan - PAN_SCROLL_AMOUNT;
  bank.setCurrentPan(curPan, id);
  return bank.getCurrentPan(id);
};

int Menu::incrementInputVolume(bool isClockwise, int id)
{
  int curVolume = bank.getCurrentInputVolume(id);
  curVolume = isClockwise ? curVolume + VOLUME_SCROLL_AMOUNT : curVolume - VOLUME_SCROLL_AMOUNT;
  bank.setCurrentInputVolume(curVolume, id);
  return bank.getCurrentInputVolume(id);
};

int Menu::incrementOutputVolume(bool isClockwise, int id)
{
  int curVolume = bank.getCurrentOutputVolume(id);
  curVolume = isClockwise ? curVolume + VOLUME_SCROLL_AMOUNT : curVolume - VOLUME_SCROLL_AMOUNT;
  bank.setCurrentOutputVolume(curVolume, id);
  return bank.getCurrentOutputVolume(id);
};

int Menu::incrementPhase(bool isClockwise, int id)
{
  // DO
  int curPhase = bank.getCurrentPhase(id);
  curPhase = isClockwise ? (curPhase + 1) % 4 : (curPhase + 3) % 4;
  bank.setCurrentPhase(curPhase, id);
  return bank.getCurrentPhase(id);
};

//----------------------------------------Hardware---------------------------------------
void Menu::sendArrayMatrixData(int loopArray[7], int size)
{
  matrixLeft.writeArray(loopArray, size);
  matrixRight.writeArray(loopArray, size);
};

void Menu::changeFootLeds(int id)
{
  footLEDs.writeAllOff();
  footLEDs.writeLed(true, bank.getCurrentPresetID());
};

void Menu::sendInputVolumes(int value, int id)
{
  digitalPots.sendLeftInputVolume(value, id);
  digitalPots.sendRightInputVolume(value, id);
};

void Menu::sendOutputVolumes(int leftValue, int rightValue, int id)
{
  digitalPots.sendLeftOutputVolume(leftValue, id);
  digitalPots.sendRightOutPutVolume(rightValue, id);
};

void Menu::sendAllHardware(Preset preset)
{
  sendArrayMatrixData(preset.getLoopArray().loopArray, preset.getLoopArray().arraySize);
  changeFootLeds(preset.getPresetID());
  for (size_t i = 0; i < 8; i++)
  {
    sendReturn(preset.getIsStereo(i),i);
    sendInputVolumes(preset.getInputVolume(i), i);
    sendOutputVolumes(preset.getLeftOutputVolume(i), preset.getRightOutputVolume(i), i);
  }
};

void Menu::sendReturn(bool value, int id)
{
  returnRelays.sendState(value,id);
}
