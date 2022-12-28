#include <Arduino.h>
#include <Display.h>
#include <NextionCommands.h>
#include <DeviceConfig.h>
#include <Debugger.h>

Display::Display(){};

void Display::sendEndCommand()
{
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
    Serial2.write(END_BYTE);
}

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
    Serial2.print(SPACE_BACKGROUND);
    sendEndCommand();
    Serial2.print(TITLE_PAGE);
    sendEndCommand();
}

void Display::setHomeScreen()
{
    Serial2.print(HOME_PAGE);
    sendEndCommand();
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
            Serial2.print(LOOPS_FOR_DISPLAY[i] + ".pco=" + color);
            sendEndCommand();
        }
        break;

    case (MenuState::INPUT_VOLUMES):
        for (int i = 0; i < 8; i++)
        {
            Serial2.print(ADDRESS_FOR_DISPLAY[i][0] + ".pco=" + color);
            sendEndCommand();
        }
        break;

    case (MenuState::OUTPUT_VOLUMES):
        for (int i = 0; i < 8; i++)
        {

            Serial2.print(ADDRESS_FOR_DISPLAY[i][1] + ".pco=" + color);
            sendEndCommand();
        }
        break;

    case (MenuState::PAN):
        for (int i = 0; i < 8; i++)
        {
            Serial2.print(ADDRESS_FOR_DISPLAY[i][3] + ".pco=" + color);
            sendEndCommand();
        }
        break;

    case (MenuState::PHASE):
        for (int i = 0; i < 8; i++)
        {
            Serial2.print(ADDRESS_FOR_DISPLAY[i][4] + ".pco=" + color);
            sendEndCommand();
        }
        for (int i = 0; i < 8; i++)
        {
            Serial2.print(ADDRESS_FOR_DISPLAY[i][5] + ".pco=" + color);
            sendEndCommand();
        }
        break;
    }
};