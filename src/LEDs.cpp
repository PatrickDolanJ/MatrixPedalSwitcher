#include <Arduino.h>
#include <LEDs.h>


LEDs::LEDs(){};

void LEDs::writeAllOff()
{
    for (size_t i = 0; i < 5; i++)
    {
        digitalWrite(ledsExpander,i,LOW);
    }

};

void LEDs::writeLed(bool state, int id)
{
    digitalWrite(ledsExpander,id, state ? HIGH : LOW);
};