#include <Arduino.h>
#include <SDCard.h>
#include <SPI.h>
#include <SD.h>

int chipSelectPin;
File myfile;

SDCard::SDCard(int csPin){
    chipSelectPin = csPin ;
    
    while (!Serial) {} // wait for serial port to connect. Needed for native USB port only
    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelectPin)) {
    Serial.println("initialization failed!");
    }
}

void SDCard::makeTestFile(){

}

