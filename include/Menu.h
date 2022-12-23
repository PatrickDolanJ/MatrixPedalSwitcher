#ifndef MENU
#define MENU

#include <Arduino.h>
#include <Display.h>
#include <DeviceConfig.h>

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
        enum MenuState {LOOPS = 1,PAN = 2, INPUT_VOLUMES = 3,OUTPUT_VOLUMES = 4, PHASE = 5, NUM_MENU_OPTIONS = 6};
        MenuState menuState;
};

#endif //MENU