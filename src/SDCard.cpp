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

void SDCard::setSaveFileName(String fileName)
{
    bankSaveFileName = fileName;
    bankSaveFileName_cc = bankSaveFileName.c_str();
    bankSaveFileName_c = &bankSaveFileName[0];
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

bool SDCard::checkForSaveFile()
{
    File myFile;
    Debugger::log("Checking SD card for bank save data...");
    if (!SD.exists(bankSaveFileName_c))
    {
        Debugger::log("File not found. Creating new file: " + bankSaveFileName);
        myFile = SD.open(bankSaveFileName_cc, FILE_WRITE);
        myFile.close();
    }
    if (!SD.exists(bankSaveFileName_c))
    {
        return false;
    }
    else
    {
        Debugger::log("Opened file: " + bankSaveFileName);
        return true;
    }
};

int SDCard::getPrevBankId()
{
    File myFile;

    myFile = SD.open(bankSaveFileName_cc, FILE_READ);
    Debugger::log("Opening: " + bankSaveFileName);

    const int capacity = 384;
    StaticJsonDocument<capacity> doc;
    StaticJsonDocument<32> filter;
    filter["prevBankId"] = true;
    DeserializationError err = deserializeJson(doc, myFile, DeserializationOption::Filter(filter));
    int prevBankId = doc["prevBankId"];
    myFile.close();
    if (err)
    {
        Debugger::log("Error: ");
        Debugger::log(err.f_str());
        return -1 ;
    }
    return prevBankId;
}