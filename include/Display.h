#ifndef  DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>


class Display{
    public:
        Display();
        void setup(unsigned long baudRate);
        void updateAll();
        void sendEndCommand();
        void bootScreen();
        void setHomeScreen();
        void highlight(bool onOrOff);


    private:
        unsigned long baudRate;
    };

#endif // ! DISPLAY_H
