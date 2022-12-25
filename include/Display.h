#ifndef  DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <MenuState.h>

class Display{
    public:
        Display();
        void setup(unsigned long baudRate);
        void updateAll();
        void sendEndCommand();
        void bootScreen();
        void setHomeScreen();
        void highlightMenu(bool onOrOff, MenuState state);


    private:
        unsigned long baudRate;
    };

#endif // ! DISPLAY_H
