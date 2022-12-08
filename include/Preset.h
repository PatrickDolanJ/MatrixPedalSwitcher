#ifndef PRESET_HEADER
#define PRESET_HEADER

#include <Arduino.h>

struct PresetData{
    
        int presetID = 0;
        int bankID = 0;
        int loopPositions[7] = {0,2,5,0,0,0,0}; // This may change ----> 8th position to allow for "Dry" loop to be sent to output
        int inputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
        int leftOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
        int rightOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
        int phase[8] = {0,0,0,0,0,0,0,0};
        bool returns[8] = {0,0,0,0,0,0,0,0}; // 0=Stereo, 1=Mono
        bool delayTrails[7] = {0,0,0,0,0,0,0}; // 0=No trail, 1=Delay Trail 
        float delayTrailsTimeSeconds[7] = {DEFAIUL_DELAY_TIME_S,DEFAIUL_DELAY_TIME_S,DEFAIUL_DELAY_TIME_S,DEFAIUL_DELAY_TIME_S,DEFAIUL_DELAY_TIME_S,DEFAIUL_DELAY_TIME_S,DEFAIUL_DELAY_TIME_S};
    };

// Test Data
// int CurrentPresetID = 0;
// int CurrentBankID = 0;
// int CurrentLoopPositions[7] = {0,2,4,5,0,0,0}; // This may change ----> 8th position to allow for "Dry" loop to be sent to output
// int CurrentInputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
// int CurrentLeftOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
// int CurrentRightOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
// int CurrentPhase[8] = {0,0,0,0,0,0,0,0};
// bool CurrentReturns[8] = {0,0,0,0,0,0,0,0}; // 0=Stereo, 1=Mono
// bool CurrentDelayTrails[7] = {0,0,0,0,0,0,0}; // 0=No trail, 1=Delay Trail 
// float CurrentDelayTrailsTimeSeconds[7] = {0,0,0,0,0,0,0};
// //

#endif 

