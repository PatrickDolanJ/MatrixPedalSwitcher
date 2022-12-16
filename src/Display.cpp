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
    Serial2.begin(9600);
    while(!Serial2){}
    Serial2.print("baud=" + String(BAUD_RATE));
    sendEndCommand();
    Serial2.end();
    delay(100);
    Serial2.begin(BAUD_RATE);
}

void Display::bootScreen(){
    
}