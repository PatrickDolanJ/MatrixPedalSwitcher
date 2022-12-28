#include <Preset.h>
#include <Arduino.h>
#include <Loop.h>
Preset::Preset()
{
    for (size_t i = 0; i < sizeOfLoops; i++)
    {
        loops[i].setChannelID(static_cast<ChannelID>(i));
    }
};

int Preset::idToArray(int id) { return id - 1; };

//---------------------Setters-------------------------
void Preset::setLoopPosition(int position, int id)
{
    int arrayId = idToArray(id);
    loops[arrayId].setChannelPosition(position);
}

void Preset::setInputVolume(int volume, int id)
{
    int arrayId = idToArray(id);
    loops[arrayId].setInputVolume(volume);
}

void Preset::setOutputVolume(int volume, int id)
{
    int arrayId = idToArray(id);
    loops[arrayId].setOutputVolume(volume);
}

void Preset::setPan(int pan, int id)
{
    int arrayId = idToArray(id);
    loops[arrayId].setPan(pan);
}

void Preset::setIsStereo(bool isStereo, int id)
{
    int arrayId = idToArray(id);
    loops[arrayId].setIsStereo(isStereo);
}

void Preset::setPhase(int phase, int id)
{

}