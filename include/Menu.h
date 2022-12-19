#ifndef MENU
#define MENU

#include <Arduino.h>
#include <Display.h>
#include <DeviceConfig.h>

class Menu{
    public:
        Menu();
        void setup();


    private:
        Display display;
    
};

#endif //MENU