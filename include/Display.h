#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <MenuState.h>
#include <Preset.h>

class Display
{
public:
    Display();
    void setup(unsigned long baudRate);
    void updateAll();
    void bootScreen();
    void setHomeScreen();
    void highlightMenu(bool onOrOff, MenuState state);
    void highlightReturn(bool onOrOff, int id);
    void setMenuStateReturn();
    void setMenuState(MenuState state);
    // Updating Values
    void sendLoopPosition(int position, int id);
    void sendInputVolume(int volume, int id);
    void sendOutputVolume(int volume, int id);
    void sendPan(int pan, int id);
    void sendReturn(bool isStereo, int id);
    void sendDrySend(int id);
    void updateMenuStateDisplay(String menuString);
    void sendPhase(int phase, int id);
    void updateBankPresetInfo(int bankId, PresetID id);
    void sendDelayTrail(bool isDelayTrail, int id);

private:
    unsigned long baudRate;
    void sendMessage(String message);
    void sendEndCommand();
    void updateTextValue(String id, String value);
    void updatePBackgroundColorValue(String id, String color);
    void updateValue(String id, String value);
    void updatePage(String page);
    String idToStringId(int id);
    int convertVolumeForDisplay(int volume);
    void updateBaudRate(unsigned long baudRate);
};

#endif // ! DISPLAY_H
