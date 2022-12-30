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
        //Updating Values
        void sendLoopPosition(int position, int id);
        void sendInputVolume(int volume, int id);
        void sendOutputVolume(int volume, int id);
        void sendPan(int pan, int id);
        void sendReturn(bool isStereo, int id);
        void sendDelayTrail(bool isDelayTrail, int id);
        

    private:
        unsigned long baudRate;
    };

#endif // ! DISPLAY_H
