#include <Arduino.h>
#include <Display.h>
#include <NextionCommands.h>
#include <DeviceConfig.h>
#include <Debugger.h>
#include <Preset.h>
#include <MenuState.h>

Display::Display(){};

void Display::setup(unsigned long baudRate)
{
    // This ensures that the baudrate is never lost which is a known issue with the Nextion
    Display::baudRate = baudRate;
    Serial2.begin(9600);
    while (!Serial2)
    {
    }
    updateBaudRate(baudRate);
    delay(100);
    Serial2.end();
    delay(100);
    Serial2.begin(baudRate);
};

void Display::bootScreen()
{
    // Not entirely sure why, but only sending the Title page does not work, seems to needs two pages for some reason?
    updatePage(SPACE_BACKGROUND);
    updatePage(TITLE_PAGE);
};

void Display::setHomeScreen()
{
    updatePage(HOME_PAGE);
};

void Display::bankSelectionPage()
{
    updatePage(BANK_SELECTION_PAGE);
}

void Display::saveMenu()
{
    updatePage(SAVE_PAGE);
}

void Display::highlightMenu(bool onOrOff, MenuState state)
{
    String color;
    color = onOrOff ? HIGHLIGHT_COLOR : DEFAULT_COLOR;
    switch (state)
    {
    case (MenuState::LOOPS):
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(LOOP_NAMES[i] + _LOOP_POS, color);
        }
        break;

    case (MenuState::INPUT_VOLUMES):
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(LOOP_NAMES[i] + _INPUT_VOLUME, color);
        }
        break;

    case (MenuState::OUTPUT_VOLUMES):
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(LOOP_NAMES[i] + _OUTPUT_VOLUME, color);
        }
        break;

    case (MenuState::PAN):
        for (int i = 0; i < ChannelID::channel_Master + 1; i++)
        {
            updatePBackgroundColorValue(LOOP_NAMES[i] + _PAN, color);
        }
        break;

    case (MenuState::PHASE):
        for (int i = 0; i < ChannelID::channel_Master + 1; i++)
        {
            updatePBackgroundColorValue(LOOP_NAMES[i] + _LEFT_PHASE, color);
        }
        for (int i = 0; i < 7; i++)
        {
            updatePBackgroundColorValue(LOOP_NAMES[i] + _RIGHT_PHASE, color);
        }
        break;
    case (MenuState::DELAY_TRILS):
        for (int i = 0; i < ChannelID::channel_Master + 1; i++)
        {
            updatePBackgroundColorValue(LOOP_NAMES[i] + _NAME, color);
        }
        break;
    }
};

void Display::sendLoopPosition(int position, int id)
{
    String positionString = String(position);
    String loop = idToStringId(id) + _LOOP_POS;
    updateValue(loop, positionString);
};

void Display::sendInputVolume(int volume, int id)
{
    int volumeForDisplay = convertVolumeForDisplay(volume);
    String volumeValueString = String(volumeForDisplay);
    String volumeIdString = idToStringId(id) + _INPUT_VOLUME;
    updateValue(volumeIdString, volumeValueString);
};

void Display::sendOutputVolume(int volume, int id)
{
    int volumeForDisplay = convertVolumeForDisplay(volume);
    String volumeValueString = String(volumeForDisplay);
    String volumeIdString = idToStringId(id) + _OUTPUT_VOLUME;
    updateValue(volumeIdString, volumeValueString);
};

void Display::sendPan(int pan, int id)
{
    String panValueString = String(pan);
    String panIdString = idToStringId(id) + _PAN;
    updateValue(panIdString, panValueString);
};

void Display::sendReturn(bool isStereo, int id)
{
    String isStereoString = isStereo ? STEREO : MONO;
    String returnIdString = idToStringId(id) + _RETURN;
    updateTextValue(returnIdString, isStereoString);
};

void Display::sendPhase(int phase, int id)
{
    String leftPhase;
    String rightPhase;

    switch (phase)
    {
    case (0):
        leftPhase = IN_PHASE;
        rightPhase = IN_PHASE;
        break;
    case (1):
        leftPhase = IN_PHASE;
        rightPhase = OUT_OF_PHASE;
        break;
    case (2):
        leftPhase = OUT_OF_PHASE;
        rightPhase = IN_PHASE;
        break;
    case (3):
        leftPhase = OUT_OF_PHASE;
        rightPhase = OUT_OF_PHASE;
        break;
    }

    String leftPhaseId = LOOP_NAMES[id] + _LEFT_PHASE;
    String rightPhaseId = LOOP_NAMES[id] + _RIGHT_PHASE;
    updateTextValue(leftPhaseId, leftPhase);
    updateTextValue(rightPhaseId, rightPhase);
};

void Display::sendDrySend(int drySend)
{
    String id = LOOP_NAMES[ChannelID::channel_Master] + _LOOP_POS;
    String drySendString;
    if (drySend >= 0)
    {
        drySendString = LOOP_NAMES[drySend];
    }
    else if (drySend == -1)
    {
        drySendString = NO_DRY_SEND;
    }
    updateTextValue(id, drySendString);
}

void Display::highlightReturn(bool onOrOff, int id)
{
    String color = onOrOff ? HIGHLIGHT_COLOR : DEFAULT_COLOR;
    if (id != 7)
    {
        String idString = LOOP_NAMES[id] + _RETURN;
        updatePBackgroundColorValue(idString, color);
    }
};

void Display::setMenuStateReturn()
{
    updateMenuStateDisplay(MENU_STATE_RETURN);
};

void Display::setMenuState(MenuState state)
{
    String stateString;
    switch (state)
    {
    case (MenuState::LOOPS):
        stateString = MENU_STATE_LOOPS;
        break;

    case (MenuState::INPUT_VOLUMES):
        stateString = MENU_STATE_INPUT_VOLUMES;
        break;

    case (MenuState::OUTPUT_VOLUMES):
        stateString = MENU_STATE_OUTPUT_VOLUMES;
        break;

    case (MenuState::PAN):
        stateString = MENU_STATE_PAN;
        break;
    case (MenuState::DELAY_TRILS):
        stateString = MENU_STATE_DELAY_TRAILS;
        break;

    case (MenuState::PHASE):
        stateString = MENU_STATE_PHASE;
        break;
    }
    updateMenuStateDisplay(stateString);
};

void Display::sendDelayTrail(bool isDelayTrail, int id)
{
    String idString = idToStringId(id) + _NAME;
    String delay = idToStringId(id) + (isDelayTrail ? IS_DELAY_TRAIL : IS_NOT_DELAY_TRAIL);
    updateTextValue(idString, delay);
};

void Display::changeSaveStatus(bool isDataChanged)
{
    String color = isDataChanged ? DATA_CHANGED_COLOR : DEFAULT_COLOR;
    updateBBackgroundColorValue(DATA_CHANGED, color);
}
//-----------------------Helpers---------------------------------

String Display::idToStringId(int id)
{
    return LOOP_NAMES[id];
};

void Display::updateValue(String id, String value)
{
    String message = id + ".val=" + value;
    sendMessage(message);
};

void Display::updateMenuStateDisplay(String menuString)
{
    updateTextValue(MENU_STATE_FOR_DISPLAY, menuString);
};

void Display::updateTextValue(String id, String value)
{
    String message = id + ".txt=" + "\"" + value + "\"";
    sendMessage(message);
};

void Display::updatePBackgroundColorValue(String id, String color)
{
    sendMessage(id + ".pco=" + color);
};

void Display::updateBBackgroundColorValue(String id, String color)
{
    Debugger::log(id + ".bco=" + color);
    sendMessage(id + ".bco=" + color);
}

void Display::updatePage(String page)
{
    sendMessage("page " + page);
};

void Display::sendMessage(String message)
{
    Serial2.print(message);
    sendEndCommand();
};

void Display::sendEndCommand()
{
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
};

int Display::convertVolumeForDisplay(int volume)
{
    return map(volume, 0, MAX_VOLUME, 0, 100);
};

void Display::updateBankPresetInfo(int bankId, PresetID id)
{
    String presetIdString = FOOT_PRESETS[id];
    String bankIdString = String(bankId);
    updateValue(BANK_NUMBER, bankIdString);
    updateTextValue(PRESET_LETTER, presetIdString);
}

void Display::updateBaudRate(unsigned long baudRate)
{
    Serial2.print("baud=" + String(baudRate));
    sendEndCommand();
}

//------------------------------------------------------------
