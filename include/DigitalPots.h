#ifndef DIGITAL_POTS
#define DIGITAL_POTS


#include <Arduino.h>

//CURRENTLY MASTER and LOOPS B AND C ARE CONFIRMED FOR WORKING

const int potID[6] = {cs0_pin,cs1_pin,cs2_pin,cs3_pin,cs4_pin,cs5_pin};

const String LOOP_NAMES[8] = {"A", "B", "C", "D", "E", "F", "G", "Master"};

const int LEFT_INPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 0, 4, 2, 0, 4, 2, 0, 4}, // Zero Indexed Internal Pot ID
  { 0, 0, 1, 2, 2, 3, 4, 4}  // Zero Indexed Pot ID for the Chip Select!!
};

const int RIGHT_INPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 1, 5, 3, 1, 5, 3, 1, 5},  // Zero Indexed Internal Pot ID
  { 0, 0, 1, 2, 2, 3, 4, 4}  // Zero Indexed Pot ID for the Chip Select!!
};
const int LEFT_OUTPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 2, 0, 4, 2, 0, 4, 2, 0},  // Zero Indexed Internal Pot ID
  { 0, 1, 1, 2, 3, 3, 4, 5}   // Zero Indexed Pot ID for the Chip Select!!
  };  

const int RIGHT_OUTPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 3, 1, 5, 3, 1, 5, 3, 1},  // Zero Indexed Internal Pot ID
  { 0, 1, 1, 2, 2, 3, 4, 5}   // Zero Indexed Pot ID for the Chip Select!!
  };  

void digitalPotWrite(int potID, int internalPotID, int value){
digitalWrite(potID,LOW);
delayMicroseconds(spiDelay);
SPI.transfer(internalPotID);
SPI.transfer(value);
delayMicroseconds(spiDelay);
digitalWrite(potID, HIGH);
};

#endif // !DIGITAL_POTS


