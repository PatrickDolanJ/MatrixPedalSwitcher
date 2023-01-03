#include <Arduino.h>
#include <Menu.h>
#include <Debugger.h>
#include <I2Cscanner.h>
#include <SPI.h>
#include <DeviceConfig.h>
#include <LoopArray.h>
#include <MatrixLibrary.h>

Menu::Menu(){};

void Menu::setup()
{
  // May want to switch back to custom animation(w/black background) to ensure this stays coherent
  display.setup(NEXTION_BAUD_RATE);
  display.bootScreen();
  delay(4000);
  menuState = LOOPS;
  SPI.begin();
  display.setHomeScreen();
  display.highlightMenu(true, menuState);
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
  int bankId = bank.getBankID();
  PresetID curPresetId = bank.getCurrentPresetID();
  display.updateBankPresetInfo(bankId, curPresetId);
};

void Menu::doDoubleFootPress()
{
  // DO
  Debugger::log("Double Foot Button detected.");
}

void Menu::duringLongPress(int id){
    // DO
};

void Menu::doLongPress(int id)
{
  Debugger::log("Long press finished: " + String(id));
};

void Menu::doRotaryEnoderSpin(bool isClockwise, int id)
{
  Debugger::log("Encoder spin: " + String(id));

  switch (menuState)
  {
  case (MenuState::LOOPS):
  {
    int curLoopPosition = incrementLoops(isClockwise, id);
    display.sendLoopPosition(curLoopPosition, id);
    LoopArray la = bank.getCurrentLoopArray();
    sendArrayMatrixData(la.loopArray, la.arraySize);
  }
  break;

  case (MenuState::PAN):
  {
    Debugger::log("From inside doRotary Pan");
    int curPan = incrementPan(isClockwise, id);
    display.sendPan(curPan, id);
  }
  break;

  case (MenuState::INPUT_VOLUMES):
  {
    Debugger::log("Spin InputVolumes");
    int curInputVolume = incrementInputVolume(isClockwise, id);
    display.sendInputVolume(curInputVolume, id);
  }
  break;

  case (MenuState::OUTPUT_VOLUMES):
  {
    Debugger::log("Spin OutputVolumes");
    int curInputVolume = incrementOutputVolume(isClockwise, id);
    display.sendOutputVolume(curInputVolume, id);
  }
  break;

  case (MenuState::PHASE):
  {
    Debugger::log("Spin Phase");
    int curPhase = incrementPhase(isClockwise, id);
    display.sendPhase(curPhase, id);
    Debugger::log(String(curPhase));
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
void Menu::updateAllValues(Preset preset)
{
  // DO
}

int Menu::incrementLoops(bool isClockwise, int id)
{
  int curLoop = bank.getCurrentLoopPosition(id);
  curLoop = isClockwise ? curLoop + 1 : curLoop - 1;
  bank.setCurrentLoopPosition(curLoop, id);
  LoopArray loopArray = bank.getCurrentLoopArray();
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

void Menu::sendArrayMatrixData(int loopArray[7], int size)
{
  matrixLeft.writeArray(loopArray, size);
  matrixRight.writeArray(loopArray, size);
};

