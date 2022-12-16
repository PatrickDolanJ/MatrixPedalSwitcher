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

    private:
        unsigned long BAUD_RATE;
    };

#endif // ! DISPLAY_H
