#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <Arduino.h>

class Debugger{
    public:
        static Debugger& Instance();
        void setup(unsigned long baudRate);
        static void log(String message);
        void i2cScan();

    private:
        Debugger();
        unsigned long BAUD_RATE;
        static Debugger* instance;
        bool hasSetup;
    };

#endif // !DEBUGGER_H
