#include <FootSwitches.h>
#include <Arduino.h>
#include <pcf8574.h>
#include <DeviceConfig.h>
#include <Debugger.h>

PCF8574 footExpander(0xFF);

FootSwitches::FootSwitches(byte address)
{
  this->address = address;
};

void FootSwitches::setup(int pin, int interuptPin, void (*userFunc)(void))
{
  footExpander.setAddress(address);
  pinMode(footExpander, pin, INPUT_PULLUP);
  pinMode(interuptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interuptPin), userFunc, FALLING);
};

int FootSwitches::getFootID()
{
  Debugger::log("hex from read: ");
  int id = footExpander.read();
  Debugger::log(id,HEX);
  Debugger::log("from hex/ID converter: " + String(footHextoID(footExpander.read())));
  return footHextoID(footExpander.read());
}

int FootSwitches::footHextoID(byte hex)
{
  // Anything that isnt FF and isnt a single button returns -2 to indicate that multiple buttons are pressed
  String currentBank = "Two Pressed";
  int footID = -2;
  switch (hex)
  {
  case (0xFE):
    footID = 1;
    break;
  case (0xFD):
    footID = 2;
    break;
  case (0xFB):
    footID = 3;
    break;
  case (0xF7):
    footID = 4;
    break;
  case (0xEF):
    footID = 5;
    break;
  case (0xFF):
    footID = 0;
    break;
  }
  return footID;
}