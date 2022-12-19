#ifndef FOOT_SWITCHES
#define FOOT_SWITCHES

#include <Arduino.h>

class FootSwitches{
    public:
        FootSwitches(byte address);
        void setup(int pin, int interuptPin,void (*userFunc)(void));
        bool checkInterupt();
    private:
        volatile bool flag = false;

};


#endif //FOOT_SWITCHES