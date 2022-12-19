#ifndef RELAYS
#define RELAYS

#include <Arduino.h>
#include <pcf8574.h>

class Relays{
    public:
        Relays(byte address);
        void sendState(int internalPin, bool onOrOff);
        void sendAllStates(bool onOrOff);
    private:
        byte address;
        PCF8574& relay;
        int boolToValue(bool onOrOff);
};
#endif //RELAYS