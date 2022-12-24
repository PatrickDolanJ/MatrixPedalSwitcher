#include <Arduino.h>
#include <Loop.h>

Channel::Channel(){};
//---------------------Setters-------------------------
void Channel::setLoopPosition(int position){loopPosition = position;};
void Channel::setInputVolume(int volume){inputVolume = volume;};
void Channel::setOutputVolume(int volume){outputVolume = volume;};
void Channel::setPan(int pan){Channel::pan = pan;};
void Channel::setIsStereo(bool isStereo){Channel::isStereo = isStereo;};
//void Channel::setIsDelayTrail(bool isDelayTrail){Channel::isDelayTrail = isDelayTrail;};


//-------------------Getters---------------------------
int Channel::getLoopPosition(){return loopPosition;};
int Channel::getInputVolume(){return inputVolume;};
int Channel::getOutputVolume(){return outputVolume;};
int Channel::getPan(){return pan;};
bool Channel::getIsStereo(){return isStereo;};
//bool Channel::getIsDelayTrail(){return isDelayTrail;};
int Channel::getLeftOutputVolume(){
    float panValue = float(pan);
    float outValue = float(outputVolume);
    return panValue > 50 ? outValue : outValue * panValue / 50.0;  
};

int Channel::getRightOutputVolume(){
    float panValue = float(pan);
    float outValue = float(outputVolume);
    return panValue < 51 ? outValue : outValue * (100.0 - panValue) / 50.0; 
};


//---------------------Loop-------------------------
void Loop::setPhase(int phase){Loop::phase = phase;};
int Loop::getPhase(){return phase;};
void Loop::setIsDelayTrail(bool isDelayTrail){Loop::isDelayTrail = isDelayTrail;};
bool Loop::getIsDelayTrail(){return isDelayTrail;};

//--------------------Master------------------------
void Master::setSendDry(int id){Master::sendDry = id;};
int Master::getSendDry(){return Master::sendDry;};

 




