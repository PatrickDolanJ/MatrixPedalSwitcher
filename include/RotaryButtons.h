#ifndef ROTARY_BUTTONS
#define ROTARY_BUTTONS

#include <Arduino.h>

class RotaryButtons{
    public:
        RotaryButtons(byte address);
        void setup(int pin, int interuptPin,void (*userFunc)(void));
        bool checkInterupt();
    private: 
        volatile bool flag = false;
};


#endif // !ROTARY_BUTTONS