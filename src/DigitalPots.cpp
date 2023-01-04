#include <Arduino.h>
#include <DigitalPots.h>
#include <Debugger.h>
#include <SPI.h>


void DigitalPots::setup()
{
    size_t sizeOfChipSelectPinsArray = sizeof(POT_EXPANDER_PINS)/sizeof(POT_EXPANDER_PINS[0]);
    for (size_t i = 0; i < sizeOfChipSelectPinsArray; i++)
    {
       pinMode(POT_EXPANDER_PINS[i],OUTPUT); 
    }
    
}

void DigitalPots::sendLeftInputVolume(int value, int id)
{
    int interalPotIds[8] = {0, 4, 2, 0, 4, 2, 0, 4};
    int chipSelectIds[8] = {0, 0, 1, 2, 2, 3, 4, 4};
    int curInternalPotId = interalPotIds[id];
    int curChipSelectId = chipSelectIds[id];
    int curChipSelect = POT_EXPANDER_PINS[curChipSelectId];
    digitalPotWrite(curChipSelect, curInternalPotId, value);
};

void DigitalPots::sendRightInputVolume(int value, int id)
{
    int interalPotIds[8] = {1, 5, 3, 1, 5, 3, 1, 5};
    int chipSelectIds[8] = {0, 0, 1, 2, 2, 3, 4, 4};
    int curInternalPotId = interalPotIds[id];
    int curChipSelectId = chipSelectIds[id];
    int curChipSelect = POT_EXPANDER_PINS[curChipSelectId];
    digitalPotWrite(curChipSelect, curInternalPotId, value);
};

void DigitalPots::sendLeftOutputVolume(int value, int id)
{
    int interalPotIds[8] = {2, 0, 4, 2, 0, 4, 2, 0};
    int chipSelectIds[8] = {0, 1, 1, 2, 3, 3, 4, 5};
    int curInternalPotId = interalPotIds[id];
    int curChipSelectId = chipSelectIds[id];
    int curChipSelect = POT_EXPANDER_PINS[curChipSelectId];
    digitalPotWrite(curChipSelect, curInternalPotId, value);
};

void DigitalPots::sendRightOutPutVolume(int value, int id)
{
    int interalPotIds[8] = {3, 1, 5, 3, 1, 5, 3, 1};
    int chipSelectIds[8] = {0, 1, 1, 2, 2, 3, 4, 5};
    int curInternalPotId = interalPotIds[id];
    int curChipSelectId = chipSelectIds[id];
    int curChipSelect = POT_EXPANDER_PINS[curChipSelectId];
    digitalPotWrite(curChipSelect, curInternalPotId, value);
};

void DigitalPots::digitalPotWrite(int chipSelect, int internalPotId, int value)
{
    digitalWrite(chipSelect, LOW);
    delayMicroseconds(SPI_DELAY);
    SPI.transfer(internalPotId);
    SPI.transfer(value);
    delayMicroseconds(SPI_DELAY);
    digitalWrite(chipSelect, HIGH);
};
