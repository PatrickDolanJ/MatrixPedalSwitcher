#include <Arduino.h>
#include <Menu.h>
#include <Debugger.h>
#include <I2Cscanner.h>

Menu::Menu(){};
I2CScanner scanner;


void Menu::setup(){
    display.setup(NEXTION_BAUD_RATE);
    display.bootScreen();
    scanner.scan();
  
};


void Menu::doButton(int id){
    Debugger::log("Button pressed: " + String(id));
    changeMenuState(id);
};

void Menu::doFoot(int id){
    Debugger::log("Foot pressed: " + String(id));
    // change preset
};


void Menu::doDoubleFootPress(){
    Debugger::log("Double Foot Button detected.");
}

void Menu::duringLongPress(int id){
    Debugger::log("Long press is currently happening!" + String(id));
};

void Menu::doLongPress(int id){
    Debugger::log("Long press finished: " + String(id));
};

void Menu::doRotaryEnoderSpin(bool isClockwise, int id){
    Debugger::log("Encoder spin: " + String(id));
};

void Menu::changeMenuState(int id){
if(id ==2){
  //highlightMenu(false);

    if(menuState == NUM_MENU_OPTIONS-1){
      menuState = static_cast<MenuState>(1);
    } else {
      menuState = static_cast<MenuState>(menuState+1);
    }
      Serial.println("MenuState = " + String(menuState));
      //highlightMenu(true);
  } else if(id ==1)
  {
    //highlightMenu(false);
    if(menuState == 1){
    menuState = static_cast<MenuState>(NUM_MENU_OPTIONS-1);
    } else {
    menuState = static_cast<MenuState>(menuState-1);
    }
    Serial.println("MenuState = " + String(menuState));
    //highlightMenu(true);
  }
};

