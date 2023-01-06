#include <ReturnRelays.h>
#include <Arduino.h>
#include <pcf8574.h>
#include <Debugger.h>

ReturnRelays::ReturnRelays(){};

void ReturnRelays::sendState(int internalPin, bool onOrOff)
{
    digitalWrite(relay, internalPin, boolToValue(onOrOff));
};

void ReturnRelays::sendAllStates(bool onOrOff)
{
    int value = boolToValue(onOrOff);
    for (size_t i = 0; i < 8; i++)
    {
        sendState(i, value);
    }
};

int ReturnRelays::boolToValue(bool onOrOff)
{
    return onOrOff ? HIGH : LOW;
}