#include <Arduino.h>
#include <Menu.h>
#include <Debugger.h>
#include <I2Cscanner.h>
#include <DeviceConfig.h>
#include <LoopArray.h>
#include <MatrixLibrary.h>
#include <MemoryFree.h>
#include <Loop.h>

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
  //--------------------Display Setup-------------------
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
  if (id != bank.getCurrentPresetID())
  {
    bank.setCurrentPreset(id);
  }
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
    display.setMenuStateReturn();
    returnHighlighted = true;
  }
};

void Menu::doLongPress(int id)
{
  Debugger::log("Long press finished: " + String(id));
  display.highlightReturn(false, id);
  bank.setCurrentReturn(!bank.getCurrentReturn(id), id);
  bool newReturn = bank.getCurrentReturn(id);
  returnRelays.sendState(id, newReturn);
  display.setMenuState(menuState);
  display.sendReturn(newReturn, id);
  returnHighlighted = false;
};

void Menu::doRotaryEnoderSpin(bool isClockwise, int id)
{
  Debugger::log("Encoder spin: " + String(id));

  switch (menuState)
  {
  case (MenuState::LOOPS):
  {
    if (id != ChannelID::channel_Master)
    {
      int curLoopPosition = incrementLoops(isClockwise, id);
      display.sendLoopPosition(curLoopPosition, id);
    }
    if (id == ChannelID::channel_Master)
    {
      int curDrysend = incrementDrySend(isClockwise, id);
      display.sendDrySend(curDrysend);
    }
    updateMatrix(bank.getCurrentPreset());
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
    if (id != ChannelID::channel_Master)
    {
      Debugger::log("Spin Phase");
      int curPhase = incrementPhase(isClockwise, id);
      sendPhase(curPhase, id);
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
  display.setMenuState(menuState);
};

//-------------------------------------------------------------------------
//------------------------------------helpers------------------------------
void Menu::updateAllValuesDisplay(Preset preset)
{
  display.updateBankPresetInfo(bank.getBankID(), preset.getPresetID());
  display.setMenuState(menuState);
  display.sendDrySend(bank.getCurrentDrySend());

  for (int i = 0; i < 8; i++)
  {

    display.sendPan(bank.getCurrentPan(i), i);
    display.sendReturn(bank.getCurrentReturn(i), i);
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

int Menu::incrementDrySend(bool isClockwise, int id)
{
  int curDrySend = bank.getCurrentDrySend();
  curDrySend = isClockwise ? curDrySend + 1 : curDrySend - 1;
  bank.setCurrentDrySend(curDrySend);
  return bank.getCurrentDrySend();
}

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
  int curPhase = bank.getCurrentPhase(id);
  curPhase = isClockwise ? (curPhase + 1) % 4 : (curPhase + 3) % 4;
  bank.setCurrentPhase(curPhase, id);
  return bank.getCurrentPhase(id);
};

//----------------------------------------Hardware---------------------------------------

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
  updateMatrix(preset);
  connectDelayTrails(preset);
  changeFootLeds(preset.getPresetID());
  for (size_t i = 0; i < 8; i++)
  {
    sendPhase(preset.getPhase(i), i);
    sendReturn(preset.getIsStereo(i), i);
    sendInputVolumes(preset.getInputVolume(i), i);
    sendOutputVolumes(preset.getLeftOutputVolume(i), preset.getRightOutputVolume(i), i);
  }
};

void Menu::sendReturn(bool value, int id)
{
  returnRelays.sendState(value, id);
};

void Menu::sendPhase(int phase, int id)
{
  phaseRelays.sendPhase(phase, id);
};

void Menu::updateMatrix(Preset preset)
{
  matrixLeft.writeArray(preset.getLoopArray().loopArray, preset.getLoopArray().arraySize);
  matrixRight.writeArray(preset.getLoopArray().loopArray, preset.getLoopArray().arraySize);

  int drySend = preset.getDrySend();
  if (drySend != -1)
  {
    matrixLeft.writeData(true, drySend, 7);
    matrixRight.writeData(true, drySend, 7);
  }
};

void Menu::connectDelayTrails(Preset preset)
{
  for (size_t i = 0; i < ChannelID::channel_Master; i++)
  {
    if (preset.getIsDelayTrail(i))
    {
      matrixLeft.writeData(true, i, 7);
      matrixRight.writeData(true, i, 7);
    }
  }
}