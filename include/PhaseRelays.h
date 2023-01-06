#ifndef PHASE_RELAYS
#define PHASE_RELAYS

#include <Arduino.h>
#include <pcf8574.h>
#include <DeviceConfig.h>

class PhaseRelays
{
public:
    PhaseRelays();
    void sendPhase(int phase, int id);

private:
    PCF8574 leftPhaseExpander = PCF8574(LEFT_PHASE_RELAYS_ADDRESS);
    PCF8574 rightPhaseExpander = PCF8574(RIGHT_PHASE_RELAY_ADDRESS);
    int boolToValue(bool onOrOff);
};

#endif // PHASE_RELAYS