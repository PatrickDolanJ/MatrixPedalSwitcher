#include <Arduino.h>
#include <Display.h>
#include <NextionCommands.h>
#include <DeviceConfig.h>
#include <Debugger.h>

Display::Display(){};

void Display::setup(unsigned long baudRate)
{
    // This ensures that the baudrate is never lost which is a known issue with the Nextion
    Display::baudRate = baudRate;
    Serial2.begin(9600);
    while (!Serial2)
    {
    }
    Serial2.print("baud=" + String(baudRate));
    sendEndCommand();
    Serial2.end();
    delay(100);
    Serial2.begin(baudRate);
}

void Display::bootScreen()
{
    // Not entirely sure why, but only sending the Title page does not work, seems to needs two pages for some reason?
    updatePage(SPACE_BACKGROUND);
    updatePage(TITLE_PAGE);
}

void Display::setHomeScreen()
{
    updatePage(HOME_PAGE);
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
            updatePBackgroundColorValue(LOOPS_FOR_DISPLAY[i], color);
        }
        break;

    case (MenuState::INPUT_VOLUMES):
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(INPUT_VOLUMES_FOR_DISPLAY[i], color);
        }
        break;

    case (MenuState::OUTPUT_VOLUMES):
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(OUTPUT_VOLUMES_FOR_DISPLAY[i], color);
        }
        break;

    case (MenuState::PAN):
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(PANS_FOR_DISPLAY[i], color);
        }
        break;

    case (MenuState::PHASE):
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(LEFT_PHASES_FOR_DISPLAY[i], color);
        }
        for (int i = 0; i < 8; i++)
        {
            updatePBackgroundColorValue(RIGHT_PHASES_FOR_DISPLAY[i], color);
        }
        break;
    }
};

void Display::sendLoopPosition(int position, int id)
{
    String positionString = String(position);
    String loop = LOOPS_FOR_DISPLAY[id];
    updateTextValue(loop, positionString);
};

void Display::sendInputVolume(int volume, int id)
{
    String volumeString = String(volume);
}

//-----------------------Helpers---------------------------------

void Display::updateTextValue(String id, String value)
{
    sendMessage(id + ".txt=" + value);
};

void Display::updatePBackgroundColorValue(String id, String color)
{
    sendMessage(id + ".pco=" + color);
};

void Display::updatePage(String page)
{
    sendMessage("page " + page);
};

void Display::sendMessage(String message)
{
    Serial2.print(message);
    sendEndCommand();
}

void Display::sendEndCommand()
{
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
}
