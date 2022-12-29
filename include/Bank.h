#ifndef BANK
#define BANK

#include <Arduino.h>
#include <Preset.h>

class Bank
{
public:
    Bank(int id);

private:
    int bankId;
    Preset presetA(presetID_A),
        presetB(presetID_B),
        presetC(presetID_C),
        presetD(presetID_D),
        presetE(presetID_E);
}

#endif // !BANK
