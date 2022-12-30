#ifndef MENU
#define MENU

#include <Arduino.h>
#include <Display.h>
#include <DeviceConfig.h>
#include <MenuState.h>
#include <Bank.h>

class Menu{
    public:
        Menu();
        void setup();
        void changeMenuState(int id);
        void doButton(int id);
        void doFoot(int id);
        void duringLongPress(int id);
        void doLongPress(int id);
        void doDoubleFootPress();
        void doRotaryEnoderSpin(bool isClockwise, int id);
    private:
        Display display;
        MenuState menuState;
        Bank bank;
};

#endif //MENU