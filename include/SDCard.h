#ifndef sd_card_inteface
#define sd_card_inteface

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <DeviceConfig.h>
#include <Flash.h> 

class SDCard
{
public:
    SDCard(int chipSelectPin);
    void begin();
    bool checkForGlobalDataFile();
    bool checkForBankFile(int id);
    int getPrevBankId();
    void setPrevBankId(int id);
    int getHighestBank();
    int addBank();

private:
    int chipSelectPin;
    void initiateGlobalData();
    int getGlobalValue(String valueName);
};
#endif
