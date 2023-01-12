#include <Arduino.h>
#include <SDCard.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <Debugger.h>
#include <MemoryFree.h>

SDCard::SDCard(int csPin)
{
    chipSelectPin = csPin;
}

void SDCard::begin()
{
    while (!Serial)
    {
    } // wait for serial port to connect. Needed for native USB port only
    Debugger::log(F("Initializing SD card..."));
    if (!SD.begin(chipSelectPin))
    {
        Debugger::log(F("initialization failed!"));
    }
    Debugger::log(F("initialization done."));
};

bool SDCard::checkForGlobalDataFile()
{
    File myFile;
    String fileName = readStringFromFlash(GLOBAL_DATA_FILENAME);
    const char *fileName_cc = readStringFromFlash(GLOBAL_DATA_FILENAME).c_str();
    char *fileName_c = &fileName[0];
    Debugger::log("Checking SD card for " + String(fileName_c) + "...");
    if (!SD.exists(fileName_c))
    {
        Debugger::log("File not found. Creating new file: " + String(fileName_cc));
        myFile = SD.open(fileName_cc, O_WRITE | O_CREAT);
        myFile.close();
    }
    if (!SD.exists(fileName_c))
    {
        Debugger::log(F("Could not create file."));
        return false;
    }
    else
    {
        Debugger::log("Opened file: " + readStringFromFlash(GLOBAL_DATA_FILENAME));
        StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
        myFile = SD.open(readStringFromFlash(GLOBAL_DATA_FILENAME).c_str(), FILE_READ);
        DeserializationError err = deserializeJson(doc, myFile);
        if (err)
        {
            Debugger::log(F("Error: "));
            Debugger::log(err.f_str());
            if (err == DeserializationError::EmptyInput)
            {
                Debugger::log(F("Resetting Global Data..."));
                initiateGlobalData();
                return true;
            }
            else
            {
                return false;
            }
        }
        Debugger::log(F("Global sava data found."));
        return true;
    }
};

void SDCard::initiateGlobalData()
{
    File myFile;
    StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
    doc["prevBankId"].set(0);
    doc["highestBankNum"].set(0);
    myFile = SD.open(readStringFromFlash(GLOBAL_DATA_FILENAME).c_str(), FILE_WRITE | O_TRUNC);
    serializeJsonPretty(doc, myFile);
    myFile.close();
}

int SDCard::getPrevBankId()
{
    return getGlobalValue("prevBankId");
    ;
};

void SDCard::setPrevBankId(int id)
{
    setGlobalValue("prevBankId",id);
};

int SDCard::getHighestBank()
{
    return getGlobalValue("highestBankNum");
};

void SDCard::setHighestBank(int highestBankNum)
{
    setGlobalValue("highestBankNum",highestBankNum);
}

int SDCard::createBankFile(int newBankId)
{
    if (checkForBankFile(newBankId))
    {
        Debugger::log(F("Bank already exists!"));
        return -1;
    }
    DynamicJsonDocument doc(BANK_DATA_CAPACITY);
    doc[F("bankId")] = newBankId;
    JsonArray presets = doc.createNestedArray(F("presets"));
    for (size_t i = 0; i < 5; i++)
    {
        JsonObject preset = presets.createNestedObject();
        preset["presetId"] = i;
        JsonArray loopPositions = preset.createNestedArray(F("loopPositions"));
        JsonArray inputVolumes = preset.createNestedArray(F("inputVolumes"));
        JsonArray outputVolumes = preset.createNestedArray(F("outputVolumes"));
        JsonArray pans = preset.createNestedArray(F("pans"));
        JsonArray isStereos = preset.createNestedArray(F("isStereos"));
        JsonArray phases = preset.createNestedArray(F("phases"));
        JsonArray isDelayTrails = preset.createNestedArray(F("isDelayTrails"));
        for (size_t i = 0; i < 8; i++)
        {
            inputVolumes.add(DEFAULT_VOLUME);
            outputVolumes.add(DEFAULT_VOLUME);
            pans.add(DEFAULT_PAN);
            isStereos.add(false);

            if (i < 7)
            {
                loopPositions.add(0);
                phases.add(0);
                isDelayTrails.add(false);
            }
            preset["drySend"] = 0;
        }
    }

    File myFile;
    String newFileName = readStringFromFlash(BANKS_FOLDER) +
                         String(newBankId) +
                         readStringFromFlash(BANK_DATA_TEMPLATE);

    myFile = SD.open(newFileName.c_str(), FILE_WRITE | O_CREAT);
    serializeJsonPretty(doc, myFile);
    myFile.close();

    return newBankId;
};

int SDCard::getGlobalValue(String valueName)
{
    File myFile;
    myFile = SD.open(readStringFromFlash(GLOBAL_DATA_FILENAME).c_str(), FILE_READ);
    Debugger::log("Opening: " + String(readStringFromFlash(GLOBAL_DATA_FILENAME)));
    StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
    StaticJsonDocument<32> filter;
    filter[valueName] = true;
    DeserializationError err = deserializeJson(doc, myFile, DeserializationOption::Filter(filter));
    myFile.close();
    if (err)
    {
        Debugger::log(F("Error: "));
        Debugger::log(err.f_str());
        return -1;
    }
    int value = doc[valueName];
    return value;
};

void SDCard::setGlobalValue(String valueName, int value)
{
    File myFile;
    String globalDataFileName = readStringFromFlash(GLOBAL_DATA_FILENAME);
    const char *globalData_cc = globalDataFileName.c_str();
    myFile = SD.open(globalData_cc, FILE_READ);
    StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
    DeserializationError err = deserializeJson(doc, myFile);
    myFile.close();
    if (err)
    {
        Debugger::log("Error: ");
        Debugger::log(err.f_str());
        return;
    }
    doc[valueName] = value;
    myFile = SD.open(globalData_cc, FILE_WRITE | O_TRUNC);
    serializeJsonPretty(doc, myFile);
    myFile.close();
}

void SDCard::setGlobalValue(String valueName, bool value)
{
        File myFile;
    String globalDataFileName = readStringFromFlash(GLOBAL_DATA_FILENAME);
    const char *globalData_cc = globalDataFileName.c_str();
    myFile = SD.open(globalData_cc, FILE_READ);
    StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
    DeserializationError err = deserializeJson(doc, myFile);
    myFile.close();
    if (err)
    {
        Debugger::log("Error: ");
        Debugger::log(err.f_str());
        return;
    }
    doc[valueName].set(value);
    myFile = SD.open(globalData_cc, FILE_WRITE | O_TRUNC);
    serializeJsonPretty(doc, myFile);
    myFile.close();
}

bool SDCard::checkForBankFile(int id)
{
    String bankFileName = readStringFromFlash(BANKS_FOLDER) + String(id) + readStringFromFlash(BANK_DATA_TEMPLATE);
    char *bankFileName_c = &bankFileName[0];
    return SD.exists(bankFileName_c);
};