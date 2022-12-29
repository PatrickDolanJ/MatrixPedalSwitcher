#include <Arduino.h>
#include <Bank.h>

Bank::Bank(int id)
{
    this->bankId = id;  
    for (size_t i = 0; i < sizeOfPresets; i++)
    {
        presets[i].setPresetId(static_cast<PresetID>(i+1));
    }
}

