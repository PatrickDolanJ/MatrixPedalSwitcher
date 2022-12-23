#include <Relays.h>
#include <Arduino.h>
#include <pcf8574.h>

Relays::Relays(byte address){
    Relays::address = address;
    relay = PCF8574(address);
};


void Relays::sendState(int internalPin, bool onOrOff){
    int value = onOrOff ? HIGH : LOW;
    digitalWrite(relay, internalPin, value);
};

void Relays::sendAllStates (bool onOrOff){
    int value = boolToValue(onOrOff);
    for (size_t i = 0; i < 8; i++)
    {
        sendState(i,value);
    }
    
};

int Relays::boolToValue(bool onOrOff){
    return onOrOff ? HIGH : LOW;
}