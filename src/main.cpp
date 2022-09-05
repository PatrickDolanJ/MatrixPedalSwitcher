#include <Arduino.h>
#include "MatrixLibrary.h"


AGD2188 matrix;
bool wipe_chip_once = true;

//#include <Wire.h>
void setup() {
  Serial.begin(9600);
  matrix = AGD2188();
}

void loop() {
  if(wipe_chip_once)
  {
  matrix.wipe_chip();
  wipe_chip_once = false;
  }
}