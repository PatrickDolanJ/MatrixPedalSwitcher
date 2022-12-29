#include <Preset.h>
#include <Arduino.h>
#include <Loop.h>
#include <Debugger.h>

Preset::Preset()
{
    for (int i = 0; i < sizeOfLoops; i++)
    {
        loops[i].setChannelID(static_cast<ChannelID>(i + 1));
    }
    master.setChannelID(channel_Master);
};

//---------------------Setters-------------------------

void Preset::setPresetId(PresetID id)
{
    this->presetID = id;
};

void Preset::setLoopPosition(int position, int id)
{
    int arrayPosition = idToArray(position);
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        loops[arrayId].setChannelPosition(arrayPosition);
    }
    else
    {
        Debugger::log("Cannot set phase on Master");
    }
}

void Preset::setInputVolume(int volume, int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        loops[arrayId].setInputVolume(volume);
    }
    else
    {
        master.setInputVolume(volume);
    }
}

void Preset::setOutputVolume(int volume, int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        loops[arrayId].setOutputVolume(volume);
    }
    else
    {
        master.setOutputVolume(volume);
    }
}

void Preset::setPan(int pan, int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        loops[arrayId].setPan(pan);
    }
    else
    {
        master.setPan(pan);
    }
}

void Preset::setIsStereo(bool isStereo, int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        loops[arrayId].setIsStereo(isStereo);
    }
    else
    {
        master.setIsStereo(isStereo);
    }
}

void Preset::setPhase(int phase, int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        loops[arrayId].setPhase(phase);
    }
    else
    {
        Debugger::log("Cannot set phase on Master");
    }
}

void Preset::setIsDelayTrail(bool isDelayTrail, int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        loops[arrayId].setIsDelayTrail(isDelayTrail);
    }
    else
    {
        Debugger::log("Cannot set Delay Trail  on Master");
    }
}

void Preset::setDrySend(int id)
{
    int arrayId = idToArray(id);
    master.setSendDry(arrayId);
}

//--------------------------Getters----------------------------

ChannelID Preset::getLoopID(int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        return loops[arrayId].getChannelID();
    }
    else
    {
        return master.getChannelID();
    }
}

int Preset::getLoopPosition(int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        return loops[arrayId].getChannelPosition();
    }
    else
    {
        return -1;
    }
}

int Preset::getInputVolume(int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        return loops[arrayId].getInputVolume();
    }
    else
    {
        return master.getInputVolume();
    }
}

int Preset::getOutputVolume(int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        return loops[arrayId].getOutputVolume();
    }
    else
    {
        return master.getOutputVolume();
    }
}

int Preset::getPan(int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        return loops[arrayId].getPan();
    }
    else
    {
        return master.getPan();
    }
}

int Preset::getLeftOutputVolume(int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        return loops[arrayId].getLeftOutputVolume();
    }
    else
    {
        return master.getLeftOutputVolume();
    }
}

int Preset::getRightOutputVolume(int id)
{
    int arrayId = idToArray(id);
    if (!checkIfMaster(arrayId))
    {
        return loops[arrayId].getRightOutputVolume();
    }
    else
    {
        return master.getRightOutputVolume();
    }
}

int Preset::getDrySend()
{
    return master.getSendDry();
}

bool Preset::checkIfMaster(int arrayId) { return arrayId == 7; }

int Preset::idToArray(int id) { return id - 1; };
