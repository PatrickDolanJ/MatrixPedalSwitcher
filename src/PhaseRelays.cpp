#include <PhaseRelays.h>

PhaseRelays::PhaseRelays(){};

void PhaseRelays::sendPhase(int phase, int id)
{
    bool isleftPhaseIn;
    bool isrightPhaseIn;
    switch (phase)
    {
    case (0):
        isleftPhaseIn = true;
        isrightPhaseIn = true;
        break;
    case (1):
        isleftPhaseIn = true;
        isrightPhaseIn = false;
        break;
    case (2):
        isleftPhaseIn = false;
        isrightPhaseIn = true;
        break;
    case (3):
        isleftPhaseIn = false;
        isrightPhaseIn = false;
        break;
    }
    digitalWrite(leftPhaseExpander, id, boolToValue(isleftPhaseIn));
    digitalWrite(rightPhaseExpander, id, boolToValue(isrightPhaseIn));
}

int PhaseRelays::boolToValue(bool onOrOff)
{
    return onOrOff ? HIGH : LOW;
}
