#ifndef CHANNEL
#define CHANNEL

#include <Arduino.h>

class Channel{
    public:
        Channel();
        // Setters
        void setPresetID(int id);
        void setBankID(int id);
        void setLoopPosition(int position);
        void setInputVolume(int volume);
        void setOutputVolume(int volume);
        void setPan(int pan);
        void setPhase(int phase);
        void setIsStereo(bool isStereo);
        // Getters
        int getPresetID();
        int getBankID();
        int getLoopPosition();
        int getInputVolume();
        int getOutputVolume();
        int getPan();
        int getPhase();
        bool getIsStereo();
        int getLeftOutputVolume();
        int getRightOutputVolume();
    private:
        int presetID;
        int bankID;
        int loopPosition;
        int inputVolume;
        int outputVolume;
        int leftOutputVolume;
        int rightOutputVolume;
        int pan;
        int phase; //maybe make enumerator?
        bool isStereo;
};




class Master: public Channel{
    public:
        void setSendDry();
        int getSendDry();
    private:
        int sendDry;
};
#endif // CHANNEL