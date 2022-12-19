#include <Arduino.h>
#include <Display.h>
#include <NextionCommands.h>
#include <Debugger.h>

Display::Display(){};

void Display::sendEndCommand(){
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
}

void Display::setup(unsigned long baudRate){
    // This ensures that the baudrate is never lost which is a known issue with the Nextion
    Display::baudRate = baudRate;
    Serial2.begin(9600);
    while(!Serial2){}
    Serial2.print("baud=" + String(baudRate));
    sendEndCommand();
    Serial2.end();
    delay(100);
    Serial2.begin(baudRate);
}

void Display::bootScreen(){
    for (size_t i = 0; i < 8; i++)
    {
        Serial2.print(BOOT_SCREEN_FRAMES[i]);
        sendEndCommand();
        delay(20);
    }
}

void Display::setHomeScreen(){
    Serial2.print(HOME_PAGE);
    sendEndCommand();
}