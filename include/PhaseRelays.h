#ifndef PHASE_RELAYS
#define PHASE_RELAYS

#include <Arduino.h>
#include <Relays.h>

class PhaseRelays
{
public:
    PhaseRelays(byte leftAddress, byte rightAddress);

private:
    //Relays &leftPhaseRelays;
    //Relays &rightPhaseRelays;
};

#endif // PHASE_RELAYS