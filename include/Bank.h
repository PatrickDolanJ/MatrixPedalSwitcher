#ifndef BANK
#define BANK

#include <Arduino.h>
#include <Preset.h>

class Bank
{
public:
    Bank(int id);
    // Getters
    Preset getCurrentPreset();
    int getBankID();
    ChannelID getLoopID(int presetId, int channelId);
    PresetID getCurrentPresetID();

    int getCurrentLoopPosition(int channelId);
    int getCurrentInputVolume(int channelId);
    int getCurrentOutputVolume(int channelId);
    int getCurrentPan(int channelId);
    int getCurrentLeftOutputVolume(int channelId);
    int getCurrentRightOutputVolume(int channelId);
    bool getCurrentIsStereo(int channelId);
    bool getCurrentIsDelayTrail(int channelId);
    int getCurrentDrySend();

    // Setters
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
    Preset
        currentPreset,
        presetA,
        presetB,
        presetC,
        presetD,
        presetE;
    Preset presets[5] = {presetA, presetB, presetC, presetD, presetE};
    int sizeOfPresets = sizeof(presets) / sizeof(presets[0]);
};

#endif // !BANK
