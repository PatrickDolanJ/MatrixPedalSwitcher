#ifndef ROTARY_BUTTONS
#define ROTARY_BUTTONS

#include <Arduino.h>

class RotaryButtons{
    public:
        RotaryButtons(byte address);
        void setup(int pin, int interuptPin,void (*userFunc)(void));
        int getRotaryID();
        void setPreviousRotaryButtonValue(int buttonValue);
        int getPreviousRotaryButtonValue();
        int getlongPressPreviousMillis();
        void setLongPressPreviousMillis(long time);
    private: 
        int previousRotaryButtonValue;
        long longPressPreviousMillis = 0;
        int rotaryHexToID(byte hexValue);
};

#endif // !ROTARY_BUTTONS