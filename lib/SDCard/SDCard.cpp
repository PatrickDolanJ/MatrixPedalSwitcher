#include <Arduino.h>
#include <SDCard.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>

int chipSelectPin;
File myFile;

SDCard::SDCard(int csPin){
    chipSelectPin = csPin ;
}

void SDCard::begin(){
     while (!Serial) {} // wait for serial port to connect. Needed for native USB port only
    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelectPin)) {
    Serial.println("initialization failed!");
    }
    Serial.println("initialization done.");
}

void SDCard::readTestFile(){
    myFile = SD.open("fart.txt",FILE_READ);

    if(!myFile){
        Serial.println("Cannot open file.");
        return;
    }


    const int capacity = 64;
    StaticJsonDocument<capacity> doc;
    DeserializationError err = deserializeJson(doc,myFile);
    if(err){
        Serial.print("Error: ");
        Serial.println(err.f_str());
        return;
    }



}


/** 
bankA.txt
{
    presets : [
        ...
    ]
}
bankB.txt
{
    presets: [
        ...
    ]
}


banks.txt
{
    banks : [
        presets : [
            channels : [
                ...
            ],
            ...
        ],
        ...
    ]
}

*/

