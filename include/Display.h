#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <MenuState.h>

class Display
{
public:
    Display();
    void setup(unsigned long baudRate);
    void updateAll();
    void bootScreen();
    void setHomeScreen();
    void highlightMenu(bool onOrOff, MenuState state);
    // Updating Values
    void sendLoopPosition(int position, int id);
    void sendInputVolume(int volume, int id);
    void sendOutputVolume(int volume, int id);
    void sendPan(int pan, int id);
    void sendReturn(bool isStereo, int id);
    void sendDelayTrail(bool isDelayTrail, int id);

private:
    unsigned long baudRate;
    void sendMessage(String message);
    void sendEndCommand();
    void updateTextValue(String id, String value);
    void updatePBackgroundColorValue(String id, String color);
    void updatePage(String page);
    void updateMenuStateDisplay(String menuString);
    String idToStringId(int id);
};

#endif // ! DISPLAY_H
