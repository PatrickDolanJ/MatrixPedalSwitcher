#include <Arduino.h>
#include <SDCard.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <Debugger.h>

int chipSelectPin;

SDCard::SDCard(int csPin)
{
    chipSelectPin = csPin;
}

void SDCard::begin()
{
    while (!Serial)
    {
    } // wait for serial port to connect. Needed for native USB port only
    Debugger::log("Initializing SD card...");
    if (!SD.begin(chipSelectPin))
    {
        Debugger::log("initialization failed!");
    }
    Debugger::log("initialization done.");
};

bool SDCard::checkForGlobalDataFile(String fileName)
{
    File myFile;

    const char *fileName_cc = fileName.c_str();
    char *fileName_c = &fileName[0];

    Debugger::log("Checking SD card for bank save data...");
    if (!SD.exists(fileName_c))
    {
        Debugger::log("File not found. Creating new file: " + String(fileName_cc));
        myFile = SD.open(fileName_cc, O_WRITE | O_CREAT);
        myFile.close();
    }
    if (!SD.exists(fileName_c))
    {
        Debugger::log("Could not create file.");
        return false;
    }
    else
    {
        Debugger::log("Opened file: " + fileName);
        StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
        myFile = SD.open(GLOBAL_DATA_FILENAME.c_str(),FILE_READ);
        DeserializationError err = deserializeJson(doc, myFile);
        myFile.close();
        if (err)
        {
            Debugger::log("Error: ");
            Debugger::log(err.f_str());
            if (err == DeserializationError::EmptyInput)
            {
                Debugger::log("Resetting Global Data...");
                initiateGlobalData();
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};

void SDCard::initiateGlobalData()
{
    File myFile;
    StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
    doc["prevBankId"].set(0);
    myFile = SD.open(GLOBAL_DATA_FILENAME.c_str(),FILE_WRITE | O_TRUNC);
    serializeJsonPretty(doc,myFile);
    myFile.close();

}

int SDCard::getPrevBankId()
{
    File myFile;
    String globalDataFileName = GLOBAL_DATA_FILENAME;
    const char *globalData_cc = globalDataFileName.c_str();

    myFile = SD.open(globalData_cc, FILE_READ);
    Debugger::log("Opening: " + globalDataFileName);
    StaticJsonDocument<GLOBAL_DATA_CAPACITY> doc;
    StaticJsonDocument<32> filter;
    filter["prevBankId"] = true;
    DeserializationError err = deserializeJson(doc, myFile, DeserializationOption::Filter(filter));
    myFile.close();
    if (err)
    {
        Debugger::log("Error: ");
        Debugger::log(err.f_str());
        return -1;
    }
    int prevBankId = doc["prevBankId"];
    return prevBankId;
};

void SDCard::setPrevBankId(int id)
{
    File myFile;
    String globalDataFileName = GLOBAL_DATA_FILENAME;
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
    doc["prevBankId"].set(id);
    myFile = SD.open(globalData_cc, FILE_WRITE | O_TRUNC);
    serializeJsonPretty(doc, myFile);
    myFile.close();
};

int SDCard::getNumBanks(){
    // DO
};

void SDCard::addBank(){
    // DO
};