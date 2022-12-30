#include <Arduino.h>
#include <Menu.h>
#include <Debugger.h>
#include <I2Cscanner.h>
#include <SPI.h>
#include <DeviceConfig.h>

Menu::Menu(){};

void Menu::setup()
{
  // May want to switch back to custom animation(w/black background) to ensure this stays coherent
  display.setup(NEXTION_BAUD_RATE);
  display.bootScreen();
  menuState = LOOPS;
  SPI.begin();
  delay(4000);
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
  // change preset
};

void Menu::doDoubleFootPress()
{
  Debugger::log("Double Foot Button detected.");
}

void Menu::duringLongPress(int id){

};

void Menu::doLongPress(int id)
{
  Debugger::log("Long press finished: " + String(id));
};

void Menu::doRotaryEnoderSpin(bool isClockwise, int id)
{
  Debugger::log("Encoder spin: " + String(id));
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
    int newMenuState = (menuState + NUM_MENU_OPTIONS -1) % (NUM_MENU_OPTIONS);
    menuState = static_cast<MenuState>(newMenuState);
    Serial.println("MenuState = " + String(menuState));
    display.highlightMenu(true, menuState);
  }
};
