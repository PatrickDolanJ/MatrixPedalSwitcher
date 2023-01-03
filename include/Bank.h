#ifndef BANK
#define BANK

#include <Arduino.h>
#include <Preset.h>
#include <LoopArray.h>

class Bank
{
public:
    Bank();
    // Getters
    Preset getCurrentPreset();
    int getBankID();
    ChannelID getLoopID(int presetId, int channelId);
    PresetID getCurrentPresetID();

    int getCurrentLoopPosition(int channelId);
    LoopArray getCurrentLoopArray();
    int getCurrentInputVolume(int channelId);
    int getCurrentOutputVolume(int channelId);
    int getCurrentPan(int channelId);
    int getCurrentLeftOutputVolume(int channelId);
    int getCurrentRightOutputVolume(int channelId);
    bool getCurrentIsStereo(int channelId);
    bool getCurrentIsDelayTrail(int channelId);
    int getCurrentPhase(int id);
    int getCurrentDrySend();

    // Setters
    void setBankId(int id);
    void setCurrentPreset(int id);
    void setCurrentLoopPosition(int position, int channelId);
    void setCurrentInputVolume(int volume, int channelId);
    void setCurrentOutputVolume(int volume, int channelId);
    void setCurrentPan(int pan, int channelId);
    void setCurrentIsStereo(bool isStereoChannelID, int channelId);
    void setCurrentIsDelayTrail(bool isDelayTrail, int channelId);
    void setCurrentPhase(int phase, int channelId);
    void setCurrentDrySend(int id);

private:
    int bankId;
    Preset currentPreset;
    Preset presets[5] = {Preset(),Preset(),Preset(),Preset(),Preset()};
    int sizeOfPresets = sizeof(presets) / sizeof(presets[0]);
};

#endif // !BANK
