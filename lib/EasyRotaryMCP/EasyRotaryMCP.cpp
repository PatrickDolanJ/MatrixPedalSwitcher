
/*
 https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/ 
*/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Rotary.h>
#include <RotaryEncOverMCP.h>
#include <EasyRotaryMCP.h>

#if defined(ESP32) || defined(ESP8266)
#define INTERRUPT_FUNC_ATTRIB IRAM_ATTR
#else
#define INTERRUPT_FUNC_ATTRIB  
#endif

/* Our I2C MCP23017 GPIO expanders */
Adafruit_MCP23017 mcp;

typedef struct RotaryData Struct;

RotaryData data;


//Array of pointers of all MCPs if there is more than one
Adafruit_MCP23017* allMCPs[] = { &mcp };
constexpr int numMCPs = (int)(sizeof(allMCPs) / sizeof(*allMCPs));
/* function prototypes */
void intCallBack();
void cleanInterrupts();
void handleInterrupt();
void RotaryEncoderChanged(bool clockwise, int id);


/* the INT pin of the MCP can only be connected to
 * an interrupt capable pin on the Arduino, either
 * D3 or D2.
 * */
byte arduinoIntPin;


/* variable to indicate that an interrupt has occured */
volatile boolean awakenByInterrupt = false;
//function pointer
typedef void (*rotaryActionFunc)(bool clockwise, int id);
rotaryActionFunc ActionFunction = nullptr;
void ThisIsAFunction(bool,int);

//function prototypes placeholder

/* Array of all rotary encoders and their pins */
RotaryEncOverMCP rotaryEncoders[] = {
    RotaryEncOverMCP(&mcp, 0, 1, &ThisIsAFunction, 1),// physical pins 21 and 22  https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/
    RotaryEncOverMCP(&mcp, 2, 3, &ThisIsAFunction, 2),// physical pins 23 and 24  https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/
    RotaryEncOverMCP(&mcp, 4, 5, &ThisIsAFunction, 3),// physical pins 25 and 26  https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/
    RotaryEncOverMCP(&mcp, 6, 7, &ThisIsAFunction, 4),// physical pins 27 and 28  https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/
    RotaryEncOverMCP(&mcp, 8, 9, &ThisIsAFunction, 5),// physical pins 1 and 2  https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/
    RotaryEncOverMCP(&mcp, 10, 11, &ThisIsAFunction, 6),// physical pins 3 and 4  https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/
    RotaryEncOverMCP(&mcp, 12, 13, &ThisIsAFunction, 7),
    RotaryEncOverMCP(&mcp, 14, 15, &ThisIsAFunction, 8)// physical pins 7 and 8  https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/
    
};
constexpr int numEncoders = (int)(sizeof(rotaryEncoders)/sizeof(*rotaryEncoders));
void ThisIsAFunction(bool clockwise,int id){
    ActionFunction(clockwise, id);
}

void EasyRotary::startup(void (*function)(bool clockwise,int id)){
    ActionFunction = function;
    pinMode(arduinoIntPin,INPUT);
    mcp.begin();      // use default address 0
    mcp.readINTCAPAB(); //read this so that the interrupt is cleared

    //initialize all rotary encoders

    //Setup interrupts, OR INTA, INTB together on both ports.
    //thus we will receive an interrupt if something happened on
    //port A or B with only a single INT connection.
    //mcp.setupInterrupts(true,false,LOW);

    //Initialize input encoders (pin mode, interrupt)
    for(int i=0; i < numEncoders; i++) {
        rotaryEncoders[i].init();
    }
    attachInterrupt(digitalPinToInterrupt(arduinoIntPin), intCallBack, FALLING);
}

EasyRotary::EasyRotary(int InteruptPin){
    arduinoIntPin = InteruptPin;
    Serial.println("MCP23017 Interrupt");

}

// The int handler will just signal that the int has happened
// we will do the work from the main loop.
void INTERRUPT_FUNC_ATTRIB intCallBack() {
    awakenByInterrupt=true;
}

RotaryData EasyRotary::checkInterrupt() {
    if(awakenByInterrupt) {
        // disable interrupts while handling them.
        detachInterrupt(digitalPinToInterrupt(arduinoIntPin));
        handleInterrupt();
        attachInterrupt(digitalPinToInterrupt(arduinoIntPin),intCallBack,FALLING);
    }
    data.changed = awakenByInterrupt;
    return data;
}

void handleInterrupt(){
    //Read the entire state when the interrupt occurred

    //An interrupt occurred on some MCP object.
    //since all of them are ORed together, we don't
    //know exactly which one has fired.
    //just read all of them, pre-emptively.

    for(int j = 0; j < numMCPs; j++) {
        uint16_t gpioAB = allMCPs[j]->readINTCAPAB();
        // we need to read GPIOAB to clear the interrupt actually.
        volatile uint16_t dummy = allMCPs[j]->readGPIOAB();
        for (int i=0; i < numEncoders; i++) {
            //only feed this in the encoder if this
            //is coming froma the correct MCP
            if(rotaryEncoders[i].getMCP() == allMCPs[j])
                rotaryEncoders[i].feedInput(gpioAB);
        }
    }
    cleanInterrupts();
}

// handy for interrupts triggered by buttons
// normally signal a few due to bouncing issues
void cleanInterrupts(){
#ifdef __AVR__
    EIFR=0x01;
#endif
    awakenByInterrupt=false;
}
