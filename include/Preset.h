#ifndef PRESET
#define PRESET

#include <Arduino.h>
#include <Loop.h>
#include <LoopArray.h>

enum PresetID
{
    presetID_A = 0,
    presetID_B = 1,
    presetID_C = 2,
    presetID_D = 3,
    presetID_E = 4
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
    void setDrySend(int id);
    void setPresetId(PresetID id);

    // getters
    int getLoopPosition(int id);
    LoopArray getLoopArray();

    int getInputVolume(int id);
    int getOutputVolume(int id);
    int getPan(int id);
    int getLeftOutputVolume(int id);
    int getRightOutputVolume(int id);
    bool getIsStereo(int id);
    bool getIsDelayTrail(int id);
    int getPhase(int id);
    int getDrySend();
    ChannelID getLoopID(int arrayPosition);
    PresetID getPresetID() { return presetID; };


private:
    PresetID presetID;
    Master master;
    Loop loops[7] = {Loop(),Loop(),Loop(),Loop(),Loop(),Loop(),Loop()};
    int sizeOfLoops = sizeof(loops) / sizeof(loops[0]);
    bool checkIfMaster(int arrayId);
};
#endif // PRESET!