#include <Arduino.h>
#include <DigitalPots.h>
#include <Debugger.h>
#include <SPI.h>

void DigitalPots::setup()
{
    size_t sizeOfChipSelectPinsArray = sizeof(POT_EXPANDER_PINS) / sizeof(POT_EXPANDER_PINS[0]);
    for (size_t i = 0; i < sizeOfChipSelectPinsArray; i++)
    {
        pinMode(POT_EXPANDER_PINS[i], OUTPUT);
    }
};

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

void DigitalPots::volumeMuteStart(int inputVolume, int leftOutputVolume, int rightOutputVolume)
{
    for (int i = 1; i < VOLUME_DAMPENING_INCREMENTS + 1; i++)
    {
        int newInputVol = inputVolume * (1.0- (float(i) / float(VOLUME_DAMPENING_INCREMENTS)));
        sendLeftInputVolume(newInputVol, 7);
        sendRightInputVolume(newInputVol, 7);
        int newLeftOutputVol = leftOutputVolume * (1 - (float(VOLUME_DAMPENING_INCREMENTS) / float(i)));
        sendLeftOutputVolume(newLeftOutputVol, 7);
        int newRightOutputVool = rightOutputVolume * (1 - (float(VOLUME_DAMPENING_INCREMENTS) / float(i)));
        sendRightOutPutVolume(newRightOutputVool, 7);
        Debugger::log(String(newInputVol));
    }
    sendLeftInputVolume(0, 7);
    sendRightInputVolume(0, 7);
    sendLeftOutputVolume(0, 7);
    sendRightOutPutVolume(0, 7);
};

void DigitalPots::volumeMuteEnd(int inputVolume, int leftOutputVolume, int rightOutputVolume)
{
    for (int i = VOLUME_DAMPENING_INCREMENTS; i > 0 + 1; i--)
    {
        int newInputVol = inputVolume * (1.0-(float(i) / float(VOLUME_DAMPENING_INCREMENTS)));
        sendLeftInputVolume(newInputVol, 7);
        sendRightInputVolume(newInputVol, 7);
        int newLeftOutputVol = leftOutputVolume * (1 - (float(VOLUME_DAMPENING_INCREMENTS) / float(i)));
        sendLeftOutputVolume(newLeftOutputVol, 7);
        int newRightOutputVool = rightOutputVolume * (1 - (float(VOLUME_DAMPENING_INCREMENTS) / float(i)));
        sendRightOutPutVolume(newRightOutputVool, 7);
        Debugger::log(String(newInputVol));
    }
    sendLeftInputVolume(inputVolume, 7);
    sendRightInputVolume(inputVolume, 7);
    sendLeftOutputVolume(leftOutputVolume, 7);
    sendRightOutPutVolume(rightOutputVolume, 7);
}
