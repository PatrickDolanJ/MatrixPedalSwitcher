#include <Arduino.h>
#include <Bank.h>
#include <Loop.h>
#include <Preset.h>

Bank::Bank()
{
    for (int i = 0; i < sizeOfPresets; i++)
    {
        presets[i].setPresetId(static_cast<PresetID>(i));
    }
    this->currentPreset = presets[presetID_A];
}

//--------------------------Setters------------------------------
void Bank::setBankId(int id) { this->bankId = id; };

void Bank::setCurrentPreset(int id)
{
    presets[getCurrentPresetID()] = currentPreset;
    currentPreset = presets[id];
};

void Bank::setCurrentLoopPosition(int position, int channelId) { currentPreset.setLoopPosition(position, channelId); };
void Bank::setCurrentInputVolume(int volume, int channelId) { currentPreset.setInputVolume(volume, channelId); };
void Bank::setCurrentOutputVolume(int volume, int channelId) { currentPreset.setOutputVolume(volume, channelId); };
void Bank::setCurrentPan(int pan, int channelId) { currentPreset.setPan(pan, channelId); };
void Bank::setCurrentIsStereo(bool isStereoChannel, int channelId) { currentPreset.setIsStereo(isStereoChannel, channelId); };
void Bank::setCurrentIsDelayTrail(bool isDelayTrail, int channelId) { currentPreset.setIsDelayTrail(isDelayTrail, channelId); };
void Bank::setCurrentPhase(int phase, int channelId) { currentPreset.setPhase(phase, channelId); };
void Bank::setCurrentDrySend(int id) { currentPreset.setDrySend(id); };

//--------------------------Getters------------------------------
ChannelID Bank::getLoopID(int presetId, int channelId)
{
    return presets[presetId].getLoopID(channelId);
};

int Bank::getBankID() { return bankId; };
Preset Bank::getCurrentPreset() { return currentPreset; };
PresetID Bank::getCurrentPresetID() { return currentPreset.getPresetID(); };
int Bank::getCurrentLoopPosition(int channelId) { return currentPreset.getLoopPosition(channelId); };
int Bank::getCurrentInputVolume(int channelId) { return currentPreset.getInputVolume(channelId); };
int Bank::getCurrentOutputVolume(int channelId) { return currentPreset.getOutputVolume(channelId); };
int Bank::getCurrentPan(int channelId) { return currentPreset.getPan(channelId); };
int Bank::getCurrentLeftOutputVolume(int channelId) { return currentPreset.getLeftOutputVolume(channelId); };
int Bank::getCurrentRightOutputVolume(int channelId) { return currentPreset.getRightOutputVolume(channelId); };
bool Bank::getCurrentIsStereo(int channelId) { return currentPreset.getIsStereo(channelId); };
bool Bank::getCurrentIsDelayTrail(int channelId) { return currentPreset.getIsDelayTrail(channelId); };
int Bank::getCurrentDrySend() { return currentPreset.getDrySend(); };
