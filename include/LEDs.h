#ifndef LEDS
#define LEDS

#include <Arduino.h>
#include <pcf8574.h>
#include <DeviceConfig.h>

class LEDs
{
public:
    LEDs();
    void writeLed(bool state, int id);
    void writeAllOff();
private:
    PCF8574 ledsExpander = PCF8574(FOOT_SWITCH_LIGHTS_ADDRESS);
};

#endif // !LEDS