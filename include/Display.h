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
    // Set Pages
    void bootScreen();
    void setHomeScreen();
    void bankSelectionPage();
    void setSaveMenu();
    //----
    void highlightMenu(bool onOrOff, MenuState state);
    void highlightReturn(bool onOrOff, int id);
    void setMenuStateReturn();
    void setMenuState(MenuState state);
    int getNewBankId();
    void setNewBankId(int id);
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
    void changeSaveStatus(bool isDataChanged);
    void sendBankID();

private:
    unsigned long baudRate;
    int newBankId;
    void sendMessage(String message);
    void sendEndCommand();
    void updateTextValue(String id, String value);
    void updatePBackgroundColorValue(String id, String color);
    void updateBBackgroundColorValue(String id, String color);
    void updateValue(String id, String value);
    void updatePage(String page);
    String idToStringId(int id);
    int convertVolumeForDisplay(int volume);
    void updateBaudRate(unsigned long baudRate);
};

#endif // ! DISPLAY_H
