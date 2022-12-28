#ifndef PRESET
#define PRESET

#include <Arduino.h>
#include <Loop.h>

enum PresetID
{
    presetA = 0,
    presetB = 1,
    presetC = 2,
    presetD = 3,
    presetE = 4
};

class Preset
{
public:
    Preset();
    // setters
    void setLoopPosition(int position, int id);
    void setInputVolume(int volume, int id);
    void setOutputVolume(int volume, int id);
    void setPan(int pan, int id);
    void setIsStereo(bool isStereoChannelID, int id);
    void setIsDelayTrail(bool isDelayTrail, int id);
    void setPhase(int phase, int id);

    // getters
    int getLoopPosition(int id);
    int getInputVolume(int id);
    int getOutputVolume(int id);
    int getPan(int id);
    int getLeftOutputVolume(int id);
    int getRightOutputVolume(int id);
    int getisStereo(int id);
    ChannelID getLoopID(int arrayPosition) { return loops[arrayPosition].getChannelID(); };

private:
    PresetID presetID;
    Loop loopA, loopB, loopC, loopD, loopE, loopF, loopG, master;
    Loop loops[8] = {loopA, loopB, loopC, loopD, loopE, loopF, loopG, master};
    int sizeOfLoops = sizeof(loops) / sizeof(loops[0]);
    int idToArray(int id);
};
#endif // PRESET!