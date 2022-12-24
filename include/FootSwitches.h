#ifndef FOOT_SWITCHES
#define FOOT_SWITCHES

#include <Arduino.h>

class FootSwitches{
    public:
        FootSwitches(byte address);
        void setup(int pin, int interuptPin,void (*userFunc)(void));
        bool checkInterupt();
        int getFootID();
    private:
        volatile bool flag = false;
        int footHextoID(byte hex);
        int address;
        
};

#endif //FOOT_SWITCHES