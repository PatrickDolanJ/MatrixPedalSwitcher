#ifndef PRESET
#define PRESET

#include <Arduino.h>
#include <Loop.h>

enum PresetID {};


class Preset{
    public:
        Preset();
        //setters
        void setLoopPosition(int position, LoopID id);
        void setInputVolume(int volume, LoopID id);
        void setOutputVolume(int volume, LoopID id);
        void setPan(int pan, LoopID id);
        void setIsStereo(bool isStereoLoopID, LoopID id);

        

  
    private:
        PresetID presetID;
        Loop loopA, loopB,loopC,loopD,loopE,loopF,loopG,master;
        Loop loops[8] = {loopA,loopB,loopC,loopD,loopE,loopF,loopG,master};


};
#endif //PRESET!