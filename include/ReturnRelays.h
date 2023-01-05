#ifndef RELAYS
#define RELAYS

#include <Arduino.h>
#include <pcf8574.h>
#include <DeviceConfig.h>

class ReturnRelays
{
public:
    ReturnRelays();
    void sendState(int internalPin, bool onOrOff);
    void sendAllStates(bool onOrOff);

private:
    byte address;
    PCF8574 relay = PCF8574(RETURN_RELAYS_ADDRESS);
    int boolToValue(bool onOrOff);
};
#endif // RELAYS