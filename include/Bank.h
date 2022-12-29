#ifndef BANK
#define BANK

#include <Arduino.h>
#include <Preset.h>

class Bank
{
public:
    Bank(int id);
    Preset getPreset();

private:
    int bankId;
    Preset presetA,
        presetB,
        presetC,
        presetD,
        presetE;
    Preset presets[5] = {presetA, presetB, presetC, presetD, presetE};
    int sizeOfPresets = sizeof(presets)/sizeof(presets[0]);
};

#endif // !BANK
