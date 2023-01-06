
#ifndef EASY_ROTARY
#define EASY_ROTARY

#include <Arduino.h>
#include <RotaryEncOverMCP.h>

struct RotaryData{
    public:
        bool clockwise;
        int id;
        bool changed;
};


class EasyRotary{
    public :
        EasyRotary(int InteruptPin);
        RotaryData checkInterrupt();
        void startup(void (*function)(bool,int));
        bool getClockwise();
        int getId();

};
#endif //EASY_ROTARY