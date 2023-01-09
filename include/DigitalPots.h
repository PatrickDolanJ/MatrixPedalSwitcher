#ifndef DIGITAL_POTS
#define DIGITAL_POTS

#include <Arduino.h>
#include <DeviceConfig.h>

class DigitalPots
{
public:
    void setup();  
    void sendLeftOutputVolume(int value,int id);
    void sendRightOutPutVolume(int value,int id);
    void sendLeftInputVolume(int value,int id);
    void sendRightInputVolume(int value,int id);
    void volumeMuteStart(int leftVolume, int rightVolume);
    void volumeMuteEnd(int leftVolume, int rightVolume);
private:
    void digitalPotWrite(int chipSelect, int internalPotId, int value);
};

#endif // !DIGITAL_POTS