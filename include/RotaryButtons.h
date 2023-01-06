#ifndef ROTARY_BUTTONS
#define ROTARY_BUTTONS

#include <Arduino.h>

class RotaryButtons{
    public:
        RotaryButtons(byte address);
        void setup(int pin, int interuptPin,void (*userFunc)(void));
        int getRotaryID();
        void setPreviousRotaryButtonValue(int buttonValue);
        void setLongPressPreviousMillis(long time);
    private: 
        long longPressPreviousMillis = 0;
        int rotaryHexToID(byte hexValue);
        byte address;
};

#endif // !ROTARY_BUTTONS