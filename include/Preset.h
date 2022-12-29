#ifndef PRESET
#define PRESET

#include <Arduino.h>
#include <Loop.h>

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
    Preset(PresetID id);
    // setters
    void setLoopPosition(int position, int id);
    void setInputVolume(int volume, int id);
    void setOutputVolume(int volume, int id);
    void setPan(int pan, int id);
    void setIsStereo(bool isStereoChannelID, int id);
    void setIsDelayTrail(bool isDelayTrail, int id);
    void setPhase(int phase, int id);
    void setDrySend(int id);

    // getters
    int getLoopPosition(int id);
    int getInputVolume(int id);
    int getOutputVolume(int id);
    int getPan(int id);
    int getLeftOutputVolume(int id);
    int getRightOutputVolume(int id);
    bool getIsStereo(int id);
    int getIsDelayTrail(int id);
    int getDrySend(int id);
    ChannelID getLoopID(int arrayPosition) { return loops[arrayPosition].getChannelID(); };
    PresetID getPresetID(){return presetID;};
private:
    PresetID presetID;
    Loop loopA, loopB, loopC, loopD, loopE, loopF, loopG;
    Master master;
    Loop loops[7] = {loopA, loopB, loopC, loopD, loopE, loopF, loopG};
    int sizeOfLoops = sizeof(loops)/sizeof(loops[0]);
    int idToArray(int id);
    bool checkIfMaster(int arrayId);
};
#endif // PRESET!