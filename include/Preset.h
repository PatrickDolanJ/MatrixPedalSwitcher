#ifndef PRESET_HEADER
#define PRESET_HEADER

#include <Arduino.h>
#include <DeviceConfig.h>

struct PresetData{
        int presetID= -1;
        int bankID = 0;
        int loopPositions[7] = {0,2,5,0,0,0,0}; // This may change ----> 8th position to allow for "Dry" loop to be sent to output
        int inputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
        int leftOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME}; // just for pots
        int rightOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME}; // just for pots
        int outputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
        int pan[8] = {DEFAULT_PAN,DEFAULT_PAN,DEFAULT_PAN,DEFAULT_PAN,DEFAULT_PAN,DEFAULT_PAN,DEFAULT_PAN,DEFAULT_PAN};
        int phase[8] = {0,0,0,0,0,0,0,0};
        bool returns[8] = {0,0,0,0,0,0,0,0}; // 0=Stereo, 1=Mono
        bool delayTrails[7] = {0,0,0,0,0,0,0}; // 0=No trail, 1=Delay Trail 

        PresetData(int id){
                presetID = id;
        }

        PresetData(){}
        
        };
#endif 


