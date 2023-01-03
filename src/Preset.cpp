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

void Preset::setPresetId(PresetID id) { this->presetID = id; };

void Preset::setLoopPosition(int position, int id)
{
    if (!checkIfMaster(id))
    {
        loops[id].setChannelPosition(position);
    }
    else
    {
        Debugger::log("Cannot set phase on Master");
    }
}

void Preset::setInputVolume(int volume, int id)
{
    if (!checkIfMaster(id))
    {
        loops[id].setInputVolume(volume);
    }
    else
    {
        master.setInputVolume(volume);
    }
}

void Preset::setOutputVolume(int volume, int id)
{
    if (!checkIfMaster(id))
    {
        loops[id].setOutputVolume(volume);
    }
    else
    {
        master.setOutputVolume(volume);
    }
}

void Preset::setPan(int pan, int id)
{
    if (!checkIfMaster(id))
    {
        loops[id].setPan(pan);
    }
    else
    {
        master.setPan(pan);
    }
}

void Preset::setIsStereo(bool isStereo, int id)
{
    if (!checkIfMaster(id))
    {
        loops[id].setIsStereo(isStereo);
    }
    else
    {
        master.setIsStereo(isStereo);
    }
}

void Preset::setPhase(int phase, int id)
{
    if (!checkIfMaster(id))
    {
        loops[id].setPhase(phase);
    }
    else
    {
        Debugger::log("Cannot set phase on Master");
    }
}

void Preset::setIsDelayTrail(bool isDelayTrail, int id)
{
    if (!checkIfMaster(id))
    {
        loops[id].setIsDelayTrail(isDelayTrail);
    }
    else
    {
        Debugger::log("Cannot set Delay Trail  on Master");
    }
}

void Preset::setDrySend(int id)
{
    master.setSendDry(id);
}

//--------------------------Getters----------------------------

ChannelID Preset::getLoopID(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getChannelID();
    }
    else
    {
        return master.getChannelID();
    }
}

int Preset::getLoopPosition(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getChannelPosition();
    }
    else
    {
        return -1;
    }
}

int Preset::getInputVolume(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getInputVolume();
    }
    else
    {
        return master.getInputVolume();
    }
}

int Preset::getOutputVolume(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getOutputVolume();
    }
    else
    {
        return master.getOutputVolume();
    }
}

int Preset::getPan(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getPan();
    }
    else
    {
        return master.getPan();
    }
}

int Preset::getLeftOutputVolume(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getLeftOutputVolume();
    }
    else
    {
        return master.getLeftOutputVolume();
    }
}

int Preset::getRightOutputVolume(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getRightOutputVolume();
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

bool Preset::getIsDelayTrail(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getIsDelayTrail();
    }
    else
    {
        return false;
    }
};

int Preset::getPhase(int id)
{
    if (!checkIfMaster(id))
    {
        return loops[id].getPhase();
    }
    else
    {
        return -1;
    }
}

LoopArray Preset::getLoopArray()
{
    LoopArray loopArray;
    for (int i = 0; i < loopArray.arraySize; i++)
    {
        loopArray.loopArray[i] = loops[i].getChannelPosition();
    }
    return loopArray;
};

bool Preset::getIsStereo(int id)
{
    if(!checkIfMaster(id))
    {
        return loops[id].getIsStereo();
    }
    else
    {
        return master.getIsStereo();
    }
}

//----------------------------------Helpers--------------------------------------
bool Preset::checkIfMaster(int id) { return id == channel_Master; };
