#include <Arduino.h>
#include <Menu.h>

Menu::Menu(){};

void Menu::setup(){
    display.setup(NEXTION_BAUD_RATE);
    display.bootScreen();
};

