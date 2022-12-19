#ifndef LOOP
#define LOOP

#include <Arduino.h>

class Loop{
    public:
        Loop();
        // Setters
        void setPresetID(int id);
        void setBankID(int id);
        void setLoopPosition(int position);
        void setInputVolume(int volume);
        void setOutputVolume(int volume);
        void setPan(int pan);
        void setPhase(int phase);
        void setIsStereo(bool isStereo);
        void setIsDelayTrail(bool isDelayTrail);
        // Getters
        int getPresetID();
        int getBankID();
        int getLoopPosition();
        int getInputVolume();
        int getOutputVolume();
        int getPan();
        int getPhase();
        bool getIsStereo();
        bool getIsDelayTrail();
    private:
        int presetID;
        int bankID;
        int loopPosition;
        int inputVolume;
        int outputVolume;
        int pan;
        int phase; //maybe make enumerator?
        bool isStereo;
        bool isDelayTrail;
};

#endif // LOOP