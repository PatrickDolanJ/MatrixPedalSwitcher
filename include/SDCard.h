#ifndef sd_card_inteface
#define sd_card_inteface

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <DeviceConfig.h>
#include <Flash.h> 
#include <Bank.h>

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
    void setHighestBank(int highestBankNum);
    int createBankFile(int newBankId);

private:
    int chipSelectPin;
    void initiateGlobalData();
    int getGlobalValue(String valueName);
    void setGlobalValue(String valueName, int value);
    void setGlobalValue(String valueName, bool value);
};
#endif
