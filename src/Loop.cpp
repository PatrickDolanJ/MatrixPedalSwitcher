#include <Arduino.h>
#include <Loop.h>
#include <DeviceConfig.h>

Channel::Channel(){};
//---------------------Setters-------------------------

void Channel::setInputVolume(int volume) { inputVolume = clampVolume(volume); };
void Channel::setOutputVolume(int volume) { outputVolume = clampVolume(volume); };
void Channel::setPan(int pan) { Channel::pan = clampPan(pan); };
void Channel::setIsStereo(bool isStereo) { Channel::isStereo = isStereo; };
void Channel::setChannelID(ChannelID id) { this->channelID = id; };
//-------------------Getters---------------------------
int Channel::getInputVolume() { return inputVolume; };
int Channel::getOutputVolume() { return outputVolume; };
int Channel::getPan() { return pan; };
bool Channel::getIsStereo() { return isStereo; };
ChannelID Channel::getChannelID() { return this->channelID; };

int Channel::getLeftOutputVolume()
{
    float panValue = float(pan);
    float outValue = float(outputVolume);
    return panValue > 50 ? outValue : outValue * panValue / 50.0;
};

int Channel::getRightOutputVolume()
{
    float panValue = float(pan);
    float outValue = float(outputVolume);
    return panValue < 51 ? outValue : outValue * (100.0 - panValue) / 50.0;
};

//---------------------Loop-------------------------
void Loop::setPhase(int phase) { Loop::phase = phase; };
int Loop::getPhase() { return phase; };
void Loop::setIsDelayTrail(bool isDelayTrail) { Loop::isDelayTrail = isDelayTrail; };
bool Loop::getIsDelayTrail() { return isDelayTrail; };
void Loop::setChannelPosition(int position) { channelPosition = clampPosition(position); };
int Loop::getChannelPosition() { return channelPosition; };

//--------------------Master------------------------
void Master::setSendDry(int id) { Master::sendDry = clampDrySend(id); };
int Master::getSendDry() { return Master::sendDry; };

//---------------------------"Data Validators"----------------------

int Channel::clampVolume(int volume) { return constrain(volume, 0, MAX_VOLUME); };

int Loop::clampPosition(int position) { return constrain(position, 0, 7); };

int Channel::clampPan(int pan) { return constrain(pan, 0, MAX_PAN); };

int Master::clampDrySend(int drySend) { return constrain(drySend, -1, 7); };