#ifndef PRESET_HEADER
#define PRESET_HEADER

#include <Arduino.h>

struct PresetStruct{
        int presetID;
        int bankID;
        int loopPositions[7] = {0,0,0,0,0,0,0}; // This may change ----> 8th position to allow for "Dry" loop to be sent to output
        int inputVolumes[8] = {0,0,0,0,0,0,0,0};
        int leftOutputVolumes[8] = {0,0,0,0,0,0,0,0};
        int rightOutputVolumes[8] = {0,0,0,0,0,0,0,0};
        int phase[8] = {0,0,0,0,0,0,0,0};
        bool returns[8] = {0,0,0,0,0,0,0,0}; // 0=Stereo, 1=Mono
        bool delayTrails[7] = {0,0,0,0,0,0,0}; // 0=No trail, 1=Delay Trail 
        float delayTrailsTimeSeconds[7] = {0,0,0,0,0,0,0};
    };

#endif 

