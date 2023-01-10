#ifndef sd_card_inteface
#define sd_card_inteface

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <DeviceConfig.h>

class SDCard
{
public:
    SDCard(int chipSelectPin);
    void begin();
    bool checkForGlobalDataFile(String fileName);

    int getPrevBankId();
    void setPrevBankId(int id);
    int getNumBanks();
    void addBank();

private:
    int chipSelectPin;
    void initiateGlobalData();
};

#endif
