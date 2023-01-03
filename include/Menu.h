#ifndef MENU
#define MENU

#include <Arduino.h>
#include <Display.h>
#include <DeviceConfig.h>
#include <MenuState.h>
#include <Bank.h>
#include <MatrixLibrary.h>

class Menu
{
public:
    Menu();
    void setup();
    void changeMenuState(int id);
    void doButton(int id);
    void doFoot(int id);
    void duringLongPress(int id);
    void doLongPress(int id);
    void doDoubleFootPress();
    void doRotaryEnoderSpin(bool isClockwise, int id);

private:
    Display display;
    MenuState menuState;
    Bank bank;
    AGD2188 matrixRight = AGD2188(RIGHT_MATRIX_ADDRESS);
    AGD2188 matrixLeft = AGD2188(LEFT_MATRIX_ADDRESS);

    void updateAllValues(Preset preset);
    int incrementLoops(bool isClockwise, int id);
    int incrementPan(bool isClockwise, int id);
    int incrementInputVolume(bool isClockwise, int id);
    int incrementOutputVolume(bool isClockwise, int id);
    int incrementPhase(bool isClockwise, int id);
    // sending data
    void sendArrayMatrixData(int loopArray[7], int size);
};

#endif // MENU